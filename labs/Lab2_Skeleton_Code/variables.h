#ifndef VARIABLES
#define VARIABLES
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
//int SensedCapacitiveTouch = DETECTION_NO;


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