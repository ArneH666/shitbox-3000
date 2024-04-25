#include <Arduino.h>

#define LIGHT_SENSOR_PIN 4
#define RED_FL 27
#define RED_FR 26
#define RED_RL 15
#define RED_RR 17
#define GREEN_FL 14
#define GREEN_FR 33
#define GREEN_RL 16
#define GREEN_RR 5
#define BLUE_FL 12
#define BLUE_FR 32
#define BLUE_RL 0
#define BLUE_RR 19

int input_pins[] = {LIGHT_SENSOR_PIN};
int output_pins[] = {RED_FL, GREEN_FL, BLUE_FL, RED_FR, GREEN_FR, BLUE_FR, RED_RL, GREEN_RL, BLUE_RL, RED_RR, GREEN_RR, BLUE_RR};

bool is_day = false;
bool indicator_left = true;
bool indicator_right = true;
bool indicated = false;

void set_lighting();
void set_front_left_led(bool r, bool g, bool b);
void set_front_right_led(bool r, bool g, bool b);
void set_rear_left_led(bool r, bool g, bool b);
void set_rear_right_led(bool r, bool g, bool b);

void setup() {
    Serial.begin(9600);
    for (int i = 0; i < 1; i++) {
        pinMode(input_pins[i], INPUT);
    }
    for (int i = 0; i < 9; i++) {
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