#ifndef SHITBOX_3000_SRC_ELECTRIC_MOTOR_MOTOR_H_
#define SHITBOX_3000_SRC_ELECTRIC_MOTOR_MOTOR_H_

class Motor {
 public:
  void drive();
  void switch_direction();
 private:
  char direction = 'F';
  char changed = 'Y';
};

#endif //SHITBOX_3000_SRC_ELECTRIC_MOTOR_MOTOR_H_
