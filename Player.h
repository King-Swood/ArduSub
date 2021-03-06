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
0x10, 0x30, 0x38, 0x38, 0x30, 0x30, 0x10, 0x10,
0x10, 0x10, 0x18, 0x18, 0x38, 0x38, 0x18, 0x10, 
0x10, 0x18, 0x38, 0x38, 0x18, 0x18, 0x10, 0x10, 
};

class Game;

class Sub : public ObjectBase
{
public:
  Sub() = default;
  Sub(int x, int y, bool valid = true):
    ObjectBase(x,y,valid)
  {
    Reset();
  }

  void Reset()
  {
    valid_ = true;
    movingRight = true;
  }

  int Width() const override {return SubSprite[0];}
  int Height() const override {return 3;}
  
  Rect BoundingBox() const override
  {
    return Rect(x_/10, (y_/10)+3, 8, 3);
  }
  
  void Update() override;
  void Draw() override;
  void UpdateBubbles(bool diving, bool crashed);
private:
  long unsigned lastBubble = millis();
  long unsigned lastMove = millis();
  unsigned bubblePeriod = 333;
  bool movingRight :1;
};
