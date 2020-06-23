#include "HiScore.h"
#include <Arduboy2.h>

// TODO: If we want more on the screen, the screen could scroll down.
// We could do this by just decreasing the initial y pixel each frame.
PROGMEM static const HiScore HiScores::Records[] = 
{
  {"Darren Pearce", 84},
  {"Johnny Dixon", 57},
  {"Sarah Pearce", 42},
  {"Bill Sinno", 32},
};

static void DrawHiScore(Arduboy2 &arduboy, const HiScore &score)
{
    int initialX = arduboy.getCursorX();
    arduboy.print(score.name);
    arduboy.setCursor(initialX + 100, arduboy.getCursorY());
    arduboy.print(score.seconds);
}

void HiScores::DrawHallOfFame(Arduboy2 &arduboy)
{
  arduboy.drawRect(0, 0, WIDTH, HEIGHT);
  
  static const int TopLeftX = 5;
  static const int TopLeftY = 5;
  arduboy.setCursor(TopLeftX + 30,TopLeftY);
  arduboy.setTextSize(1);
  arduboy.print("Hall of Fame");
  arduboy.setCursor(TopLeftX, TopLeftY + 13);

  for( int i=0; i<(sizeof(Records)/sizeof(HiScore)); i++) {
    HiScore hiScore;
    memcpy_P( &hiScore, &Records[i], sizeof(HiScore));
    DrawHiScore(arduboy, hiScore);
    arduboy.setCursor(TopLeftX, arduboy.getCursorY() + 10);
  }
}
