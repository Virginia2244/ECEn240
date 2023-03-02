#include "action.h"

/**********************************************************************************************************
  Robot ACTION - implementing the decisions from planning to specific actions
 ********************************************************************/
void RobotAction() {
  // Here the results of planning are implented so the robot does something

  // This turns the collision LED on and off
  switch (ActionCollision) {
    case COLLISION_OFF:
//      doTurnLedOff(LED_3); //OR ELSE YOUR LEDS WON'T WORK!!!
      break;
    case COLLISION_ON:
//      doTurnLedOn(LED_3);
      break;
  }

  //Prints the volatge of BUTTON_3
  //  Serial.print(getPinVoltage(BUTTON_3));
  //  Serial.print("\n");

  // This drives the main motors on the robot
  switch (ActionRobotDrive) {
    case DRIVE_STOP:
      //control the LEDs
//      doTurnLedOff(H_BRIDGE_ENA);
//      doTurnLedOff(H_BRIDGE_ENB);
      break;
    case DRIVE_LEFT:
      //control the LEDs
//      doTurnLedOn(H_BRIDGE_ENA);
//      doTurnLedOff(H_BRIDGE_ENB);
      break;
    case DRIVE_RIGHT:
      //control the LEDs
//      doTurnLedOff(H_BRIDGE_ENA);
//      doTurnLedOn(H_BRIDGE_ENB);
      break;
    case DRIVE_STRAIGHT:
//      doTurnLedOn(H_BRIDGE_ENA);
//      doTurnLedOn(H_BRIDGE_ENB);
      break;
  }

  switch (BatteryState){
    case 0:
        doTurnLedOff(LED_5);
        doTurnLedOff(LED_4);
        doTurnLedOff(LED_3);
    break;
    case 1:
        doTurnLedOn(LED_5);
        doTurnLedOff(LED_4);
        doTurnLedOff(LED_3);
    break;
    case 2:
        doTurnLedOn(LED_5);
        doTurnLedOn(LED_4);
        doTurnLedOff(LED_3);
    break;
    case 3:
        doTurnLedOn(LED_5);
        doTurnLedOn(LED_4);
        doTurnLedOn(LED_3);
    break;
  }

  

  // This calls a function to move the servo
  MoveServo();
}


////////////////////////////////////////////////////////////////////
// Function that causes the servo to move up or down.
////////////////////////////////////////////////////////////////////
void MoveServo() {
  // Note that there needs to be some logic in the action of moving
  // the servo so that it does not exceed its range
  /* Add CurrentServoAngle in lab 6 */
  switch (ActionServoMove) {
    case SERVO_MOVE_STOP:
//      doTurnLedOff(LED_5);
//      doTurnLedOff(LED_1);
      break;
    case SERVO_MOVE_UP:
//      doTurnLedOff(LED_5);
//      doTurnLedOn(LED_1);
      break;
    case SERVO_MOVE_DOWN:
//      doTurnLedOn(LED_5);
//      doTurnLedOff(LED_1);
      break;
  }
}




/********************************************************************
  AUXILIARY functions that may be useful in performing diagnostics
 ********************************************************************/
// Function to turn LED on
void doTurnLedOn(int led_pin) {
  digitalWrite(led_pin, HIGH);
}

// Function to turn LED off
void doTurnLedOff(int led_pin) {
  digitalWrite(led_pin, LOW);
}
