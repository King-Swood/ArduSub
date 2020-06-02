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

  virtual void Reset()
  {
  x_ = 0;
  y_ = 0;
  vX_ = 0;
  vY_ = 0;
  valid_ = true;
  }

  void Move(int x, int y)
  {
    x_ += x;
    y_ += y;
  }

  void SetPosition(int x, int y)
  {
    x_ = x;
    y_ = y;
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

template <class T, size_t ElementCount>
class ObjectManager
{
public:
  size_t Size() const {return ElementCount;}
  T items[ElementCount];
  T& operator[](size_t index)
  {
    return items[index];
  }
  const T& operator[](size_t index) const
  {
    return items[index];
  }
  virtual int Add(const T& item)
  {
    if (count_ >= ElementCount) {
      return -1;
    }
    for (size_t i = 0; i < ElementCount; i++) {
      if (!items[i].IsValid()) {
        items[i] = item;
        count_++;
        return i;
      }
    }
  }
  void ClearAll()
  {
    for (auto& item : items) {
      item.Invalidate();
    }
  }
  void UpdateAll(void (*callback)(T&, void*) = nullptr, void *data = nullptr)
  {
    for (auto i = 0; i < Size(); i++) {
      if (items[i].IsValid()) {
        items[i].Update();
        if (callback) {
          callback(items[i], data);
        }
        if (!items[i].IsValid()) {
          RemoveAt(i);
        }
      }
    }
  }
  void DrawAll()
  {
    for (const auto& item : items) {
      if (item.IsValid()) {
        item.Draw();
      }
    }
  }
  void RemoveAt (size_t index)
  {
    if (index >= ElementCount) {
      return;
    }
    items[index].Invalidate();
    count_--;
  }
  size_t Count() const
  {
    return count_;
  }
private:
  size_t count_ = 0;
};
