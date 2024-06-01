#include <Arduino.h>

#include "pins/pins.h"
#include "lighting/lighting.h"
#include "bluetooth/bluetooth.h"
#include "distance/ultrasonic_distance.h"
#include "electric_motor/motor.h"

Lighting lighting;
Motor motor;
Bluetooth bluetooth = {};

void receive_bluetooth_messages();

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

  pinMode(motorPins[0], OUTPUT);
  pinMode(motorPins[1], OUTPUT);
}

void loop() {
  receive_bluetooth_messages();

  int light_val = analogRead(lightSensorPin);
  lighting.setLighting(light_val);

//  Distances dist = UltrasonicDistance::get_distances();
//
//  Serial.print("F:");
//  Serial.print(dist.front);
//  Serial.print(";L:");
//  Serial.println(dist.left);

//  motor.drive();

//  digitalWrite(motorPins[0], HIGH);
//  digitalWrite(motorPins[1], LOW);

  delay(100);
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
    motor.switch_direction();
  }
}
