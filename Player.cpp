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
    
    if (valid_) {
#if !TEST_COLLISIONS
      static const int Momentum = 3;
      static const int MaxLiftSpeed = 10;
      static const int MaxSinkSpeed = 10;

      bool diving = false;
      if (arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON)) {
        vY_ += Momentum;
        diving = true;
        if (vY_ > MaxSinkSpeed) {
          vY_ = MaxSinkSpeed;
        }
        else {
          bubblePeriod >>= 1;
        }
      }
      else {
        vY_ -= Momentum;
        if (vY_ < -MaxLiftSpeed) {
          vY_ = -MaxLiftSpeed;
        }
      }

      y_ += vY_;

      if ((millis() - lastBubble) >= bubblePeriod) {
        lastBubble = millis();
        bubblePeriod = random(500, 1000);
        if (diving) {
          // Add bubble on top of sub.
          game.bubbles.Add(Bubble((x_/10)+1, (y_/10)+1));
        }
        else {
          // Add bubble behind sub
          game.bubbles.Add(Bubble((x_/10)-1, (y_/10)+1));
        }
      }
      if ((millis() - lastMove) >= 100) {
        lastMove = millis();
        x_ += 1;
      }
#else 
      if (arduboy.pressed(LEFT_BUTTON)) {
        x_ -= 5;
      }
      if (arduboy.pressed(RIGHT_BUTTON)) {
        x_ += 5;
      }
      if (arduboy.pressed(UP_BUTTON)) {
        y_ -= 5;
      }
      if (arduboy.pressed(DOWN_BUTTON)) {
        y_ += 5;
      }
#endif
    }
    else {
      if (!Arduboy2Base::collide(tempRect, BoundBottom)) {
        y_ += 3;
        bubblePeriod >>= 1;
      }
      if ((millis() - lastBubble) >= bubblePeriod) {
        lastBubble = millis();
        bubblePeriod = random(300, 800);
        game.bubbles.Add(Bubble((x_/10) + random(0, 8), (y_/10) + random(0, 2)));
      }
    }
  }
