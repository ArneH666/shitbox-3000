#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
#include <Arduino.h>
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

String btName = "Shitbox-3000";

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);

    SerialBT.begin(btName);
    Serial.println("The device started, now you can pair it with bluetooth!   Name: " + btName);
}

void loop()
{
    char message;

    if (SerialBT.available())
    {
        message = SerialBT.read();
        Serial.write(message);
    }
}