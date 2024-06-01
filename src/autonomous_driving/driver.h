#ifndef SHITBOX_3000_SRC_AUTONOMOUS_DRIVING_DRIVER_H_
#define SHITBOX_3000_SRC_AUTONOMOUS_DRIVING_DRIVER_H_

#include "../lighting/lighting.h"
#include "../electric_motor/motor.h"
#include "../distance/ultrasonic_distance.h"

class Driver {
 public:
  Driver(Lighting, Motor);
  void drive(Distances);
 private:
  Lighting m_lighting;
  Motor m_motor;
  UltrasonicDistance m_distance;
};

#endif //SHITBOX_3000_SRC_AUTONOMOUS_DRIVING_DRIVER_H_
