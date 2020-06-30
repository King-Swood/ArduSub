#pragma once
#include "Globals.h"
#include "Player.h"
#include "Obstacle.h"
#include "Particles.h"
#include "Title.h"

extern Arduboy2 arduboy;

// TODO: Add timer to top of screen.
// TODO: Make it so we can enable/disable player control for the sub.
//        This way we can call the subs update function as it moves onto the screen, and animate it/cause bubbles.
// TODO: It would be good to be able to update bubbles/mines in all states, so bubbles come off the sub as it enters the screen.
// TODO: Start adding audio.
// TODO: Handle the case where the player reaches the edge of the screen.

enum class GameState {
  Initial,
  Menu = Initial,
  GameStart,
  Countdown,
  Running,
  GameOver,
  Size,
};

class Game {
public:
  Game()
  {
    Reset();
  }
    
  Title title_;
  Sub sub;
  ObjectManager<Mine, 20> mines;
  ObjectManager<Bubble, 20> bubbles;
  
  long unsigned gameTimeStartMS = 0;
  long unsigned gameTimeEndMS = 0;
  long unsigned nextMineTimeMS;
  long unsigned maxMineTimeMS = 3000;
  static const long unsigned MinMineTimeMS = 800;
  static const long unsigned CountDownTimeMS = 2999;
  static const long unsigned GoDisplayMS = 800;
  static const long unsigned GameOverMinMS = 2000;
  GameState state = GameState::Initial;
  GameState lastState = GameState::Size;
  
  void Update()
  {
    bool firstTime = (state != lastState);
    bool showHiScores = (lastState == GameState::GameOver);
    lastState = state;
  
    switch (state) {
      case GameState::Menu:
        if (firstTime) {
          title_ = Title();
          if (showHiScores) {
            title_.DisplayHiScores();
          }
        }
        title_.Update();
        if (title_.IsPlayingGame()) {
          state = GameState::GameStart;
        }
        break;
      case GameState::GameStart:
        if (firstTime) {
          Reset();
          sub.SetPosition(0 - sub.Width(), 40);
        }
        sub.Move(5, 0);
        sub.UpdateBubbles(false, false);
        bubbles.UpdateAll();
        if (sub.X() >= 50) {
          state = GameState::Countdown;
        }
        break;
      case GameState::Countdown:
        if (firstTime){
          gameTimeStartMS = millis();
        }
        sub.UpdateBubbles(false, false);
        bubbles.UpdateAll();
        if ((millis() - gameTimeStartMS) >= CountDownTimeMS) {
          state = GameState::Running;
        }
        break;
      case GameState::Running:
        if (firstTime) {
          gameTimeStartMS = millis();
        }
        UpdateAll();
        if (!sub.IsValid()) {
          state = GameState::GameOver;
        }
        break;
      case GameState::GameOver:
        if (firstTime) {
          gameTimeEndMS = millis();
        }
        UpdateAll();
        if ((millis() - gameTimeEndMS) >= GameOverMinMS) {
          if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) {
            state = GameState::Initial;
          }
        }
        break;
      case GameState::Size:
        break;
    }
  }

  void Draw()
  {
    if ((state == GameState::Menu) || (lastState == GameState::Menu)) {
      return;
    }
    // TODO: Not sure if we should continue doing this or not...
    // We use lastState here to draw, because otherwise the actual state may have changed but we haven't initialised the new state yet.
    // This way, we are always drawing a scene which is valid.
    sub.Draw();
    mines.DrawAll();
    bubbles.DrawAll();

    switch (lastState) {
      case GameState::Countdown: {
        long unsigned countdown = millis() - gameTimeStartMS;
        if (countdown > CountDownTimeMS) {
          countdown = CountDownTimeMS;
        }
        DrawCountdown(((CountDownTimeMS - countdown) / 1000) + 1);
        break;
      }
      case GameState::Running: {
        if ((millis() - gameTimeStartMS) < GoDisplayMS) {
          DrawCountdown(0);
        }
        break;
      }
      case GameState::GameOver: {
        DrawGameOver((gameTimeEndMS - gameTimeStartMS) / 1000);
        break;
      }
    }

    arduboy.drawRect(0, 0, WIDTH, HEIGHT);
  }

  static void DrawGameOver(long unsigned gameTimeS)
  {
    static const int Width = 63;
    static const int Height = 22;
    static const int TopLeftX = (WIDTH >> 1) - (Width >> 1);
    static const int TopLeftY = (HEIGHT >> 1) - (Height >> 1);
    arduboy.drawRect(TopLeftX, TopLeftY, Width, Height);
    arduboy.fillRect(TopLeftX+1, TopLeftY+1, Width-2, Height-2, BLACK);
    arduboy.setCursor(TopLeftX+5,TopLeftY+2);
    arduboy.print("Game Over");
    arduboy.setCursor(TopLeftX+2,TopLeftY+11);
    arduboy.print("Lasted");
    if (gameTimeS < 100) {
      // We have room to put a space
      arduboy.print(" ");
    }
    arduboy.print(gameTimeS);
    arduboy.print("s");
  }

  static void DrawCountdown(long unsigned timeLeftS)
  {
    static const int Width = 10;
    static const int Height = 10;
    static const int TopLeftX = (WIDTH >> 1) - (Width >> 1);
    static const int TopLeftY = (HEIGHT >> 1) - (Height >> 1);
    arduboy.setCursor(TopLeftX,TopLeftY);
    if (timeLeftS > 0) {
      arduboy.print(timeLeftS);
    }
    else {
      arduboy.print("GO");
    }
  }

  void AddMine(bool fixedPosition = false)
  {
    int radius = random(2, 10);
    if (fixedPosition) {
      mines.Add(Mine(random(1, (WIDTH-(radius << 1))),
        random(1, (HEIGHT-(radius << 1))),
        radius));
    }
    else {
      int index = mines.Add(Mine(WIDTH-1,
        random(0, (HEIGHT-(radius << 1))),
        radius));
      if (index >= 0) {
        mines[index].SetVelocity(random(-15, -5), random(-3,4));
//        mines[index].SetVelocity(-10, 0);
      }
    }
  }
private:
  void UpdateAll()
  {
    sub.Update();
    bubbles.UpdateAll();
    
    mines.UpdateAll([](Mine& mine, Game* game)
    {
      if (game->sub.IsColliding(mine)) {
        game->sub.Invalidate();
      }
    }, this);
    
    if (millis() > nextMineTimeMS) {
      AddMine();
      nextMineTimeMS = millis() + random(maxMineTimeMS >> 1, maxMineTimeMS);
      maxMineTimeMS -= 100;
      if (maxMineTimeMS < MinMineTimeMS) {
        maxMineTimeMS = MinMineTimeMS;
      }
    }
  }

  void Reset()
  {
    sub = Sub(-100,-100);
    mines.ClearAll();
    bubbles.ClearAll();
    gameTimeStartMS = 0;
    gameTimeEndMS = 0;
    nextMineTimeMS = (millis() + random(1000));
    maxMineTimeMS = 3000;

  #if TEST_COLLISIONS
    for (int i = 0; i < mines.Size(); i++) {
      AddMine(true);
    }
  #endif
  }
};
