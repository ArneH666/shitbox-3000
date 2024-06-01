#include <Arduino.h>

#include "motor.h"
#include "../pins/pins.h"

void Motor::drive() {
  switch (changed) {
    case 'N':
      return;
    default:
      changed = 'N';
  }
  switch (direction) {
    case 'F':
      Serial.println("Forward");
      digitalWrite(motorPins[0], HIGH);
      digitalWrite(motorPins[1], LOW);
      break;
    case 'R':
      Serial.println("Reverse");
      digitalWrite(motorPins[0], LOW);
      digitalWrite(motorPins[1], HIGH);
      break;
  }
}

void Motor::switch_direction() {
  Serial.println("Switching direction");
  direction = (direction == 'F') ? 'R' : 'F';
}
