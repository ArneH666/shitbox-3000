#include <Arduino.h>

#include "driver.h"
#include "../steering/steering.h"

Driver::Driver(Lighting lighting, Motor motor) {
  m_lighting = lighting;
  m_motor = motor;
}

void Driver::drive(int distance_front) {
  if (m_last_reverse_step != 0 ||
      millis() - m_last_reverse_step < 500) {
    Driver::driveBackwards();
  } else {
    m_last_reverse_step = 0;
    m_lighting.setReverse(false);
  }

  if (distance_front > 50) {
    driveForward();
  } else if (distance_front > 20) {
    AvoidObstacle();
  } else {
    driveBackwards();
    m_last_reverse_step = millis();
  }
}

void Driver::driveForward() {
  setSteering(90);
  m_motor.setDirection('F');
  m_motor.drive();
}

void Driver::AvoidObstacle() {
  setSteering(135);
  m_motor.setDirection('F');
  m_motor.drive();
}

void Driver::driveBackwards() {
  setSteering(45);
  m_motor.setDirection('R');
  m_motor.drive();
  m_lighting.setReverse(true);
}
