/********************************************************************
  ECEN 240/301 Lab Code
  Light-Following Robot

  The approach of this code is to use an architectured that employs
  three different processes:
    Perception
    Planning
    Action

  By separating these processes, this allows one to focus on the
  individual elements needed to do these tasks that are general
  to most robotics.


  Version History
  1.1.3       11 January 2023   Creation by Dr. Mazzeo and TAs from 2022 version

 ********************************************************************/

/* These initial includes allow you to use necessary libraries for
your sensors and servos. */
#include "Arduino.h"
#include "variables.h"
#include "action.h"





/********************************************************************
  SETUP function - this gets executed at power up, or after a reset
 ********************************************************************/
void setup() {
  //Set up serial connection at 9600 Baud
  Serial.begin(9600);
  
  //Set up output pins
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);
  
  //Set up input pins
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  pinMode(BUTTON_3, INPUT);
  pinMode(BUTTON_4, INPUT);
  pinMode(BUTTON_5, INPUT);

  //Set up servo - Lab 6

}

/********************************************************************
  Main LOOP function - this gets executed in an infinite loop until
  power off or reset. - Notice: PERCEPTION, PLANNING, ACTION
 ********************************************************************/
void loop() {
  // This DebugStateOutput flag can be used to easily turn on the
  // serial debugging to know what the robot is perceiving and what
  // actions the robot wants to take.
  int DebugStateOutput = true; // Change false to true to debug
  
  RobotPerception(); // PERCEPTION
  if (DebugStateOutput) {
    Serial.print("Perception:");
    Serial.print(SensedLightUp);
    Serial.print(SensedLightLeft);
    Serial.print(SensedCollision);
    Serial.print(SensedLightRight); 
    Serial.print(SensedLightDown);
//    Serial.print(SensedCapacitiveTouch); - Lab 4
  }
  
  RobotPlanning(); // PLANNING
  if (DebugStateOutput) {
    Serial.print(" Action:");
    Serial.print(ActionCollision);
    Serial.print(ActionRobotDrive); 
//    Serial.print(ActionRobotSpeed); - Lab 4
    Serial.println(ActionServoMove);
  }
  RobotAction(); // ACTION
}


/**********************************************************************************************************
  Robot PLANNING - using the sensing to make decisions
 **********************************************************************************************************/
void RobotPlanning(void) {
  // The planning FSMs that are used by the robot to assign actions
  // based on the sensing from the Perception stage.
  fsmCollisionDetection(); // Milestone 1
  fsmMoveServoUpAndDown(); // Milestone 3
  // Add Speed Control State Machine in lab 4
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
      /* Add code in milestone 2 to stop the robot's wheels - Hint: ActionRobotDrive = ________ */
      
      
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
      break;
  }
}

////////////////////////////////////////////////////////////////////
// State machine for detecting if light is to the right or left,
// and steering the robot accordingly.
////////////////////////////////////////////////////////////////////
void fsmSteerRobot() {
  static int steerRobotState = 0;
  //Serial.println(steerRobotState); //uncomment for debugging

  /* Get rid of this whole line for milestone 2
  switch (steerRobotState) {
    case 0: //light is not detected
      //The light is straight ahead, drive straight
      ActionRobotDrive = DRIVE_STOP;
      
      //State transition logic
      if ( SensedLightLeft == DETECTION_YES ) {
        steerRobotState = 1; //if light on left of robot, go to left state
      } else if ( SensedLightRight == DETECTION_YES ) {
        steerRobotState = 2; //if light on right of robot, go to right state
      }
      break;
    
    case 1: //light is to the left of robot
      //The light is on the left, turn left
      ActionRobotDrive =  //Add appropriate variable to set the action to turn left
      
      //State transition logic
      if ( *Add code: If light is also to the right, the light is in front* ) {
        *Add code to transition to the "light on left and right" state* //if light is on right, then go straight
      } else if ( *Add code: no longer light to the left ) {
        *Add transition code* //if light is not on left, go back to stop state
      }
      
      break;
    
    case 2: //light is to the right of robot
      //The light is on the right, turn right
      *Add code to set the action*
      
      //State transition logic
      *Add code to transition to the "light on right and left" state 

      break;
      
    // light is on both right and left
      *Add Code: Add in a case 3 for when the light is on both the right and left 
      *Think about what actions you need to implement and 
      *what changes could occur that would cause a transition to another 
      *state. Don't forget the break statement at the end of the case.
      
      
    default: // error handling
    {
      steerRobotState = 0;
    }
  }
  Get rid of this whole line for milestone 2*/
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
  
}

////////////////////////////////////////////////////////////////////
// State machine for detecting when the capacitive sensor is
// touched, and changing the robot's speed.
////////////////////////////////////////////////////////////////////
void fsmCapacitiveSensorSpeedControl() {
  /*Implement in lab 4*/
}

////////////////////////////////////////////////////////////////////
// State machine for cycling through the robot's speeds.
////////////////////////////////////////////////////////////////////
void fsmChangeSpeed() {
  /*Implement in lab 4*/
}
