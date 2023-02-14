#include "action.h"

/**********************************************************************************************************
  Robot ACTION - implementing the decisions from planning to specific actions
 ********************************************************************/
void RobotAction()
{
    // Here the results of planning are implented so the robot does something

    // This turns the collision LED on and off
    switch (ActionCollision)
    {
    case COLLISION_OFF:
        doTurnLedOff(LED_3); // OR ELSE YOUR LEDS WON'T WORK!!!
        break;
    case COLLISION_ON:
        doTurnLedOn(LED_3);
        break;
    }

    // Prints the volatge of BUTTON_3
//    Serial.print(getPinVoltage(BUTTON_3));
//    Serial.print("\n");

    // This drives the main motors on the robot
    switch (ActionRobotDrive)
    {
    case DRIVE_STOP:
        /* Add code in milestone 2 to turn off both left and right motors (LEDs right now).
          Use the doTurnLedOff() function */
        /* DON'T FORGET TO USE YOUR LED VARIABLES AND NOT YOUR BUTTON VARIABLES FOR THIS!!! */
        break;
    case DRIVE_LEFT:
        /* Add code in milestone 2 to turn off the right and on the left LEDs */
        break;
    case DRIVE_RIGHT:
        /* Add code in milestone 2 */
        break;
    case DRIVE_STRAIGHT:
        /* Add code in milestone 2 */
        break;
    }

    // This calls a function to move the servo
    MoveServo();
}

////////////////////////////////////////////////////////////////////
// Function that causes the servo to move up or down.
////////////////////////////////////////////////////////////////////
void MoveServo()
{
    // Note that there needs to be some logic in the action of moving
    // the servo so that it does not exceed its range
    /* Add CurrentServoAngle in lab 6 */
    switch (ActionServoMove)
    {
    case SERVO_MOVE_STOP:
        /* Add code in milestone 3 */
        break;
    case SERVO_MOVE_UP:
        /* Add code in milestone 3 */
        break;
    case SERVO_MOVE_DOWN:
        /* Add code in milestone 3 */
        break;
    }
}

/**********************************************************************************************************
  AUXILIARY functions that may be useful in performing diagnostics
 ********************************************************************/
// Function to turn LED on
void doTurnLedOn(int led_pin)
{
    digitalWrite(led_pin, HIGH);
}

// Function to turn LED off
void doTurnLedOff(int led_pin)
{
    digitalWrite(led_pin, LOW);
}
