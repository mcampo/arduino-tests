#include <CustomStepper.h>

float rpm = 12;
CustomStepper stepper(11, 10, 9, 8, (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001}, 4075.7728395, 12, CW);


String command = "";

void setup()
{
  Serial.begin(9600);
  //sets the RPM
  stepper.setRPM(2);
  stepper.setSPR(4075.7728395);
  stepper.rotate();
  stepper.setDirection(STOP);
  Serial.println("Ready!");
}

void loop()
{
  checkSerial();
  //this is very important and must be placed in your loop, it is this that makes the motor steps
  //when necessary
  stepper.run();
}

void checkSerial() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      processCommand();
      command = "";
    } else {
      command += inChar;
    }
  }
}

void processCommand() {
  command.toUpperCase();
  Serial.println("Processing command " + command);

  if (command.equals("CW")) {
    stepper.setDirection(CW);
    stepper.rotate();
  }

  if (command.equals("CCW")) {
    stepper.setDirection(CCW);
    stepper.rotate();
  }

  if (command.equals("STOP")) {
    stepper.setDirection(STOP);
  }

  if (command.startsWith("RPM")) {
    float rpm = command.substring(4).toFloat();
    stepper.setRPM(rpm);
  }

}

