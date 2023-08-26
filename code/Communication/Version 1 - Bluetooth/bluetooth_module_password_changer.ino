//HC-05 bluetooth module name and password setting with Arduino Nano
//To set HC-05 to AT mode, before power up, press and hold reset button on HC-05. AT mode = 2s led blink on HC-05.
//In Serial Monitor, set line ending to “Both NL & CR”.
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(9, 10); // D9 --> HC05 TX, D10 --> HC05 RX

void setup() {
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  BTSerial.begin(38400); // HC-05 default speed in AT command mode
}

void loop() {
  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (BTSerial.available()) Serial.write(BTSerial.read());

  // Keep reading from Arduino Serial Monitor and send to HC-05
  // To test, type AT and press enter. You should see OK in Serial Monitor.
  // To change name, type: AT+NAME=HC05-Sam1. To query name, type AT+NAME?
  // To change password, type: AT+PSWD="1234". Don't forget the double quotes! To query password, type AT+PSWD?
  if (Serial.available()) BTSerial.write(Serial.read());
}