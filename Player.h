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

class Sub : public ObjectBase
{
public:
  Sub() = default;
  Sub(int x, int y, bool valid = true):
    ObjectBase(x,y,valid)
  {}

  int Width() const override {return SubSprite[0];}
  int Height() const override {return SubSprite[1];}
  
  Rect BoundingBox() const override
  {
      return Rect(x_, y_+3, 8, 3);
  }
  
  void Update() override
  {
    bool hitWall = false;
    // Check in Y direction first
    Rect tempRect = BoundingBox();
    if (Arduboy2Base::collide(tempRect, BoundTop) || Arduboy2Base::collide(tempRect, BoundBottom)) {
      hitWall = true;
    }
  
    if (hitWall) {
      Invalidate();
    }
    else {
#if !TEST_COLLISIONS
      if (arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON)) {
        y_ -= 1;
      }
      else {
        y_ += 1;
      }
#else 
      if (arduboy.pressed(LEFT_BUTTON)) {
        x_ -= 1;
      }
      if (arduboy.pressed(RIGHT_BUTTON)) {
        x_ += 1;
      }
      if (arduboy.pressed(UP_BUTTON)) {
        y_ -= 1;
      }
      if (arduboy.pressed(DOWN_BUTTON)) {
        y_ += 1;
      }
#endif
    }
  }
  void Draw() override
  {
    Sprites::drawOverwrite(x_, y_, SubSprite, 0);
#if TEST_COLLISIONS
    DrawBoundingBox();
#endif
  }
};
