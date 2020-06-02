#include "Player.h"
#include "Game.h"

extern Game game;

  void Sub::Update()
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

      if ((millis() - lastBubble) >= bubblePeriod) {
        lastBubble = millis();
        bubblePeriod = random(750);
        game.bubbles.Add(Bubble(x_-1, y_+1));
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
