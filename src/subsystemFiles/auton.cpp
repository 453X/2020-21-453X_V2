#include "main.h"

void deploy(){
  resetIntakeEncoders();
  resetRollersEncoders();
  while(avgIntakeEncoder() < abs(500)){
    intakeLeft.move_voltage(-12000);
    intakeRight.move_voltage(12000);
    rollersTop.move_voltage(12000);
    rollersBottom.move_voltage(12000);
    pros::delay(10);
  }
}

void redLeft(){
  pros::lcd::initialize();
  calibrate();
  delaySeconds(2);
  forward(100, 1800);
  stop(0.3);
  rotateDegrees(225);
  stop(0.3);
  intake();
  forward(80, 2050);
  forward(60);
  delaySeconds(0.5);
  intakeStop();
  stop(0.2);
  roll();
  delaySeconds(0.8);
  rollersStop();
  stop();
  forward(100, -1500);
  stop(0.2);
  rotateDegrees(180);
  stop(0.2);
  straft(100, -2000);
  stop(0.2);
  forward(80);
  delaySeconds(0.7);
  roll();
  delaySeconds(1);
  forward(80, -1000);
  stop();
}
