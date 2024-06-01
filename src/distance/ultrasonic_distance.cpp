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
  unsigned long duration_front = pulseIn(ultrasonic_sensor_pins[0], HIGH);
  delay(25);
  call_trig();
  unsigned long duration_left = pulseIn(ultrasonic_sensor_pins[1], HIGH);
  delay(25);

  dists.front = floor(duration_front * 0.0344 / 2);
  dists.left = floor(duration_left * 0.0344 / 2);
  return dists;
}
