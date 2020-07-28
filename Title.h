#pragma once
#include "Globals.h"
#include "HiScore.h"

extern Arduboy2 arduboy;

const unsigned char PROGMEM TitleSprite[] =
{
  128,64,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80,
  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80,
  0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00,
  0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80,
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
  0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
  0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80,
  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc,
  0xff, 0xff, 0xff, 0x07, 0xff, 0xff, 0xff, 0xf8,
  0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
  0xff, 0x87, 0x87, 0xff, 0xff, 0xff, 0xff, 0xfc,
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x07, 0x07, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00,
  0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
  0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
  0x7e, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xc7, 0xdf,
  0x9f, 0x1f, 0x1f, 0x1e, 0x00, 0x00, 0x00, 0xff,
  0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
  0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff,
  0xff, 0xff, 0xff, 0x87, 0x87, 0xff, 0xff, 0xff,
  0xff, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0xff,
  0xff, 0xff, 0xf1, 0xf0, 0xf1, 0xff, 0xff, 0xff,
  0xfe, 0xc0, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
  0xff, 0x07, 0x07, 0xff, 0xff, 0xff, 0xfd, 0xf8,
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
  0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
  0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
  0xe0, 0xe0, 0xe1, 0xe3, 0xe7, 0x0f, 0x0f, 0x1f,
  0xff, 0xff, 0xfe, 0xfc, 0xf8, 0x00, 0x00, 0xff,
  0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
  0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff,
  0xff, 0xff, 0xff, 0x07, 0x07, 0xff, 0xff, 0xfe,
  0xfe, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f,
  0x0f, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f,
  0x0f, 0x0f, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f,
  0x0f, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
  0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
  0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x07, 0x03, 0x00,
  0x00, 0x00, 0x01, 0x03, 0x07, 0xcf, 0x0f, 0x0f,
  0x0f, 0x0f, 0x0f, 0x07, 0x07, 0x01, 0x00, 0x00,
  0x01, 0x07, 0x07, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
  0x0f, 0x0f, 0x07, 0x07, 0x03, 0x00, 0x00, 0x01,
  0x03, 0x07, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
  0x07, 0x07, 0x01, 0x00, 0x00, 0x00, 0x0f, 0x0f,
  0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
  0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xfe, 0x80,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x10, 0x10, 0x10, 0x20, 0x20, 0x20, 0x30,
  0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
  0x90, 0x90, 0x90, 0x90, 0x90, 0x30, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x60, 0x40, 0xc0,
  0x80, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
  0xc0, 0x00, 0x20, 0x20, 0x20, 0x20, 0x60, 0x70,
  0x70, 0x70, 0x70, 0xf0, 0xff, 0xff, 0xff, 0xff,
  0xf0, 0x70, 0x70, 0x70, 0x70, 0x60, 0x20, 0x20,
  0xa0, 0xa0, 0x80, 0x80, 0x80, 0x40, 0x60, 0x20,
  0x20, 0x60, 0x40, 0xc0, 0x80, 0x80, 0x80, 0x80,
  0xc0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
  0x40, 0x40, 0x60, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x60, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
  0x40, 0x40, 0x40, 0x40, 0x60, 0x20, 0x30, 0x10,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02,
  0x02, 0x06, 0x04, 0x0c, 0x08, 0x08, 0x08, 0x18,
  0x10, 0x10, 0x30, 0x60, 0xc0, 0x88, 0x08, 0x08,
  0x91, 0x91, 0x91, 0x05, 0x09, 0xc9, 0xf1, 0x99,
  0xed, 0x35, 0x96, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xb6, 0x35, 0xed, 0xd9, 0x71, 0xc5, 0x05,
  0x65, 0x25, 0x85, 0x81, 0x9c, 0x84, 0x22, 0x22,
  0x20, 0x20, 0xa0, 0xa0, 0x80, 0xc0, 0x40, 0x40,
  0x40, 0x60, 0x20, 0x30, 0x10, 0x10, 0x10, 0x18,
  0x08, 0x0c, 0x04, 0x04, 0x06, 0x02, 0x03, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xc0, 0xfc, 0xff, 0xff, 0xfd,
  0xf6, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xfb, 0xf6, 0xfd, 0xff, 0xff, 0xfc,
  0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

class Title
{
public:
  void DisplayHiScores()
  {
    currentState_ = State::HiScores;
    lastState_ = State::Size;
  }
  
  void Update()
  {
    bool firstTime = (currentState_ != lastState_);
    lastState_ = currentState_;
  
    switch (currentState_) {
      case State::Title:
        if (firstTime) {
          screenTimeoutMS_ = millis();
          flashTimerMS_ = millis();
          hidden_ = false;
        }
        
        if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) {
            currentState_ = State::Game;
        }
        
        if ((millis() - flashTimerMS_) > 500) {
          flashTimerMS_ = millis();
          hidden_ = !hidden_;
        }
        
        if (currentState_ == lastState_) {
          if ((millis() - screenTimeoutMS_) > 5000) {
            currentState_ = State::HiScores;
          }
        }
        
        Draw();
        break;
      case State::Game:
        break;
      case State::HiScores:
        if (firstTime) {
          screenTimeoutMS_ = millis();
        }
        HiScores::DrawHallOfFame(arduboy);
        if ((millis() - screenTimeoutMS_) > 5000) {
          currentState_ = State::Title;
        }
        if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) {
          currentState_ = State::Title;
        }
        break;
      case State::Size:
        break;
    }
  }

  void Draw()
  {
    Sprites::drawOverwrite(0, 0, TitleSprite, 0);

    if (!hidden_) {
      arduboy.setCursor(90,33);
      arduboy.print("A or B");
    }
  }

  bool IsPlayingGame() const
  {
    return currentState_ == State::Game;
  }

private:
  enum class State {
    Title,
    Game,
    HiScores,
    Size
  };
  
  long unsigned flashTimerMS_ = millis();
  long unsigned screenTimeoutMS_ = millis();
  State currentState_ = State::Title;
  State lastState_ = State::Size;
  bool hidden_ = false;
};
