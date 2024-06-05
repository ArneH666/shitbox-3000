#include <Arduino.h>

#include "steering.h"
#include "../pins/pins.h"

void setSteering(int angle) {
  int turn_angle = 102.4 + angle * 2.161 + 0.5;
  ledcWrite(STEERING_SERVO_CHANNEL, turn_angle);
}
