#include <Arduino.h>
#include "lighting/lighting.h"


typedef struct {
    bool red;
    bool green;
    bool blue;
} light_value;


int LIGHT_SENSOR_PIN = 4;

int FRONT_LEFT[] = {16, 17, 5};
int FRONT_RIGHT[] = {0, 2, 15};
int REAR_LEFT[] = {26, 33, 32};
int REAR_RIGHT[] = {27, 14, 12};

bool indicator_left = true;
bool indicator_right = true;
bool indicated = false;

int input_pins[] = {LIGHT_SENSOR_PIN};
int output_pins[] = {
    FRONT_LEFT[0], FRONT_LEFT[1], FRONT_LEFT[2],
    FRONT_RIGHT[0], FRONT_RIGHT[1], FRONT_RIGHT[2],
    REAR_LEFT[0], REAR_LEFT[1], REAR_LEFT[2],
    REAR_RIGHT[0], REAR_RIGHT[1], REAR_RIGHT[2]
};

void set_lighting();
void set_lights(int[3], light_value);

void setup() {
    Serial.begin(9600);
    for (int input_pin : input_pins) {
        pinMode(input_pin, INPUT);
    }
    for (int output_pin : output_pins) {
        pinMode(output_pin, OUTPUT);
    }
}

void loop() {
    set_lighting();
    delay(500);
}

void set_lighting() {
    int lightValue = analogRead(LIGHT_SENSOR_PIN);
    Serial.println(lightValue);

    bool is_night = lightValue <= 100;

    light_value front_left = {false, false, false};
    light_value front_right = {false, false, false};
    light_value rear_left = {false, false, false};
    light_value rear_right = {false, false, false};


    if (is_night) {
        front_left = {true, true, true};
        front_right = {true, true, true};
        rear_left = {true, false, false};
        rear_right = {true, false, false};
    }

    if (indicator_left && !indicated) {
        front_left = {true, true, false};
        rear_left = {true, true, false};
    } else if (indicator_left && indicated && is_night) {
        front_left = {true, true, true};
        rear_right = {true, false, false};
    }

    if (indicator_right && !indicated) {
        front_right = {true, true, false};
        rear_right = {true, true, false};
    } else if (indicator_right && indicated && is_night) {
        front_right = {true, true, true};
        rear_right = {true, false, false};
    }

    if (indicator_left || indicator_right) {
        indicated = !indicated;
    } else {
        indicated = false;
    }

    set_lights(FRONT_LEFT, front_left);
    set_lights(FRONT_RIGHT, front_right);
    set_lights(REAR_LEFT, rear_left);
    set_lights(REAR_RIGHT, rear_right);
}

void set_lights(int led_pins[3], light_value led_values) {
    digitalWrite(led_pins[0], !led_values.red);
    digitalWrite(led_pins[1], !led_values.green);
    digitalWrite(led_pins[2], !led_values.blue);
}
