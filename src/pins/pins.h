#ifndef SHITBOX_3000_PINS_H
#define SHITBOX_3000_PINS_H

typedef struct Light {
  int red_pin;
  int green_pin;
  int blue_pin;
} Light;

extern const int LIGHT_SENSOR_PIN;

extern const int ULTRASONIC_SENSOR_PIN;
extern const int ULTRASONIC_TRIGGER_PIN;

extern const Light LIGHT_PINS[4];

extern const int MOTOR_PINS[2];

extern const int STEERING_SERVO_CHANNEL;

extern void setPinModes();
extern void setPWMSignals();

#endif //SHITBOX_3000_PINS_H
