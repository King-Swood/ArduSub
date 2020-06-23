#pragma once
#include "Globals.h"

#define HISCORE_NAME_LENGTH (30)
typedef struct {
  char name[HISCORE_NAME_LENGTH];
  unsigned seconds;
}HiScore;

class Arduboy2;

class HiScores {
public:
  static const HiScore Records[];
  static void DrawHallOfFame(Arduboy2 &arduboy);
};
