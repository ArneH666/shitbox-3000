#ifndef SHITBOX_3000_BLUETOOTH_H
#define SHITBOX_3000_BLUETOOTH_H

#include <Arduino.h>
#include <BluetoothSerial.h>

class Bluetooth {
 public:
  Bluetooth();
  String get_message();

 private:
  BluetoothSerial m_bt_serial;
};

#endif //SHITBOX_3000_BLUETOOTH_H
