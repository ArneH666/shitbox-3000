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
bool indicator_right = false;
bool indicated = false;

void set_lighting();

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
    delay(50);
}

void set_lighting() {
    int lightValue = analogRead(LIGHT_SENSOR_PIN);
    Serial.println(lightValue);

    bool red_1 = false;
    bool red_2 = false;
    bool green_1 = false;
    bool green_2 = false;
    bool blue_1 = false;
    bool blue_2 = false;

    if (lightValue < 100) {
        red_1 = true;
        green_1 = true;
        blue_1 = true;
        red_2 = true;
        green_2 = true;
        blue_2 = true;
    } else {
        red_1 = false;
        green_1 = false;
        blue_1 = false;
        red_2 = false;
        green_2 = false;
        blue_2 = false;
    }

    // Left LED
    if (indicator_left && !indicated) {
        red_1 = true;
        green_1 = true;
        blue_1 = false;
        indicated = true;
    } else if (!indicator_left) {
        red_1 = false;
        green_1 = false;
        blue_1 = false;
        indicated = false;
    } else if (indicator_left && indicated) {
        red_1 = false;
        green_1 = false;
        blue_1 = false;
        indicated = false;
    }

    digitalWrite(RED_PIN_1, red_1);
    digitalWrite(GREEN_PIN_1, green_1);
    digitalWrite(BLUE_PIN_1, blue_1);
    digitalWrite(RED_PIN_2, red_2);
    digitalWrite(GREEN_PIN_2, green_2);
    digitalWrite(BLUE_PIN_2, blue_2);
    delay(500);
}