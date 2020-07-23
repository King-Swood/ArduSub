#pragma once
#include "Globals.h"
#include "ObjectBase.h"

extern Arduboy2 arduboy;
extern const Rect BoundScreen;

class Mine : public ObjectBase
{
public:
  Mine() = default;
  Mine(int x, int y, int radius = 2):
    ObjectBase(x,y,true),
    radius_(radius)
  {}

  int Width() const override {return radius_ << 1;}
  int Height() const override {return radius_ << 1;}
  Rect BoundingBox() const override
  {
    // The mine bounding box is smaller than the circle by 1 pixel on each side.
    // This means that the corners of the bounding box line up well with the "corners" of the circle.
    return Rect((x_/10)+1, (y_/10)+1, (radius_ << 1)-1, (radius_ << 1)-1);
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
    arduboy.drawCircle((x_/10)+radius_, (y_/10)+radius_, radius_);
#if TEST_COLLISIONS
    DrawBoundingBox();
#endif
  }
private:
  uint8_t radius_;
};
