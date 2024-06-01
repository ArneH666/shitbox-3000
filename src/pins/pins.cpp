int lightSensorPin = 36;

int ultrasonic_sensor_pins[] = {4, 18};
int ultrasonic_trigger_pin = 13;

int lightPins[][3] = {
    {16, 17, 5},
    {0, 2, 15},
    {25, 33, 32},
    {27, 14, 12}
};

int motorPins[2] = {18, 19};

int inputPins[] = {lightSensorPin, ultrasonic_sensor_pins[0], ultrasonic_sensor_pins[1]};