#include "Globals.h"
#include "Game.h"

Arduboy2 arduboy;

const Rect BoundLeft(-WIDTH, -1, WIDTH, HEIGHT);
const Rect BoundRight(WIDTH, -1, WIDTH, HEIGHT);
const Rect BoundTop(0, -HEIGHT, WIDTH, HEIGHT);
const Rect BoundBottom(0, HEIGHT, WIDTH, HEIGHT);
const Rect BoundScreen(0, 0, WIDTH, HEIGHT);

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
        game = Game();
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
