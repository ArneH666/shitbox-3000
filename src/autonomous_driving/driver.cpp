#include <Arduino.h>

#include "driver.h"
#include "../steering/steering.h"
#include "../pins/pins.h"

Driver::Driver(Lighting lighting, Motor motor) {
  m_lighting = lighting;
  m_motor = motor;
}

void Driver::drive(Distances distances) {
  if (distances.front > 50) {
    setSteering(90);
    m_motor.setDirection('F');
    m_motor.drive();
  } else if (distances.front > 20) {
    setSteering(135);
    m_motor.setDirection('F');
    m_motor.drive();
  } else {
    setSteering(45);
    m_motor.setDirection('R');
    m_motor.drive();
    m_lighting.setReverse(true);
    int light_val = analogRead(lightSensorPin);
    m_lighting.setLighting(light_val);
    delay(1000);
    m_lighting.setReverse(false);
  }
}
