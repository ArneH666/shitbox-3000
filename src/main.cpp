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

void handleBluetoothMessages(String);

void setup() {
  Serial.begin(9600);

  setPinModes();
  setPWMSignals();
}

void loop() {
  String msg = bluetooth.get_message();
  if (msg != "") {
    Serial.println(msg);
    handleBluetoothMessages(msg);
  }

  int light_val = analogRead(LIGHT_SENSOR_PIN);
  lighting.setLighting(light_val);

  if (autonomous_driving) {
    long dist = getDistance();
    driver.drive(dist);
  } else {
    motor.drive();
  }

  delay(1);
}

void handleBluetoothMessages(String msg) {
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
