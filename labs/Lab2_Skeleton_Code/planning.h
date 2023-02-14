#include "variables.h"

#ifndef PLANNING
#define PLANNING
void RobotPlanning(void);

void fsmCollisionDetection();

void fsmSteerRobot();

void fsmMoveServoUpAndDown();

void fsmCapacitiveSensorSpeedControl();

void fsmChangeSpeed();
#endif