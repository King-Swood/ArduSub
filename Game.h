#pragma once
#include "Globals.h"
#include "Player.h"
#include "Obstacle.h"
#include "Particles.h"

enum class GameState {
  Running,
  Finished,
  Size,
};

class Game {
public:
  Game():
    sub(10,10),
    originalTimeMS(millis()),
    nextMineTimeMS(millis() + random(1000)),
    state(GameState::Running),
    lastState(GameState::Size)
  {
  #if TEST_COLLISIONS
    for (Mine& mine : game->mines) {
      AddMine(true);
    }
  #endif
  }
    
  Sub sub;

  ObjectManager<Mine, 20> mines;
  ObjectManager<Bubble, 20> bubbles;
  
  long unsigned originalTimeMS;
  long unsigned nextMineTimeMS;
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
          bubbles.Add(Bubble(20, 20));
          nextMineTimeMS = millis() + random(1000);
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
    int radius = random(2, 5);
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
      mines[index].SetVelocity(-1, 0);
      }
    }
  }
};
