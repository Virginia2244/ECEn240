#include "variables.h"

#ifndef PERCEPTION
#define PERCEPTION
void RobotPerception();

float getPinVoltage(int pin);

bool isButtonPushed(int button_pin);

bool isCollision();

bool isCapacitiveSensorTouched();

bool isPhotodiodeLit(int pin);
#endif
