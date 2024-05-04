#ifndef SHITBOX_3000_BLUETOOTH_H
#define SHITBOX_3000_BLUETOOTH_H

#include <Arduino.h>
#include <BluetoothSerial.h>

class Bluetooth {
public:
    String get_message();
    BluetoothSerial BTSerial;
};


#endif //SHITBOX_3000_BLUETOOTH_H
