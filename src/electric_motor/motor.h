#ifndef SHITBOX_3000_SRC_ELECTRIC_MOTOR_MOTOR_H_
#define SHITBOX_3000_SRC_ELECTRIC_MOTOR_MOTOR_H_

class Motor {
 public:
  void drive();
  void setDirection(char );
 private:
  char m_direction = 'S';
  bool m_changed = true;
};

#endif //SHITBOX_3000_SRC_ELECTRIC_MOTOR_MOTOR_H_
