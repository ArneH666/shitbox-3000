#ifndef SHITBOX_3000_LIGHTING_H
#define SHITBOX_3000_LIGHTING_H

class Lighting {
 public:
  void setLighting(int);

  void invertIndicatorLeft();
  void invertIndicatorRight();
  void setReverse(bool);
 private:
  bool indicator_left = false;
  bool indicator_right = false;
  bool indicated = false;
  bool reverse = false;
  bool changed = false;

  clock_t last_light_change = 0;
};

#endif //SHITBOX_3000_LIGHTING_H
