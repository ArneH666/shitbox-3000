#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>

#include "pins/pins.h"
#include "lighting/lighting.h"
#include "bluetooth/bluetooth.h"


Lighting lighting;
Bluetooth bluetooth = {};


void receive_bluetooth_messages();


void setup() {
    Serial.begin(9600);

    bluetooth.BTSerial.begin("Shitbox-3000");

    for (auto & lightPin : lightPins)
        for (int j : lightPin)
            pinMode(j, OUTPUT);
}

void loop() {
    String msg = bluetooth.get_message();
    if (msg != "") {
        Serial.println(msg);
        for (char c : msg) {
            int ch = c;
            Serial.print(ch);
            Serial.print(" ");
        }
        Serial.println();
    }

    int light_val = analogRead(lightSensorPin);

    lighting.set_lighting(light_val);
    delay(500);
}