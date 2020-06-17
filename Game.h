#pragma once
#include "Globals.h"
#include "Player.h"
#include "Obstacle.h"
#include "Particles.h"

extern Arduboy2 arduboy;

// TODO: Add timer to top of screen.
// TODO: Add "Game over" screen, which shows time.
// TODO: Add explosion animation when sub crashes.

enum class GameState {
  Running,
  Finished,
  Size,
};

class Game {
public:
  Game():
    sub(5,26),
    mines(),
    bubbles(),
    gameTimeStartMS(millis()),
    originalTimeMS(millis()),
    nextMineTimeMS(millis() + random(1000)),
    state(GameState::Running),
    lastState(GameState::Size)
  {
  #if TEST_COLLISIONS
    for (int i = 0; i < mines.Size(); i++) {
      AddMine(true);
    }
  #endif
  }
    
  Sub sub;
  ObjectManager<Mine, 20> mines;
  ObjectManager<Bubble, 20> bubbles;
  
  long unsigned gameTimeStartMS;
  long unsigned gameTimeEndMS = 0;
  long unsigned originalTimeMS;
  long unsigned nextMineTimeMS;
  long unsigned maxMineTimeMS = 3000;
  static const long unsigned MinMineTimeMS = 800;
  GameState state;
  GameState lastState;
  
  void Update()
  {
    bool firstTime = (state != lastState);
    lastState = state;
  
    switch (state) {
      case GameState::Running:
      case GameState::Finished:
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

        if (state == GameState::Running) {
          if (!sub.IsValid()) {
            state = GameState::Finished;
            gameTimeEndMS = millis();
          }
        }
        break;
      case GameState::Size:
        break;
    }
  }

  void Draw()
  {
    switch (state) {
      case GameState::Running:
      case GameState::Finished:
        sub.Draw();
        mines.DrawAll();
        bubbles.DrawAll();
        if (state == GameState::Finished) {
          DrawGameOver((gameTimeEndMS - gameTimeStartMS) / 1000);
        }
        break;
      case GameState::Size:
        break;
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
};
