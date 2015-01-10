/*
Adafruit Arduino - Lesson 10. Pseudo Thermin
*/
 
int speakerPin = 11;
int photocellPin = 0;
 
void setup()
{
}
 
void loop()
{
  int reading = analogRead(photocellPin);
  int pitch = 200 + reading / 2;
  tone(speakerPin, pitch);
}