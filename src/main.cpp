#include <Arduino.h>

#include "pins/pins.h"
#include "lighting/lighting.h"
#include "bluetooth/bluetooth.h"


Lighting lighting;
Bluetooth bluetooth = {};


void receive_bluetooth_messages();


void setup() {
    Serial.begin(9600);

    bluetooth.BTSerial.begin("Shitbox-3000");

    for (auto &lightPin: lightPins)
        for (int j: lightPin)
            pinMode(j, OUTPUT);
}

void loop() {
    String msg = bluetooth.get_message();
    if (msg != "") {
        Serial.println(msg);
    }

    if (msg == "ind_left")
        lighting.invertIndicatorLeft();
    else if (msg == "ind_right")
        lighting.invertIndicatorRight();
    else if (msg == "reverse")
        lighting.invertReverse();

    int light_val = analogRead(lightSensorPin);

    lighting.setLighting(light_val);
    delay(1);
}