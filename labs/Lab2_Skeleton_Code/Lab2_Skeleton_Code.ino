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

//
// Compiler defines: the compiler replaces each name with its assignment
// (These make your code so much more readable.)
//

/***********************************************************/
// Hardware pin definitions
// Replace the pin numbers with those you connect to your robot

// Button pins. These will be replaced with the photodiode variables in lab 5
#define BUTTON_1  A2     // Far left Button - Servo Up
#define BUTTON_2  A3     // Left middle button - Left Motor
#define BUTTON_3  A4     // Middle Button - Collision
#define BUTTON_4  A5     // Right middle button - Right Motor
#define BUTTON_5  A6     // Far right button - Servo Down

// LED pins
#define LED_1   6       // Far Left LED - Servo Up
#define LED_2   5       // Left Middle LED  - Left Motor
#define LED_3   4       // Middle LED - Collision
#define LED_4   3       // Right Middle LED - Right Motor
#define LED_5   2       // Far Right LED - Servo Down


// Motor enable pins - Lab 3
// These will replace LEDs 2 and 4

// Photodiode pins - Lab 5
// These will replace buttons 1, 2, 4, 5

// Capacitive sensor pins - Lab 4


// Ultrasonic sensor pin - Lab 6
// This will replace button 3 and LED 3 will no longer be needed

// Servo pin - Lab 6
// This will replace LEDs 1 and 5

/***********************************************************/
// Configuration parameter definitions
// Replace the parameters with those that are appropriate for your robot

// Voltage at which a button is considered to be pressed
#define BUTTON_THRESHOLD 2.5

// Voltage at which a photodiode voltage is considered to be present - Lab 5


// Number of samples that the capacitor sensor will use in a measurement - Lab 4


// Parameters for servo control as well as instantiation - Lab 6


// Parameters for ultrasonic sensor and instantiation - Lab 6


// Parameter to define when the ultrasonic sensor detects a collision - Lab 6



/***********************************************************/
// Defintions that allow one to set states
// Sensor state definitions
#define DETECTION_NO    0
#define DETECTION_YES   1

// Motor speed definitions - Lab 4

// Collision definitions
#define COLLISION_OFF 0
#define COLLISION_ON  1

// Driving direction definitions
#define DRIVE_STOP      0
#define DRIVE_LEFT      1
#define DRIVE_RIGHT     2
#define DRIVE_STRAIGHT  3

// Servo movement definitions
#define SERVO_MOVE_STOP 0
#define SERVO_MOVE_UP   1
#define SERVO_MOVE_DOWN 2


/***********************************************************/
// Global variables that define PERCEPTION and initialization

// Collision (using Definitions)
int SensedCollision = DETECTION_NO;

// Photodiode inputs (using Definitions) - The button represent the photodiodes for lab 2
int SensedLightRight = DETECTION_NO;
int SensedLightLeft = DETECTION_NO;
int SensedLightUp = DETECTION_NO;
int SensedLightDown = DETECTION_NO;

// Capacitive sensor input (using Definitions) - Lab 4
//int SensedCapacitiveTouch = DETECTION_NO;


/***********************************************************/
// Global variables that define ACTION and initialization

// Collision Actions (using Definitions)
int ActionCollision = COLLISION_OFF;

// Main motors Action (using Definitions)
int ActionRobotDrive = DRIVE_STOP;
// Add speed action in Lab 4

// Servo Action (using Definitions)
int ActionServoMove =  SERVO_MOVE_STOP;

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
  int DebugStateOutput = false; // Change false to true to debug

  RobotPerception(); // PERCEPTION
  if (DebugStateOutput) {
    Serial.print("Perception:");
    //    Serial.print(SensedLightUp);
    //    Serial.print(SensedLightLeft);
    Serial.print(SensedCollision);
    Serial.print(SensedLightRight);
    Serial.print(SensedLightDown);
    //    Serial.print(SensedCapacitiveTouch); - Lab 4
  }

  RobotPlanning(); // PLANNING
  if (DebugStateOutput) {
    Serial.print(" Action:");
    Serial.print(ActionCollision);
    Serial.println(ActionRobotDrive);
    //    Serial.print(ActionRobotSpeed); - Lab 4
    //    Serial.println(ActionServoMove);
  }
  RobotAction(); // ACTION
}

/**********************************************************************************************************
  Robot PERCEPTION - all of the sensing
 ********************************************************************/
