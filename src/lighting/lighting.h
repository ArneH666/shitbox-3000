#ifndef SHITBOX_3000_LIGHTING_H
#define SHITBOX_3000_LIGHTING_H

class Lighting {
public:
    bool indicator_left = false;
    bool indicator_right = false;
    bool indicated = false;
    bool reverse = false;
    void set_lighting(int);
};

#endif //SHITBOX_3000_LIGHTING_H
