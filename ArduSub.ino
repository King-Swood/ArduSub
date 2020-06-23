#include "Globals.h"
#include "Title.h"
#include "Game.h"
#include "HiScore.h"

Arduboy2 arduboy;

// TODO: Work out how to statically initialise these and put them in PROGMEM
const Rect BoundLeft(-WIDTH, -1, WIDTH, HEIGHT);
const Rect BoundRight(WIDTH, -1, WIDTH, HEIGHT);
const Rect BoundTop(0, -HEIGHT, WIDTH, HEIGHT);
const Rect BoundBottom(0, HEIGHT, WIDTH, HEIGHT);
const Rect BoundScreen(0, 0, WIDTH, HEIGHT);

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
 
  randomSeed(analogRead(0));
}

void loop() {
  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame())) {
    return;
  }

  arduboy.pollButtons();
  
  // first we clear our screen to black
  arduboy.clear();

  game.Update();
  game.Draw();

  arduboy.display();
}
