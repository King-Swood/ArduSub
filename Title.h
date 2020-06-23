#pragma once
#include "Globals.h"
#include "HiScore.h"

extern Arduboy2 arduboy;

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
    arduboy.setTextSize(2);
    arduboy.setCursor(10, 10);
    arduboy.print("ARDUSUB");
    arduboy.setTextSize(1);
  
    if (!hidden_) {
      arduboy.setCursor(10,35);
      arduboy.print("A or B to Start");
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
