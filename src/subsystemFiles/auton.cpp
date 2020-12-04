#include "main.h"
#include "subsystemHeaders/rollers.hpp"

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
  rollersStop();
  intakeStop();
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

void skills(){
  deploy();
  intake();
  rollBottom();
  forward(60, 600);

  stop(0.3);
  rotateDegrees(140);
  rollersStop();
  intakeStop();
  stop();
  forward(70, 700);
  forward(80);
  delaySeconds(0.5);
  stop();
  roll();
  delaySeconds(0.3);
  rollersStop();
  forward(80, -800);
  stop(0.2);
  rotateDegrees(90);
  stop(0.2);
  straft(80, -2100);
  stop(0.3);
  forward(80);
  delaySeconds(0.5);
  stop();
  roll();
  delaySeconds(0.5);
  rollersStop();
  forward(80, -550);
  delaySeconds(0.2);
  rotateDegrees(0);
  stop(0.2);
  rollBottom();
  intake();
  forward(60, 1700);
  rollersStop();
  delaySeconds(0.2);
  rotateDegrees(35);
  delaySeconds(0.2);
  intakeStop();
  roll();
  forward(80, 1500);
  forward(80);
  delaySeconds(0.5);
  stop();

  delaySeconds(1);
  rollersStop();

}
