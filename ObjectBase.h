#pragma once
#include "Globals.h"

extern Arduboy2 arduboy;

class ObjectBase
{
public:
  ObjectBase() = default;
  ObjectBase(int x, int y, bool valid = false):
    x_(x),
    y_(y),
    valid_(valid)
  {}

  void Move(int x, int y)
  {
    x_ += x;
    y_ += y;
  }

  void SetVelocity(int x, int y)
  {
    vX_ = x;
    vY_ = y;
  }

  virtual Rect BoundingBox() const
  {
      return Rect(x_, y_, Width(), Height());
  }

  bool IsColliding(const ObjectBase& other)
  {
    return Arduboy2Base::collide(BoundingBox(), other.BoundingBox());
  }

  void Invalidate() {valid_ = false;}
  bool IsValid() const {return valid_;}

  virtual int Width() const = 0;
  virtual int Height() const = 0;
  virtual void Draw() = 0;
  virtual void Update() = 0;
protected:
  int x_ = 0;
  int y_ = 0;
  int vX_ = 0;
  int vY_ = 0;
  bool valid_ :1;

  void DrawBoundingBox()
  {
    Rect box = BoundingBox();
    arduboy.drawRect(box.x, box.y, box.width, box.height);
  }
};
