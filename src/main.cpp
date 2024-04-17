#include <Arduino.h>

#define LIGHT_SENSOR_PIN 4
#define RED_PIN_1 26
#define RED_PIN_2 32
#define GREEN_PIN_1 27
#define GREEN_PIN_2 33
#define BLUE_PIN_1 12
#define BLUE_PIN_2 25

bool is_day = false;
bool indicator_left = true;
bool indicator_right = true;
bool indicated = false;

void set_lighting();
void set_front_left_led(bool r, bool g, bool b);
void set_front_right_led(bool r, bool g, bool b);

void setup() {
    Serial.begin(9600);
    pinMode(LIGHT_SENSOR_PIN, INPUT);
    pinMode(RED_PIN_1, OUTPUT);
    pinMode(GREEN_PIN_1, OUTPUT);
    pinMode(BLUE_PIN_1, OUTPUT);
    pinMode(RED_PIN_2, OUTPUT);
    pinMode(GREEN_PIN_2, OUTPUT);
    pinMode(BLUE_PIN_2, OUTPUT);
}

void loop() {
    set_lighting();
    Serial.println("X");
    delay(500);
}

void set_lighting() {
    int lightValue = analogRead(LIGHT_SENSOR_PIN);
    Serial.println(lightValue);
    lightValue = 0;

    if (lightValue < 100) {
        is_day = false;
    } else {
        is_day = true;
    }

    bool red_1 = false;
    bool red_2 = false;
    bool green_1 = false;
    bool green_2 = false;
    bool blue_1 = false;
    bool blue_2 = false;

    if (is_day) {
        red_1 = false;
        green_1 = false;
        blue_1 = false;
        red_2 = false;
        green_2 = false;
        blue_2 = false;
    } else {
        red_1 = true;
        green_1 = true;
        blue_1 = true;
        red_2 = true;
        green_2 = true;
        blue_2 = true;
    }

    // Left LED
    if (indicator_left && !indicated) {
        red_1 = true;
        green_1 = true;
        blue_1 = false;
    } else if (indicator_left && indicated && is_day) {
        red_1 = false;
        green_1 = false;
        blue_1 = false;
    } else if (indicator_left && indicated && !is_day) {
        red_1 = true;
        green_1 = true;
        blue_1 = true;
    }

    // Right LED
    if (indicator_right && !indicated) {
        red_2 = true;
        green_2 = true;
        blue_2 = false;
    } else if (indicator_right && indicated && is_day) {
        red_2 = false;
        green_2 = false;
        blue_2 = false;
    } else if (indicator_right && indicated && !is_day) {
        red_2 = true;
        green_2 = true;
        blue_2 = true;
    }

    indicated = !indicated;

    set_front_left_led(red_1, green_1, blue_1);
    set_front_right_led(red_2, green_2, blue_2);
    // delay(500);
}

void set_front_left_led(bool r, bool g, bool b) {
    digitalWrite(RED_PIN_1, r);
    digitalWrite(GREEN_PIN_1, g);
    digitalWrite(BLUE_PIN_1, b);
}

void set_front_right_led(bool r, bool g, bool b) {
    digitalWrite(RED_PIN_2, r);
    digitalWrite(GREEN_PIN_2, g);
    digitalWrite(BLUE_PIN_2, b);
}