// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _ac_control_H_
#define _ac_control_H_
#include "Arduino.h"
//add your includes for the project ac_control here

#include <SoftwareSerial.h>
#include "ir_codes.h"

//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project ac_control here

void processCommand(char);
void sendCode(int[], int);
void pulseIR(long);

//Do not add code below this line
#endif /* _ac_control_H_ */
