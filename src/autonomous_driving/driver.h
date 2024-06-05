#ifndef SHITBOX_3000_SRC_AUTONOMOUS_DRIVING_DRIVER_H_
#define SHITBOX_3000_SRC_AUTONOMOUS_DRIVING_DRIVER_H_

#include "../lighting/lighting.h"
#include "../electric_motor/motor.h"

class Driver {
 public:
  Driver(Lighting, Motor);
  void drive(int);

 private:
  Lighting m_lighting;
  Motor m_motor;
  unsigned long m_last_reverse_step = 0;

  void driveForward();
  void AvoidObstacle();
  void driveBackwards();
};

#endif //SHITBOX_3000_SRC_AUTONOMOUS_DRIVING_DRIVER_H_
