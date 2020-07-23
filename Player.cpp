#include "Player.h"
#include "Game.h"

extern Game game;

const Rect BoundLeft(-WIDTH, -1, WIDTH+5, HEIGHT);
const Rect BoundRight(WIDTH-5, -1, WIDTH, HEIGHT);

void Sub::Update()
{  
  Rect tempRect = BoundingBox();

  if (valid_) {
#if !TEST_COLLISIONS
    static const int Momentum = 3;
    static const int MomentumX = 1;
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

    UpdateBubbles(diving, false);
    if ((millis() - lastMove) >= 100) {
      lastMove = millis();
      x_ += vX_;
      
      if (Arduboy2Base::collide(tempRect, BoundRight) || Arduboy2Base::collide(tempRect, BoundLeft)) {
        if (movingRight) {
          x_ -= 10;
        }
        else {
          x_ += 10;
        }
        movingRight = !movingRight;
        vX_ = -vX_;
      }
    }
#else 
    if (arduboy.pressed(LEFT_BUTTON)) {
      movingRight = false;
      x_ -= 5;
    }
    if (arduboy.pressed(RIGHT_BUTTON)) {
      movingRight = true;
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
    UpdateBubbles(false, true);
  }
}
void Sub::Draw()
{
  int spriteNo = 0;
  if (valid_) {
    spriteNo = movingRight ? 0 : 1;
  }
  else {
    spriteNo = movingRight ? 2 : 3;
  }
  
  Sprites::drawOverwrite(x_/10, y_/10, SubSprite, spriteNo);
    
#if TEST_COLLISIONS
  DrawBoundingBox();
#endif
}

void Sub::UpdateBubbles(bool diving, bool crashed)
{
  if ((millis() - lastBubble) >= bubblePeriod) {
    lastBubble = millis();

    if (crashed) {
      bubblePeriod = random(300, 800);
      game.AddBubble(Bubble((x_/10) + random(0, Width()), (y_/10) + random(0, Height())));
    }
    else {
      bubblePeriod = random(500, 1000);
      if (diving) {
        // Add bubble on top of sub.
        movingRight ? game.AddBubble(Bubble((x_/10)+1, (y_/10)+1)) : game.AddBubble(Bubble((x_/10)+Width()-2, (y_/10)+1));
      }
      else {
        // Add bubble behind sub
        movingRight ? game.AddBubble(Bubble((x_/10)-1, (y_/10)+1)) : game.AddBubble(Bubble((x_/10)+Width(), (y_/10)+1));
      }
    }
  }
  }
