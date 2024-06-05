#include <Arduino.h>

#include "motor.h"
#include "../pins/pins.h"

void writeMotorDirection(int pin_1_value, int pin_2_value) {
  digitalWrite(MOTOR_PINS[0], pin_1_value);
  digitalWrite(MOTOR_PINS[1], pin_2_value);
}

void Motor::drive() {
  if (!m_changed) {
    return;
  }

  m_changed = false;
  switch (m_direction) {
    case 'F':Serial.println("Forward");
      writeMotorDirection(HIGH, LOW);
      break;
    case 'R':Serial.println("Reverse");
      writeMotorDirection(LOW, HIGH);
      break;
    case 'S':Serial.println("Stop");
      writeMotorDirection(LOW, LOW);
      break;
  }
}

void Motor::setDirection(char dir) {
  m_direction = dir;
  m_changed = true;
}
