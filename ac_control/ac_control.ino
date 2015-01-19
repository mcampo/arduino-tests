#include "ac_control.h"

#define IR_LED_PIN 3

//repeat the signal a few times
#define IR_CODE_REPEAT_COUNT 3

SoftwareSerial bluetooth(10, 11); // RX, TX

void setupBluetooth() {
    bluetooth.begin(9600);
    //set name and pin
    bluetooth.write("AT");
    delay(1000);
    bluetooth.write("AT+NAMEAC Control");
    delay(1000);
    bluetooth.write("AT+PIN0000");
    delay(1000);

    //read and discard AT command responses
    while(bluetooth.available()) {
        Serial.print((char)bluetooth.read());
    }
    Serial.println();

    Serial.println("Bluetooth initialized");
}

void setup() {
    //initialize ir led pin
    pinMode(IR_LED_PIN, OUTPUT);

    //Initialize serial
    Serial.begin(9600);
    Serial.println("Serial initialized");

    //Initialize bluetooth
    setupBluetooth();
}

void loop() {
    if (bluetooth.available()) {
        processCommand((char)bluetooth.read());
    }
}

void processCommand(char command) {
    Serial.print("Received command: ");
    Serial.print(command);
    Serial.println();

    switch (command) {
    case 'A':
        Serial.println("Turning AC on");
        sendCode(CODE_AC_ON, CODE_AC_ON_LENGTH);
        break;
    case 'a':
        Serial.println("Turning AC off");
        sendCode(CODE_AC_OFF, CODE_AC_OFF_LENGTH);
        break;
    }
}

// This procedure sends a 38KHz pulse to the IRledPin
// for a certain # of microseconds. We'll use this whenever we need to send codes
void pulseIR(long microsecs) {
    // we'll count down from the number of microseconds we are told to wait

    cli();
    // this turns off any background interrupts

    while (microsecs > 0) {
        // 38 kHz is about 13 microseconds high and 13 microseconds low
        digitalWrite(IR_LED_PIN, HIGH); // this takes about 3 microseconds to happen
        delayMicroseconds(10); // hang out for 10 microseconds, you can also change this to 9 if its not working
        digitalWrite(IR_LED_PIN, LOW);   // this also takes about 3 microseconds
        delayMicroseconds(10); // hang out for 10 microseconds, you can also change this to 9 if its not working

        // so 26 microseconds altogether
        microsecs -= 26;
    }

    sei();
    // this turns them back on
}

void sendCode(int codeSequence[], int codeLength) {
    for (int repeatCount = 0; repeatCount < IR_CODE_REPEAT_COUNT; repeatCount++) {
        for (int codeIndex = 0; codeIndex < codeLength; codeIndex = codeIndex + 2) {
            pulseIR(codeSequence[codeIndex]);
            delayMicroseconds(codeSequence[codeIndex + 1]);
        }
    }
}
