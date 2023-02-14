#include "variables.h"
#include "perception.h"

#ifndef ACTION
#define ACTION
void RobotAction();

void MoveServo();

void doTurnLedOn(int led_pin);

void doTurnLedOff(int led_pin);
#endif