#include <Arduino.h>

#include "ultrasonic_distance.h"
#include "../pins/pins.h"

void call_trig() {
//  digitalWrite(ultrasonic_trigger_pin, LOW);
//  delayMicroseconds(2);
  digitalWrite(ultrasonic_trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonic_trigger_pin, LOW);
}

Distances UltrasonicDistance::get_distances() {
  Distances dists = {};
  call_trig();
  unsigned long duration_front = pulseIn(ultrasonic_sensor_pin, HIGH);

  dists.front = floor(duration_front * 0.0344 / 2);
  return dists;
}
