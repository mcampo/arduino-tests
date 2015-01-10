#include <Servo.h> 

const int STEP_DELAY = 50;
const int TURN_WAIT = 2000;
 
Servo servo;
int pos;
 
void setup() 
{ 
  servo.attach(9);
} 
 
void loop() 
{ 
  for(pos = 60; pos < 120; pos += 1) 
  {
    servo.write(pos);
    delay(STEP_DELAY);
  }
  delay(TURN_WAIT);
  for(pos = 119; pos > 60; pos-=1)
  {                                
    servo.write(pos);
    delay(STEP_DELAY);
  } 
  delay(TURN_WAIT);
} 
