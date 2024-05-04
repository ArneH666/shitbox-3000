#include <Arduino.h>

#include "pins/pins.h"
#include "lighting/lighting.h"


Lighting lighting;


void setup() {
    Serial.begin(9600);
    lighting.indicator_left = true;
    lighting.indicator_right = true;
    lighting.reverse = true;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 3; j++)
            pinMode(lightPins[i][j], OUTPUT);
}

void loop() {
    int light_val = analogRead(lightSensorPin);

    lighting.set_lighting(light_val);
    delay(500);
}