#include <Servo.h>
#include "track_test.h"

const int ANGLE_DELTA = 2;
const int MAX_DISTANCE_DIFFERENCE = 8;
const int MIN_MEASURE_DISTANCE = 3;
const int MAX_MEASURE_DISTANCE = 60;
const int SERVO_PIN = 9;

US_SENSOR leftSensor = { 8, 7 }; //triggerPin, echoPin
US_SENSOR rightSensor = { 13, 12 }; //triggerPin, echoPin

Servo servo;
int servoPos;

void setup() {
  Serial.begin(9600);

  initSensor(&leftSensor);
  initSensor(&rightSensor);

  servo.attach(SERVO_PIN);
  servoPos = 90;
  moveServo(servoPos);
}

void initSensor(US_SENSOR *sensor) {
  pinMode(sensor->triggerPin, OUTPUT);
  pinMode(sensor->echoPin, INPUT);
  digitalWrite(sensor->triggerPin, LOW);
  
  sensor->currentDistance = 0;
  sensor->previousDistance = 0;
}

void loop() {
  measureDistance(&leftSensor);
  delay(50);
  measureDistance(&rightSensor);
  delay(50);

  Serial.print(leftSensor.currentDistance);
  Serial.print(" - ");
  Serial.print(rightSensor.currentDistance);

  hasToMove();  
  
  Serial.println();
}

void measureDistance(US_SENSOR *sensor) {
  sensor->previousDistance = sensor->currentDistance;

  digitalWrite(sensor->triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensor->triggerPin, LOW);
  long pulseDuration = pulseIn(sensor->echoPin, HIGH);
  sensor->currentDistance = microsecondsToCentimeters(pulseDuration);

  sensor->objectDetected = true;
  if (sensor->currentDistance < MIN_MEASURE_DISTANCE || sensor->currentDistance > MAX_MEASURE_DISTANCE) {
    sensor->objectDetected = false;
    sensor->currentDistance = 0;
    sensor->previousDistance = 0;
  }
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 58;
}

void hasToMove() {
  bool bothDetected = leftSensor.objectDetected && rightSensor.objectDetected;

  if (bothDetected && abs(leftSensor.currentDistance - rightSensor.currentDistance) < MAX_DISTANCE_DIFFERENCE) {
    Serial.print("  -->  LOCK ON OBJECT");
    return;
  }
  if (bothDetected && leftSensor.currentDistance < rightSensor.currentDistance) {
    moveLeft();
    return;
  }
  if (bothDetected && rightSensor.currentDistance < leftSensor.currentDistance) {
    moveRight();
    return;
  }
  if (leftSensor.objectDetected && !rightSensor.objectDetected) {
    moveLeft();
    return;
  }
  if (rightSensor.objectDetected && !leftSensor.objectDetected) {
    moveRight();
    return;
  }

  Serial.print("  --> NOTHING DETECTED");
}

void moveLeft() {
  Serial.print("  -->  MOVE LEFT");
  servoPos += servoPos + ANGLE_DELTA;
  moveServo(servoPos);
}

void moveRight() {
  Serial.print("  -->  MOVE RIGHT");
  servoPos = servoPos - ANGLE_DELTA;
  moveServo(servoPos);
}

void moveServo(int pos) {
  if (pos > 179) {
    pos = 179;
  }
  if (pos < 1) {
    pos = 1;
  }
  servo.write(pos);
}