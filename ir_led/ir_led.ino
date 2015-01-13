//From: https://learn.adafruit.com/ir-sensor

int IRledPin =  13;    // LED connected to digital pin 13

//ON, OFF (in microseconds)
int CODE_1[] = {
  4420, 4360,
  560, 1620,
  560, 1620,
  560, 1620,
  560, 520,
  540, 560,
  560, 520,
  560, 520,
  580, 520,
  560, 1620,
  560, 1620,
  560, 1600,
  580, 520,
  560, 520,
  540, 560,
  560, 520,
  560, 520,
  560, 540,
  560, 520,
  560, 1620,
  560, 520,
  580, 500,
  580, 520,
  560, 520,
  580, 520,
  560, 1620,
  560, 1620,
  560, 520,
  560, 1620,
  560, 1620,
  560, 1620,
  560, 1620,
  540, 1640,
  56, 0};

//ON, OFF (in microseconds)
int CODE_AC_ON[] = {
  4300, 4280,
  560, 1580,
  540, 520,
  560, 1580,
  540, 1580,
  540, 520,
  560, 520,
  540, 1580,
  560, 520,
  560, 500,
  560, 1560,
  560, 520,
  540, 520,
  540, 1580,
  560, 1580,
  500, 560,
  560, 1560,
  580, 500,
  540, 520,
  540, 1580,
  560, 1580,
  540, 1580,
  560, 1580,
  540, 1580,
  560, 1580,
  560, 1560,
  540, 1580,
  520, 560,
  540, 520,
  540, 520,
  560, 520,
  500, 560,
  500, 560,
  560, 1560,
  560, 1580,
  500, 560,
  500, 1640,
  540, 520,
  500, 560,
  520, 540,
  520, 560,
  560, 500,
  540, 520,
  500, 1640,
  500, 560,
  500, 1620,
  520, 1620,
  500, 1620,
  560, 1580,
  560, 5100,
  4320, 4260,
  500, 1640,
  500, 580,
  480, 1640,
  500, 1620,
  500, 560,
  500, 560,
  520, 1620,
  500, 580,
  520, 540,
  500, 1620,
  500, 580,
  480, 580,
  480, 1640,
  500, 1640,
  480, 560,
  500, 1660,
  520, 540,
  480, 560,
  520, 1620,
  500, 1620,
  500, 1620,
  520, 1620,
  500, 1620,
  500, 1620,
  540, 1600,
  500, 1620,
  520, 580,
  480, 560,
  500, 580,
  480, 580,
  480, 560,
  520, 580,
  500, 1600,
  500, 1640,
  500, 560,
  500, 1620,
  520, 560,
  500, 560,
  500, 560,
  500, 580,
  520, 520,
  520, 560,
  500, 1620,
  500, 580,
  500, 1640,
  480, 1620,
  520, 1620,
  500, 1620,
  52, 0};
 
int CODE_AC_OFF[] = {
  4320, 4280,
  560, 1580,
  560, 500,
  520, 1620,
  520, 1600,
  560, 540,
  500, 540,
  520, 1600,
  540, 520,
  580, 500,
  520, 1600,
  560, 500,
  560, 520,
  540, 1580,
  560, 1580,
  540, 520,
  540, 1600,
  560, 500,
  540, 1580,
  540, 1600,
  540, 1580,
  560, 1580,
  540, 520,
  520, 1620,
  520, 1600,
  560, 1560,
  540, 520,
  540, 540,
  520, 540,
  540, 520,
  540, 1600,
  520, 540,
  540, 520,
  560, 1580,
  520, 1600,
  520, 1640,
  500, 540,
  520, 540,
  520, 540,
  540, 520,
  540, 540,
  560, 500,
  520, 540,
  540, 520,
  560, 1580,
  520, 1600,
  520, 1600,
  560, 1580,
  520, 1600,
  560, 5100,
  4340, 4260,
  520, 1600,
  520, 540,
  540, 1600,
  560, 1560,
  560, 520,
  520, 540,
  520, 1600,
  560, 500,
  580, 500,
  520, 1600,
  540, 520,
  540, 520,
  540, 1600,
  540, 1580,
  560, 520,
  540, 1580,
  560, 500,
  540, 1600,
  560, 1560,
  540, 1600,
  520, 1600,
  520, 540,
  540, 1600,
  520, 1620,
  540, 1580,
  520, 540,
  560, 500,
  560, 500,
  560, 500,
  560, 1580,
  560, 500,
  540, 540,
  540, 1580,
  540, 1580,
  560, 1580,
  540, 520,
  540, 520,
  560, 500,
  560, 500,
  560, 520,
  560, 500,
  560, 500,
  560, 500,
  540, 1600,
  540, 1580,
  560, 1580,
  540, 1580,
  560, 1560,
  54, 0};

void setup()   {                
  // initialize the IR digital pin as an output:
  pinMode(IRledPin, OUTPUT);      
 
  Serial.begin(9600);
}
 
void loop()                     
{
  Serial.println("Sending IR signal");
 
  sendCode();
  delay(65);
  sendCode();
 
  delay(2*1000);
}
 
// This procedure sends a 38KHz pulse to the IRledPin 
// for a certain # of microseconds. We'll use this whenever we need to send codes
void pulseIR(long microsecs) {
  // we'll count down from the number of microseconds we are told to wait
 
  cli();  // this turns off any background interrupts
 
  while (microsecs > 0) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
   digitalWrite(IRledPin, HIGH);  // this takes about 3 microseconds to happen
   delayMicroseconds(9);         // hang out for 10 microseconds, you can also change this to 9 if its not working
   digitalWrite(IRledPin, LOW);   // this also takes about 3 microseconds
   delayMicroseconds(9);         // hang out for 10 microseconds, you can also change this to 9 if its not working
 
   // so 26 microseconds altogether
   microsecs -= 26;
  }
 
  sei();  // this turns them back on
}
 
void sendCode() {
 int codeLength = sizeof(CODE_1) / sizeof(int);
  for (int i = 0; i < codeLength; i = i + 2) {
    pulseIR(CODE_1[i]);
    delayMicroseconds(CODE_1[i+1]);
  }
}