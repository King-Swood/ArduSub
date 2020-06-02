#include <Arduboy2.h>
#include "Globals.h"
#include "Player.h"
#include "Obstacle.h"

Arduboy2 arduboy;

const Rect BoundLeft(-WIDTH, -1, WIDTH, HEIGHT);
const Rect BoundRight(WIDTH, -1, WIDTH, HEIGHT);
const Rect BoundTop(0, -HEIGHT, WIDTH, HEIGHT);
const Rect BoundBottom(0, HEIGHT, WIDTH, HEIGHT);
const Rect BoundScreen(0, 0, WIDTH, HEIGHT);

enum class GameState {
  Running,
  Finished,
  Size,
};

class Game {
public:
  Game() = default;
  Sub sub;

  ObjectManager<Mine, 20> mines;
  
  long unsigned originalTimeMS;
  long unsigned nextMineTimeMS;
  GameState state;
  GameState lastState;

  void Reset()
  {
    state = GameState::Running;
    sub = Sub(0, 10);
    for (Mine& mine : mines.items) {
      mine = Mine();
    }
    originalTimeMS = millis();
    nextMineTimeMS = millis() + random(1000);
  
  #if TEST_COLLISIONS
    for (Mine& mine : game->mines) {
      AddMine(true);
    }
  #endif
  }
  
  void Update()
  {
    bool firstTime = (state != lastState);
    lastState = state;
  
    switch (state) {
      case GameState::Running:
        sub.Update();
        
        mines.UpdateAll([](Mine& mine, Game* game)
        {
          if (game->sub.IsColliding(mine)) {
            game->sub.Invalidate();
          }
        }, this);
        
        if (millis() > nextMineTimeMS) {
          AddMine();
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

struct Title {
  long unsigned lastTimeMS;
  bool hidden;
  bool starGame;
};

void TitleInit(struct Title *title)
{
  title->lastTimeMS = millis();
  title->hidden = false; 
  title->starGame = false;
}

void TitleUpdate(Title *title)
{
  if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) {
    title->starGame = true;
  }
  
  if ((millis() - title->lastTimeMS) > 500) {
    title->lastTimeMS = millis();
    title->hidden = !title->hidden;
  }
}

void TitleDraw(Title *title)
{
  arduboy.setTextSize(2);
  arduboy.setCursor(30, 10);
  arduboy.print("SUB");
  arduboy.setTextSize(1);

  if (!title->hidden) {
    arduboy.setCursor(10,35);
    arduboy.print("A or B to Start");
  }
}

enum class State {
  Title,
  Game,
  Size,
};
State currentState;
State lastState;
Title title;
Game game;

void setup() {
  Serial.begin(9600);
  arduboy.begin();

  // here we set the framerate to 15, we do not need to run at
  // default 60 and it saves us battery life
#if TEST_COLLISIONS
  arduboy.setFrameRate(5);
#else
  arduboy.setFrameRate(30);
#endif
  
  currentState = State::Title;
  lastState = State::Size;
  randomSeed(analogRead(0));
}

void loop() {
  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame())) {
    return;
  }

  arduboy.pollButtons();

  bool firstTime = (currentState != lastState);
  lastState = currentState;
  
  // first we clear our screen to black
  arduboy.clear();

  switch (currentState) {
    case State::Title:
      if (firstTime) {
        TitleInit(&title);
      }
      TitleUpdate(&title);
      TitleDraw(&title);
      if (title.starGame) {
        currentState = State::Game;
      }
      break;
    case State::Game:
      if (firstTime) {
        game.Reset();
      }
      game.Update();
      game.Draw();
      if (game.state == GameState::Finished) {
        currentState = State::Title;
      }
      break;
    case State::Size:
      break;
  }

  arduboy.display();
}
