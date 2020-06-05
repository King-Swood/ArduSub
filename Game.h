#pragma once
#include "Globals.h"
#include "Player.h"
#include "Obstacle.h"
#include "Particles.h"

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
          maxMineTimeMS -= 50;
          if (maxMineTimeMS < MinMineTimeMS) {
            maxMineTimeMS = MinMineTimeMS;
          }
        }
        if (!sub.IsValid()) {
          state = GameState::Finished;
        }
        break;
      case GameState::Finished:
        break;
      case GameState::Size:
        break;
    }
  }

  void Draw()
  {
    switch (state) {
      case GameState::Running:
        sub.Draw();
        mines.DrawAll();
        bubbles.DrawAll();
        break;
      case GameState::Finished:
        sub.Draw();
        break;
      case GameState::Size:
        break;
    }
    arduboy.drawRect(0, 0, WIDTH, HEIGHT);
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
