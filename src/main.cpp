#include <Arduino.h>

#include "pins/pins.h"
#include "lighting/lighting.h"
#include "bluetooth/bluetooth.h"
#include "distance/ultrasonic_distance.h"

Lighting lighting;
UltrasonicDistance distance;
Bluetooth bluetooth = {};

void setup() {
  Serial.begin(9600);

  bluetooth.BTSerial.begin("Shitbox-3000");

  for (auto &lightPin : lightPins) {
    for (int j : lightPin) {
      pinMode(j, OUTPUT);
    }
  }

  pinMode(ultrasonic_trigger_pin, OUTPUT);

  for (int pin : inputPins) {
    pinMode(pin, INPUT);
  }
}

void loop() {
  digitalWrite(ultrasonic_trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonic_trigger_pin, LOW);
  Serial.println(digitalRead(ultrasonic_sensor_pins[0]));

//  receive_bluetooth_messages();
//
//  int light_val = analogRead(lightSensorPin);
//
//  Distances dist = distance.get_distances();
//
////  Serial.println(dist.front);
//
//  lighting.setLighting(light_val);
  delay(1);
}

void receive_bluetooth_messages() {
  String msg = bluetooth.get_message();
  if (msg != "") {
    Serial.println(msg);
  }

  if (msg == "ind_left") {
    lighting.invertIndicatorLeft();
  } else if (msg == "ind_right") {
    lighting.invertIndicatorRight();
  } else if (msg == "reverse") {
    lighting.invertReverse();
  }
}