void RobotPerception() {
  // This function polls all of the sensors and then assigns sensor outputs
  // that can be used by the robot in subsequent stages



  // Photodiode Sensing
  //Serial.println(getPinVoltage(BUTTON_2)); //uncomment for debugging


  if (isButtonPushed(BUTTON_2)) {
    SensedLightLeft = DETECTION_YES;
  } else {
    SensedLightLeft = DETECTION_NO;
  }
  // Remember, you can find the buttons and which one goes to what towards the top of the file
  if (isButtonPushed(BUTTON_4)) {
    SensedLightRight = DETECTION_YES;
  } else {
    SensedLightRight = DETECTION_NO;
  }



  /* Code to detect if light is up or down. Lab 2 milestone 3*/
  if (isButtonPushed(BUTTON_1)) {
    SensedLightUp = DETECTION_YES;
  } else {
    SensedLightUp = DETECTION_NO;
  }

  if (isButtonPushed(BUTTON_5)) {
    SensedLightDown = DETECTION_YES;
  } else {
    SensedLightDown = DETECTION_NO;
  }


  // Capacitive Sensor
  /*Add code in lab 4*/

  // Collision Sensor
  if (isCollision()) {   // Add code in isCollision() function for lab 2 milestone 1
    SensedCollision = DETECTION_YES;
  } else {
    SensedCollision = DETECTION_NO;
  }
}


////////////////////////////////////////////////////////////////////
// Function to read pin voltage
////////////////////////////////////////////////////////////////////
float getPinVoltage(int pin) {
  //This function can be used for many different tasks in the labs
  //Study this line of code to understand what is going on!!
  //What does analogRead(pin) do?
  //Why is (float) needed?
  //Why divide by 1024?
  //Why multiply by 5?
  return 5 * (float)analogRead(pin) / 1024;
}

////////////////////////////////////////////////////////////////////
// Function to determine if a button is pushed or not
////////////////////////////////////////////////////////////////////
bool isButtonPushed(int button_pin) {
  //This function can be used to determine if a said button is pushed.
  //Remember that when the voltage is 0, it's only close to zero.
  //Hint: Call the getPinVoltage function and if that value is greater
  // than the BUTTON_THRESHOLD variable toward the top of the file, return true.
  return getPinVoltage(button_pin) >= BUTTON_THRESHOLD;
}


////////////////////////////////////////////////////////////////////
// Function that detects if there is an obstacle in front of robot
////////////////////////////////////////////////////////////////////
bool isCollision() {
  //This is where you add code that tests if the collision button
  // was pushed (BUTTON_3)
  //In lab 6 you will add a sonar sensor to detect collision and
  // the code for the sonar sensor will go in this function.
  // Until then we will use a button to model the sensor.
  return isButtonPushed(BUTTON_3);
}

////////////////////////////////////////////////////////////////////
// Function that detects if the capacitive sensor is being touched
////////////////////////////////////////////////////////////////////
bool isCapacitiveSensorTouched() {
  //In lab 4 you will add a capacitive sensor, and
  // you will need to modify this function accordingly.
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


/**********************************************************************************************************
  Robot ACTION - implementing the decisions from planning to specific actions
 ********************************************************************/
void RobotAction() {
  // Here the results of planning are implented so the robot does something

  // This turns the collision LED on and off
  switch (ActionCollision) {
    case COLLISION_OFF:
      doTurnLedOff(LED_3); //OR ELSE YOUR LEDS WON'T WORK!!!
      break;
    case COLLISION_ON:
      doTurnLedOn(LED_3);
      break;
  }

  //Prints the volatge of BUTTON_3
  //  Serial.print(getPinVoltage(BUTTON_3));
  //  Serial.print("\n");

  // This drives the main motors on the robot
  switch (ActionRobotDrive) {
    case DRIVE_STOP:
      //control the LEDs
      doTurnLedOff(LED_2);
      doTurnLedOff(LED_4);
      break;
    case DRIVE_LEFT:
      //control the LEDs
      doTurnLedOn(LED_2);
      doTurnLedOff(LED_4);
      break;
    case DRIVE_RIGHT:
      //control the LEDs
      doTurnLedOff(LED_2);
      doTurnLedOn(LED_4);
      break;
    case DRIVE_STRAIGHT:
      doTurnLedOn(LED_2);
      doTurnLedOn(LED_4);
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
      doTurnLedOff(LED_5);
      doTurnLedOff(LED_1);
      break;
    case SERVO_MOVE_UP:
      doTurnLedOff(LED_5);
      doTurnLedOn(LED_1);
      break;
    case SERVO_MOVE_DOWN:
      doTurnLedOn(LED_5);
      doTurnLedOff(LED_1);
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
