#include <Arduino.h>
#include <ctime>

#include "lighting.h"
#include "pins/pins.h"

typedef struct {
  bool red;
  bool green;
  bool blue;
} light;

void set_lights(int pins[3], light light_val) {
  digitalWrite(pins[0], !light_val.red);
  digitalWrite(pins[1], !light_val.green);
  digitalWrite(pins[2], !light_val.blue);
}

void Lighting::invertIndicatorLeft() {
  indicator_left = !indicator_left;
  changed = true;
}
void Lighting::invertIndicatorRight() {
  indicator_right = !indicator_right;
  changed = true;
}
void Lighting::invertReverse() {
  reverse = !reverse;
  changed = true;
}

void Lighting::setLighting(int brightness) {
  if (last_light_change == 0 || clock() - last_light_change >= 500 || changed) {
    last_light_change = clock();
    changed = false;
  } else
    return;

  bool is_night = brightness <= 200;

  light front_left = {false, false, false};
  light front_right = front_left;
  light rear_left = front_left;
  light rear_right = front_left;

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

  set_lights(lightPins[0], front_left);
  set_lights(lightPins[1], front_right);
  set_lights(lightPins[2], rear_left);
  set_lights(lightPins[3], rear_right);
}