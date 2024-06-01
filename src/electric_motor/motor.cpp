#include <Arduino.h>

#include "motor.h"
#include "../pins/pins.h"

void Motor::drive() {
//  if (!changed) {
//    return;
//  }
  changed = false;
  switch (direction) {
    case 'F':Serial.println("Forward");
      digitalWrite(motorPins[0], HIGH);
      digitalWrite(motorPins[1], LOW);
      break;
    case 'R':Serial.println("Reverse");
      digitalWrite(motorPins[0], LOW);
      digitalWrite(motorPins[1], HIGH);
      break;
    case 'S':Serial.println("Stop");
      digitalWrite(motorPins[0], LOW);
      digitalWrite(motorPins[1], LOW);
      break;
  }
}

void Motor::setDirection(char dir) {
  Serial.println("Setting direction");
  direction = dir;
  changed = true;
}
