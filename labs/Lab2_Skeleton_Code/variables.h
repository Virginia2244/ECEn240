#ifndef VARIABLES
#define VARIABLES

#include "Arduino.h"

//
// Compiler defines: the compiler replaces each name with its assignment
// (These make your code so much more readable.)
//

/***********************************************************/
// Hardware pin definitions
// Replace the pin numbers with those you connect to your robot

// Button pins. These will be replaced with the photodiode variables in lab 5
#define BUTTON_1 A2 // Far left Button - Servo Up
#define BUTTON_2 A3 // Left middle button - Left Motor
#define BUTTON_3 A4 // Middle Button - Collision
#define BUTTON_4 A5 // Right middle button - Right Motor
#define BUTTON_5 A6 // Far right button - Servo Down

// LED pins
#define LED_1 6 // Far Left LED - Servo Up
#define LED_2 5 // Left Middle LED  - Left Motor
#define LED_3 4 // Middle LED - Collision
#define LED_4 3 // Right Middle LED - Right Motor
#define LED_5 2 // Far Right LED - Servo Down

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
#define DETECTION_NO 0
#define DETECTION_YES 1

// Motor speed definitions - Lab 4

// Collision definitions
#define COLLISION_OFF 0
#define COLLISION_ON 1

// Driving direction definitions
#define DRIVE_STOP 0
#define DRIVE_LEFT 1
#define DRIVE_RIGHT 2
#define DRIVE_STRAIGHT 3

// Servo movement definitions
#define SERVO_MOVE_STOP 0
#define SERVO_MOVE_UP 1
#define SERVO_MOVE_DOWN 2



/***********************************************************/
// Global variables that define PERCEPTION and initialization

// Collision (using Definitions)
extern int SensedCollision;

// Photodiode inputs (using Definitions) - The button represent the photodiodes for lab 2
extern int SensedLightRight;
extern int SensedLightLeft;
extern int SensedLightUp;
extern int SensedLightDown;

// Capacitive sensor input (using Definitions) - Lab 4
// int SensedCapacitiveTouch = DETECTION_NO;

/***********************************************************/
// Global variables that define ACTION and initialization

// Collision Actions (using Definitions)
extern int ActionCollision;

// Main motors Action (using Definitions)
extern int ActionRobotDrive;
// Add speed action in Lab 4

// Servo Action (using Definitions)
extern int ActionServoMove;
#endif
