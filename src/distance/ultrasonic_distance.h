#ifndef SHITBOX_3000_ULTRASONIC_DISTANCE_H
#define SHITBOX_3000_ULTRASONIC_DISTANCE_H

typedef struct {
  unsigned long front;
  unsigned long left;
  unsigned long right;
  unsigned long back;
} Distances;

class UltrasonicDistance {
 public:
  static Distances get_distances();
};

#endif //SHITBOX_3000_ULTRASONIC_DISTANCE_H
