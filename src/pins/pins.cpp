#include <Arduino.h>

#include "pins.h"

const int LIGHT_SENSOR_PIN = 36;

const int ULTRASONIC_SENSOR_PIN = 23;
const int ULTRASONIC_TRIGGER_PIN = 19;

const Light LIGHT_PINS[4] = {
    {16, 17, 5},
    {0, 2, 15},
    {25, 33, 32},
    {27, 14, 12}
};

const int MOTOR_PINS[2] = {4, 22};

const int STEERING_SERVO_CHANNEL = 0;
const int STEERING_SERVO_FREQUENCY = 50;
const int STEERING_SERVO_RESOLUTION = 12;
const int STEERING_SERVO_PIN = 13;

void setPinModes() {
  pinMode(LIGHT_SENSOR_PIN, INPUT);

  pinMode(ULTRASONIC_SENSOR_PIN, INPUT);
  pinMode(ULTRASONIC_TRIGGER_PIN, OUTPUT);

  for (Light led : LIGHT_PINS) {
    pinMode(led.red_pin, OUTPUT);
    pinMode(led.green_pin, OUTPUT);
    pinMode(led.blue_pin, OUTPUT);
  }

  for (int pin : MOTOR_PINS) {
    pinMode(pin, OUTPUT);
  }
}

void setPWMSignals() {
  ledcSetup(STEERING_SERVO_CHANNEL, STEERING_SERVO_FREQUENCY, STEERING_SERVO_RESOLUTION);
  ledcAttachPin(STEERING_SERVO_PIN, STEERING_SERVO_CHANNEL);
}
