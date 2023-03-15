#include "planning.h"

/**********************************************************************************************************
  Robot PLANNING - using the sensing to make decisions
 **********************************************************************************************************/
void RobotPlanning(void) {
  // The planning FSMs that are used by the robot to assign actions
  // based on the sensing from the Perception stage.
  fsmCollisionDetection(); // Milestone 1
  fsmMoveServoUpAndDown(); // Milestone 3
  fsmVoltageDetection(); // Lab 3 Milestone 2
  fsmCapacitiveSensorSpeedControl();
}

////////////////////////////////////////////////////////////////////
// State machine for detecting collisions, and stopping the robot
// if necessary.
////////////////////////////////////////////////////////////////////
void fsmCollisionDetection() {
  static int collisionDetectionState = 0;
  //Serial.println(collisionDetectionState); //uncomment for debugging

  switch (collisionDetectionState) {
    case 0: //collision detected
      //There is an obstacle, stop the robot
      ActionCollision = COLLISION_ON; // Sets the action to turn on the collision LED
      ActionRobotDrive = DRIVE_STOP;


      //State transition logic
      if ( SensedCollision == DETECTION_NO) {
        collisionDetectionState = 1; //if no collision, go to no collision state
      }
      break;

    case 1: //no collision
      //There is no obstacle, drive the robot
      ActionCollision = COLLISION_OFF; // Sets action to turn off the collision LED

      fsmSteerRobot(); // Milestone 2

      //State transition logic
      if ( SensedCollision == DETECTION_YES ) {
        collisionDetectionState = 0; //if collision, go to collision state
      }
      break;

    default: // error handling
      {
        collisionDetectionState = 0;
      }
  }
}

////////////////////////////////////////////////////////////////////
// Code for determining the state of steerRobotState
////////////////////////////////////////////////////////////////////

int getSteerRobotState() {
  if ((SensedLightLeft == 0) && (SensedLightRight == 0)) {
    return 0; //Stop
  }
  else if ((SensedLightLeft == 1) && (SensedLightRight == 0)) {
    return 1; //turn left
  }
  else if ((SensedLightLeft == 0) && (SensedLightRight == 1)) {
    return 2; //turn right
  }
  else {
    return 3; //go straight
  }
}

////////////////////////////////////////////////////////////////////
// State machine for detecting if light is to the right or left,
// and steering the robot accordingly.
////////////////////////////////////////////////////////////////////

void fsmSteerRobot() {
  static int steerRobotState = 0;
  //  Serial.println(steerRobotState); //uncomment for debugging

  switch (steerRobotState) {
    case 0: //light is not detected
      //The light is straight ahead, drive straight
      ActionRobotDrive = DRIVE_STOP;
      steerRobotState = getSteerRobotState();
      break;

    case 1: //light is to the left of robot
      //The light is on the left, turn left
      ActionRobotDrive =  DRIVE_LEFT;
      steerRobotState = getSteerRobotState();
      break;

    case 2: //light is to the right of robot
      //The light is on the right, turn right
      ActionRobotDrive =  DRIVE_RIGHT;
      steerRobotState = getSteerRobotState();
      break;

    case 3:
      ActionRobotDrive = DRIVE_STRAIGHT;
      steerRobotState = getSteerRobotState();
      //control the LEDs
      break;

    default: // error handling
      {
        steerRobotState = 0;
      }
  }
}


////////////////////////////////////////////////////////////////////
// Helper funciton for fsmMoveServoUpAndDown
// Checks the state of the sensors and changes moveServoState accordingly
////////////////////////////////////////////////////////////////////
int getServoState() {
  if (((SensedLightDown == 1) && (SensedLightUp == 0))) {
    return SERVO_MOVE_DOWN;
  } else if (((SensedLightDown == 0) && (SensedLightUp == 1))) {
    return SERVO_MOVE_UP;
  } else {
    return SERVO_MOVE_STOP;
  }
}

////////////////////////////////////////////////////////////////////
// State machine for detecting if light is above or below center,
// and moving the servo accordingly.
////////////////////////////////////////////////////////////////////
void fsmMoveServoUpAndDown() {
  static int moveServoState = 0;
  //Serial.println(moveServoState); //uncomment for debugging

  // Milestone 3
  //Create a state machine modeled after the ones in milestones 1 and 2
  // to plan the servo action based off of the perception of the robot
  //Remember no light or light in front = servo doesn't move
  //Light above = servo moves up
  //Light below = servo moves down

  switch (moveServoState) {
    case SERVO_MOVE_STOP: //Light is detected evenly across the sensors
      moveServoState = getServoState();
      ActionServoMove = SERVO_MOVE_STOP;
      break;

    case SERVO_MOVE_UP: //Light is detected by the upper sensor
      moveServoState = getServoState();
      ActionServoMove = SERVO_MOVE_UP;
      break;

    case SERVO_MOVE_DOWN: //Light is detected by the lower sensor
      moveServoState = getServoState();
      ActionServoMove = SERVO_MOVE_DOWN;
      break;

    default:  //bug handling
      {
        moveServoState = SERVO_MOVE_STOP;
      }

  }

}


////////////////////////////////////////////////////////////////////
// State machine for detecting when the battery's voltage
// is running low and turning on the right LEDs
////////////////////////////////////////////////////////////////////
void fsmVoltageDetection(){
  if (BatV <= (7.2/3)){
    BatteryState = 0;
  }
  else if (BatV <= (9/3)){
    BatteryState = 1;
  }
  else if (BatV <= (11.2/3)){
    BatteryState = 2;
  }
  else {
    BatteryState = 3;
  }
}

////////////////////////////////////////////////////////////////////
// State machine for detecting when the capacitive sensor is
// touched, and changing the robot's speed.
////////////////////////////////////////////////////////////////////
void fsmCapacitiveSensorSpeedControl() {
    static int CapacitorState = 0;
    Serial.print(CapacitorState);
  switch(CapacitorState ){
    case 0:
        if(CapacitorTouched){
            CapacitorState = 1;
        }
    break;
    case 1:
        if(!CapacitorTouched){
            CapacitorState = 2;
        }
    break;
    case 2:
        CapacitorState = 0;
        if(MotorSpeed + INCREMENT_SPEED > 255){
            MotorSpeed = 0;
        }
        else {
            MotorSpeed += INCREMENT_SPEED;
        }
    break;
    default:
        CapacitorState = 0;
    break;
  }
}

////////////////////////////////////////////////////////////////////
// State machine for cycling through the robot's speeds.
////////////////////////////////////////////////////////////////////
void fsmChangeSpeed() {
  /*Implement in lab 4*/
}
