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
#include "perception.h"
#include "planning.h"
#include "action.h"





/********************************************************************
  SETUP function - this gets executed at power up, or after a reset
 ********************************************************************/
void setup() {
  //Set up serial connection at 9600 Baud
  Serial.begin(9600);
  
  //Set up output pins
  pinMode(LED_1, OUTPUT);
//  pinMode(LED_2, OUTPUT);
//  pinMode(LED_3, OUTPUT);
//  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);

  //Set up output pins for motors
  pinMode(H_BRIDGE_ENA, OUTPUT);
  pinMode(H_BRIDGE_ENB, OUTPUT);

  //Set up input pin for sensing battery voltage
  pinMode(BATTERY_V, INPUT);
  
  //Set up input pins
  pinMode(PHOTO_DOWN, INPUT);
  pinMode(PHOTO_UP, INPUT);
  pinMode(BUTTON_3, INPUT);
  pinMode(PHOTO_LEFT, INPUT);
  pinMode(PHOTO_RIGHT, INPUT);

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
//  Serial.print("Voltage: ");
//  Serial.print(SensedLightLeft);
//  Serial.print("  ");
//  Serial.print(SensedLightRight);
//  Serial.print("\tBattery State: ");
//  Serial.println(ActionRobotDrive);

//Debgging the capacitive sensor
Serial.print("Speed: ");
Serial.print(MotorSpeed);
Serial.print("\tActionServoMove: ");
Serial.print(ActionServoMove);
Serial.print("\tLeft: ");
Serial.print(SensedLightLeft);
Serial.print("\tRight: ");
Serial.print(SensedLightRight);
Serial.print("\tUp: ");
Serial.print(SensedLightUp);
Serial.print("\tDown: ");
Serial.println(SensedLightDown);
}
