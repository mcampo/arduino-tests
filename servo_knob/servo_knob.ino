#include <Servo.h> 

const int SERVO_PIN = 9;
const int POT_PIN = 0;

const int POT_MIN_DELTA = 3;

Servo servo;
int potVal = 0;
int prevPotVal = 0;
int servoPos;
 
void setup() 
{ 
  Serial.begin(9600);
  servo.attach(SERVO_PIN);
} 
 
void loop() 
{ 
  potVal = analogRead(POT_PIN);

  if (abs(potVal - prevPotVal) > POT_MIN_DELTA) {
    servoPos = map(potVal, 0, 1023, 0, 179);
    Serial.print(potVal);
    Serial.print(" -> "); 
    Serial.print(servoPos);
    Serial.println();

    servo.write(servoPos);
    delay(15);

    prevPotVal = potVal;
  }

} 
