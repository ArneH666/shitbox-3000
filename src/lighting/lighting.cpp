#include <Arduino.h>
#include <ctime>

#include "lighting.h"
#include "pins/pins.h"

typedef struct {
  bool red;
  bool green;
  bool blue;
} LightValues;

void set_lights(Light led, LightValues light_val) {
  digitalWrite(led.red_pin, !light_val.red);
  digitalWrite(led.green_pin, !light_val.green);
  digitalWrite(led.blue_pin, !light_val.blue);
}

void Lighting::invertIndicatorLeft() {
  indicator_left = !indicator_left;
  changed = true;
}

void Lighting::invertIndicatorRight() {
  indicator_right = !indicator_right;
  changed = true;
}

void Lighting::setReverse(bool state) {
  reverse = state;
  changed = true;
}

void Lighting::setLighting(int brightness) {
  if (last_light_change == 0 || clock() - last_light_change >= 500 || changed) {
    last_light_change = clock();
    changed = false;
  } else {
    return;
  }

  bool is_night = brightness <= 200;

  LightValues front_left = {false, false, false};
  LightValues front_right = front_left;
  LightValues rear_left = front_left;
  LightValues rear_right = front_left;

  if (is_night && !reverse) {
    front_left = {true, true, true};
    front_right = front_left;
    rear_left = {true, false, false};
    rear_right = rear_left;
  } else if (is_night) {
    front_left = {true, false, false};
    front_right = front_left;
    rear_left = {true, true, true};
    rear_right = rear_left;
  } else if (reverse) {
    rear_left = {true, true, true};
    rear_right = rear_left;
  }

  if (indicator_left && !indicated) {
    front_left = {true, true, false};
    rear_left = front_left;
  }

  if (indicator_right && !indicated) {
    front_right = {true, true, false};
    rear_right = front_right;
  }

  if (indicator_left || indicator_right)
    indicated = !indicated;
  else if (indicated)
    indicated = false;

  set_lights(LIGHT_PINS[0], front_left);
  set_lights(LIGHT_PINS[1], front_right);
  set_lights(LIGHT_PINS[2], rear_left);
  set_lights(LIGHT_PINS[3], rear_right);
}