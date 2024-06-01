#include <Arduino.h>

#include "pins/pins.h"
#include "lighting/lighting.h"
#include "bluetooth/bluetooth.h"
#include "distance/ultrasonic_distance.h"
#include "electric_motor/motor.h"
#include "steering/steering.h"
#include "autonomous_driving/driver.h"

Lighting lighting;
Motor motor;
Bluetooth bluetooth = {};
Driver driver(lighting, motor);

bool autonomous_driving = false;

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

  pinMode(13, OUTPUT);
  ledcSetup(0, 50, 12);
  ledcAttachPin(13, 0);
}

void loop() {
  receive_bluetooth_messages();

  int light_val = analogRead(lightSensorPin);
  lighting.setLighting(light_val);

  if (autonomous_driving) {
    Distances dist = UltrasonicDistance::get_distances();
    Serial.println(dist.front);
    driver.drive(dist);
  } else {
    motor.drive();
  }

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
  } else if (msg.startsWith("steering:")) {
    int val = map(msg.substring(9).toInt(), -100, 100, 45, 135);
    setSteering(val);
  } else if (msg.startsWith("direction:")) {
    motor.setDirection(msg[10]);
  } else if (msg == "autonomous") {
    autonomous_driving = !autonomous_driving;
    if (!autonomous_driving) {
      motor.setDirection('S');
      setSteering(90);
    }
  }
}
