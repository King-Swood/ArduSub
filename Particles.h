#pragma once
#include "Globals.h"
#include "ObjectBase.h"

extern Arduboy2 arduboy;

class Bubble : public ObjectBase
{
public:
  Bubble() = default;
  Bubble(int x, int y):
    ObjectBase(x,y,true)
  {
    SetVelocity(0, -1);
  }

  int Width() const override {1;}
  int Height() const override {1;}
  void Update() override
  {
    if (IsValid()) {
      Move(vX_, vY_);
      if (!Arduboy2Base::collide(BoundingBox(), BoundScreen)) {
        Invalidate();
      }
    }
  }
  void Draw() override
  {
    arduboy.drawPixel(x_, y_);
  }
};
