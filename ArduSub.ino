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
  static const int MinesLength = 20;
  Mine mines[MinesLength];
  int minesCount;
  long unsigned originalTimeMS;
  long unsigned nextMineTimeMS;
  GameState state;
  GameState lastState;

  void AddMine(bool fixedPosition = false)
  {
    if (minesCount < MinesLength) {
      minesCount++;
      for (int i = 0; i < MinesLength; i++) {
        if (!mines[i].IsValid()) {
          int radius = random(2, 5);
          if (fixedPosition) {
            mines[i] = Mine(random(1, (WIDTH-(radius << 1))),
              random(1, (HEIGHT-(radius << 1))),
              radius);
          }
          else {
            mines[i] = Mine(WIDTH-1,
              random(0, (HEIGHT-(radius << 1))),
              radius);
            mines[i].SetVelocity(-1, 0);
          }
          break;
        }
      }
    }
  }
};

void GameInit(struct Game *game)
{
  game->state = GameState::Running;
  game->sub = Sub(0, 10);
  for (Mine& mine : game->mines) {
    mine = Mine();
  }
  game->minesCount = 0;
  game->originalTimeMS = millis();
  game->nextMineTimeMS = millis() + random(1000);

#if TEST_COLLISIONS
  for (Mine& mine : game->mines) {
    game->AddMine(true);
  }
#endif
}

void GameUpdate(Game *game)
{
  bool firstTime = (game->state != game->lastState);
  game->lastState = game->state;

  switch (game->state) {
    case GameState::Running:
      game->sub.Update();
      for (auto& mine : game->mines) {
        if (mine.IsValid()) {
          mine.Update();
          if (game->sub.IsColliding(mine)) {
            game->sub.Invalidate();
          }
          if (!mine.IsValid()) {
            game->minesCount--;
          }
        }
      }
      if (millis() > game->nextMineTimeMS) {
        game->AddMine();
        game->nextMineTimeMS = millis() + random(1000);
      }
      if (!game->sub.IsValid()) {
        game->state = GameState::Finished;
      }
      break;
    case GameState::Finished:
      break;
    case GameState::Size:
      break;
  }
}

void GameDraw(Game *game)
{
  switch (game->state) {
    case GameState::Running:
      game->sub.Draw();
      for (const auto& mine : game->mines) {
        if (mine.IsValid()) {
          mine.Draw();
        }
      }
      break;
    case GameState::Finished:
      game->sub.Draw();
      break;
    case GameState::Size:
      break;
  }
  arduboy.drawRect(0, 0, WIDTH, HEIGHT);
}

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
        GameInit(&game);
      }
      GameUpdate(&game);
      GameDraw(&game);
      if (game.state == GameState::Finished) {
        currentState = State::Title;
      }
      break;
    case State::Size:
      break;
  }

  arduboy.display();
}
