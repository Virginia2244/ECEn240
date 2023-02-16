#include "perception.h"

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