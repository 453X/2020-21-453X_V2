#include "main.h"
#include "subsystemHeaders/rollers.hpp"

void deploy() {
  resetIntakeEncoders();
  resetRollersEncoders();
  while (avgIntakeEncoder() < abs(750)) {
    intakeLeft.move_voltage(-12000);
    intakeRight.move_voltage(12000);
    rollersTop.move_voltage(12000);
    rollersBottom.move_voltage(12000);
    pros::delay(10);
  }
  rollersStop();
  intakeStop();
}

void left() {
  deploy();

  // move forward
  forward(100, 1800);
  stop(0.3);

  // turn to 1st goal
  rotateDegrees(225);
  stop(0.3);
  intake();

  // go to 1st goal
  forward(80, 2050);
  forward(60);
  delaySeconds(0.5);
  intakeStop();
  stop(0.2);

  // put ball to goal
  roll();
  delaySeconds(0.8);
  rollersStop();

  // back off
  forward(100, -1500);
  rollBottom();
  intake();
  stop(0.2);

  // turn to face the wall
  rotateDegrees(180);
  stop(0.2);
  intakeStop();
  rollersStop();

  // straft to 2nd goal
  straft(100, -2000);
  stop(0.2);

  // move to goal
  forward(80);
  delaySeconds(0.7);

  // put ball in 2nd goal
  roll();
  delaySeconds(1);

  // back off
  forward(80, -1000);
  stop();
}

void skills() {
  deploy();

  //move forward
  intake();
  rollBottom();
  forward(60, 600);
  stop(0.3);

  //rotate to 1st goal
  rotateDegrees(140);
  rollersStop();
  intakeStop();
  stop();

  //move to 1st goal
  forward(70, 700);
  forward(80);
  delaySeconds(0.5);
  stop();

  //put ball in 1st goal
  roll();
  delaySeconds(0.3);
  rollersStop();

  //back off from 1st goal
  forward(80, -800);
  stop(0.2);

  //rotate to face 2nd wall
  rotateDegrees(90);
  stop(0.2);

  //straft to 2nd goal
  straft(80, -2100);
  stop(0.3);

  //move to 2nd goal
  forward(80);
  delaySeconds(0.5);
  stop();

  //put ball in 2nd goal
  roll();
  delaySeconds(0.5);
  rollersStop();

  //back off from 2nd goal
  forward(80, -550);
  delaySeconds(0.2);

  //turn to initial direction
  rotateDegrees(0);
  stop(0.2);

  //intake the ball in front of 3rd goal
  rollBottom();
  intake();

  //move to ball
  forward(60, 1700);
  rollersStop();
  delaySeconds(0.2);

  //turn to 3rd goal
  rotateDegrees(35);
  delaySeconds(0.2);
  intakeStop();
  rollBottom();

  //go to 3rd goal
  forward(80, 1500);
  forward(80);
  roll();
  delaySeconds(0.5);
  stop();

  delaySeconds(1);
  rollersStop();
}

void right(){
  deploy();

  // move forward
  forward(100, 1800);
  stop(0.3);

  // turn to 1st goal
  rotateDegrees(315);
  stop(0.3);
  intake();

  // go to 1st goal
  forward(80, 2050);
  forward(60);
  delaySeconds(0.5);
  intakeStop();
  stop(0.2);

  // put ball to goal
  roll();
  delaySeconds(0.8);
  rollersStop();

  // back off
  forward(100, -1500);
  rollBottom();
  intake();
  stop(0.2);

  // turn to face the wall
  rotateDegrees(270);
  stop(0.2);
  intakeStop();
  rollersStop();

  // straft to 2nd goal
  straft(100, -2000);
  stop(0.2);

  // move to goal
  forward(80);
  delaySeconds(0.7);

  // put ball in 2nd goal
  roll();
  delaySeconds(1);

  // back off
  forward(80, -1000);
  stop();
}
