#include <Arduino.h>

#include "steering.h"

void setSteering(int angle) {
  int turn_angle = 102.4 + angle * 2.161 + 0.5;
  ledcWrite(0, turn_angle);
}
