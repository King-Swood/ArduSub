#pragma once
#include "Globals.h"
#include "ObjectBase.h"

extern Arduboy2 arduboy;
extern const Rect BoundTop;
extern const Rect BoundBottom;

const unsigned char PROGMEM SubSprite[] =
{
// width, height,
8, 8,
0x10, 0x10, 0x30, 0x30, 0x38, 0x38, 0x30, 0x10, 
};

class Game;

class Sub : public ObjectBase
{
public:
  Sub() = default;
  Sub(int x, int y, bool valid = true):
    ObjectBase(x,y,valid)
  {}

  void Reset()
  {
    valid_ = true;
  }

  int Width() const override {return SubSprite[0];}
  int Height() const override {return SubSprite[1];}
  
  Rect BoundingBox() const override
  {
      return Rect(x_, y_+3, 8, 3);
  }
  
  void Update() override;
  void Draw() override
  {
    Sprites::drawOverwrite(x_, y_, SubSprite, 0);
#if TEST_COLLISIONS
    DrawBoundingBox();
#endif
  }
private:
  long unsigned lastBubble = millis();
  unsigned bubblePeriod = 333;
};
