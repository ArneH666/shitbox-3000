#include <Arduino.h>
#include <list>

int LIGHT_SENSOR_PIN 4;

int FRONT_LEFT[] = {16, 17, 5};
int FRONT_RIGHT[] = {0, 2, 15};
int REAR_LEFT[] = {26, 33, 32};
int REAR_RIGHT[] = {27, 14, 12};

int input_pins[] = {LIGHT_SENSOR_PIN};
int output_pins[] = {
    FRONT_LEFT[0], FRONT_LEFT[1], FRONT_LEFT[2],
    FRONT_RIGHT[0], FRONT_RIGHT[1], FRONT_RIGHT[2],
    REAR_LEFT[0], REAR_LEFT[1], REAR_LEFT[2],
    REAR_RIGHT[0], REAR_RIGHT[1], REAR_RIGHT[2]
};

void setup() {
    Serial.begin(9600);
    for (int i = 0; i < 1; i++) {
        pinMode(input_pins[i], INPUT);
    }
    for (int i = 0; i < sizeof(output_pins) / sizeof(output_pins[0]); i++) {
        pinMode(output_pins[i], OUTPUT);
    }
}

void loop() {
    set_lighting();
    delay(500);
}

void set_lighting() {
    int lightValue = analogRead(LIGHT_SENSOR_PIN);
    // Serial.println(lightValue);

    if (lightValue < 100) {
        is_day = false;
    } else {
        is_day = true;
    }

    bool red_fl = false;
    bool red_fr = false;
    bool red_rl = false;
    bool red_rr = false;
    bool green_fl = false;
    bool green_fr = false;
    bool green_rl = false;
    bool green_rr = false;
    bool blue_fl = false;
    bool blue_fr = false;
    bool blue_rl = false;
    bool blue_rr = false;

    if (is_day) {
        red_fl = false;
        green_fl = false;
        blue_fl = false;
        red_fr = false;
        green_fr = false;
        blue_fr = false;
        red_rl = false;
        green_rl = false;
        blue_rl = false;
        red_rr = false;
        green_rr = false;
        blue_rr = false;
    } else {
        red_fl = true;
        green_fl = true;
        blue_fl = true;
        red_fr = true;
        green_fr = true;
        blue_fr = true;
        red_rl = true;
        green_rl = false;
        blue_rl = false;
        red_rr = true;
        green_rr = false;
        blue_rr = false;
    }

    // Left LEDs
    if (indicator_left && !indicated) {
        red_fl = true;
        green_fl = true;
        blue_fl = false;
        red_rl = true;
        green_rl = true;
        blue_rl = false;
    } else if (indicator_left && indicated && is_day) {
        red_fl = false;
        green_fl = false;
        blue_fl = false;
        red_rl = false;
        green_rl = false;
        blue_rl = false;
    } else if (indicator_left && indicated && !is_day) {
        red_fl = true;
        green_fl = true;
        blue_fl = true;
        red_rl = true;
        green_rl = false;
        blue_rl = false;
    }

    // Right LED
    if (indicator_right && !indicated) {
        red_fr = true;
        green_fr = true;
        blue_fr = false;
        red_rr = true;
        green_rr = true;
        blue_rr = false;
    } else if (indicator_right && indicated && is_day) {
        red_fr = false;
        green_fr = false;
        blue_fr = false;
        red_rr = false;
        green_rr = false;
        blue_rr = false;
    } else if (indicator_right && indicated && !is_day) {
        red_fr = true;
        green_fr = true;
        blue_fr = true;
        red_rr = true;
        green_rr = false;
        blue_rr = false;
    }

    if (indicator_left || indicator_right) {
        indicated = !indicated;
    } else {
        indicated = false;
    }

    set_front_left_led(red_fl, green_fl, blue_fl);
    set_front_right_led(red_fr, green_fr, blue_fr);
    set_rear_left_led(red_rl, green_rl, blue_rl);
    set_rear_right_led(red_rr, green_rr, blue_rr);
}

void set_front_left_led(bool r, bool g, bool b) {
    digitalWrite(RED_FL, !r);
    digitalWrite(GREEN_FL, !g);
    digitalWrite(BLUE_FL, !b);
}

void set_front_right_led(bool r, bool g, bool b) {
    digitalWrite(RED_FR, !r);
    digitalWrite(GREEN_FR, !g);
    digitalWrite(BLUE_FR, !b);
}

void set_rear_left_led(bool r, bool g, bool b) {
    digitalWrite(RED_RL, !r);
    digitalWrite(GREEN_RL, !g);
    digitalWrite(BLUE_RL, !b);
}

void set_rear_right_led(bool r, bool g, bool b) {
    digitalWrite(RED_RR, !r);
    digitalWrite(GREEN_RR, !g);
    digitalWrite(BLUE_RR, !b);
}