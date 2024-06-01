#include "bluetooth.h"
#include <BluetoothSerial.h>

String Bluetooth::get_message() {
  String msg = "";
  while (BTSerial.available()) {
    char ch = BTSerial.read();
    msg += ch;
  }
  while (msg.indexOf(10) != -1)
    msg.remove(msg.indexOf(10));
  while (msg.indexOf(13) != -1)
    msg.remove(msg.indexOf(13));
  return msg;
}
