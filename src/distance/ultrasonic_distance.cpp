#include <Arduino.h>

#include "ultrasonic_distance.h"
#include "../pins/pins.h"

void callTrigger() {
  digitalWrite(ULTRASONIC_TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_TRIGGER_PIN, LOW);
}

long getDistance() {
  callTrigger();
  unsigned long duration_front = pulseIn(ULTRASONIC_SENSOR_PIN, HIGH);

  long front_distance = floor(duration_front * 0.0344 / 2);
  return front_distance;
}
