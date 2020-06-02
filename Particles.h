#pragma once
#include "Globals.h"
#include "ObjectBase.h"

extern Arduboy2 arduboy;

class Bubble : public ObjectBase
{
public:
  Mine() = default;
  Mine(int x, int y):
    ObjectBase(x,y,true),
    vY(1),
    vX(1),
    radius(random(2,4))
  {}

  int Width() const override {return radius_ << 1;}
  int Height() const override {return radius_ << 1;}
  Rect BoundingBox() const override
  {
    // The bounding box is smaller than the circle by 1 pixel on each side.
    // This means that the corners of the bounding box line up well with the "corners" of the circle.
    return Rect(x_+1, y_+1, (radius_ << 1)-1, (radius_ << 1)-1);
  }
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
    // The x,y coordinates are the center of the circle, so we need to correct for this when drawing.
    arduboy.drawCircle(x_+radius_, y_+radius_, radius_);
#if TEST_COLLISIONS
    DrawBoundingBox();
#endif
  }
private:
  int radius_;
};
