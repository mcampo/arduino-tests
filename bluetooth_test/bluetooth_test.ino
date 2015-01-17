/*
Modified example from: http://arduino.cc/en/Reference/softwareSerial
 */
#include <SoftwareSerial.h>

#define LED_PIN 3

SoftwareSerial bluetoothSerial(10, 11); // RX, TX
char readChar;

void setup()  
{
  pinMode(LED_PIN, OUTPUT);

  //Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println("Serial initialized");

  //set the data rate for the SoftwareSerial port
  bluetoothSerial.begin(9600);
  bluetoothSerial.println("Bluetooth initialized");

  //set name and pin
  bluetoothSerial.write("AT");
  delay(1000);
  bluetoothSerial.write("AT+NAMEMy BT Device");
  delay(1000);
  bluetoothSerial.write("AT+PIN0000");
  delay(1000);

  digitalWrite(LED_PIN, HIGH);
  delay(300);
  digitalWrite(LED_PIN, LOW);
  delay(300);
  digitalWrite(LED_PIN, HIGH);
  delay(300);
  digitalWrite(LED_PIN, LOW);
}

void loop()
{
  if (bluetoothSerial.available()) {
    readChar = bluetoothSerial.read();
    switch(readChar) {
      case 'A':
        digitalWrite(LED_PIN, HIGH);
        break;
      case 'a':
        digitalWrite(LED_PIN, LOW);
        break;
    }

    Serial.write(readChar);
  }

  if (Serial.available()){
    bluetoothSerial.write(Serial.read());
  }
}