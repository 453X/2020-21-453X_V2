#include "main.h"

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
    // move forward
    forward(100, 1200);
    stop(0.3);

    // turn to 1st goal
    rollBottom();
    rotateDegrees(140);
    stop(0.3);
    intake();

    // go to 1st goal
    forward(80, 1550);
    forward(60);
    delaySeconds(0.5);
    intakeStop();
    stop(0.2);
    rollersStop();

    // put ball to goal
    roll();
    delaySeconds(0.5);
    rollersStop();

    // back off
    forward(100, -1200);
    rollBottom();
    intake();
    stop(0.2);

    // turn to face the wall
    rotateDegrees(180);
    stop(0.2);
    intakeStop();
    rollersStop();

    // straft to 2nd goal
    straft(100, 1500);
    straft(50, 600);
    stop(0.2);

    // move to goal
    forward(80);
    delaySeconds(0.7);

    // put ball in 2nd goal
    roll();
    delaySeconds(0.4);
    rollersStop();

    // back off
    forward(80, -1200);
    stop();

  // turn to face ball
  rotateDegrees(0);

  //go to descore middle goal
  intakeRight.move_voltage(-12000);
  forward(80, 1300);
  forward(80);
  delaySeconds(0.5);

  //back off
  intakeStop();
  forward(80, -900);
/*
  //turn to face ball
  rotateDegrees(270);

  // go to ball
  intake();
  rollBottom();
  forward(80, 1500);
  delaySeconds(0.5);
*/
  // turn to face 3rd goal
  rotateDegrees(245);
  intakeStop();
  rollersStop();
  delaySeconds(0.5);

  // go to 3rd goal
  intake();
  rollBottom();
  forward(100, 2000);
  stop(0.5);

  rotateDegrees(250);
  forward(50, 1000);
  forward(90);
  delaySeconds(0.8);


  rollersStop();
  stop();

  rotateDegrees(230);

  // move to goal
  forward(80);
  delaySeconds(2.5);

  // put ball in 2nd goal
  roll();
  delaySeconds(0.4);
  rollersStop();

  // put ball in 3rd goal
  roll();
  delaySeconds(1);
  intakeStop();


  // back off
  forward(80, -1000);
  delaySeconds(0.3);
  rollersStop();
/*
  // turn to ball
  rotateDegrees(270);

  // go to ball
  intake();
  rollBottom();
  forward(70, 1500);

  // turn to 4th goal
  rotateDegrees(0);

  // go to 4th goal
  forward(80, 1300);
  forward(70);
  delaySeconds(0.5);
  stop();

  // back off
  forward(80, -2000);

  // turn to face ball and 5th goal
  rotateDegrees(315);
  delaySeconds(0.2);

  // go to goal
  intake();
  rollBottom();
  forward(80, 3000);
  forward(70);
  delaySeconds(0.5);
  stop();
  intakeStop();
  rollersStop();
  delaySeconds(0.2);

  // put ball in 5th goal
  roll();
  delaySeconds(1.5);
  rollersStop();

  // back off
  forward(80, -500);
  */
}

void right() {
  deploy();

  // move forward
  forward(100, 1200);
  stop(0.3);

  // turn to 1st goal
  rollBottom();
  rotateDegrees(140);
  stop(0.3);
  intake();

  // go to 1st goal
  forward(80, 1550);
  forward(60);
  delaySeconds(0.5);
  intakeStop();
  stop(0.2);
  rollersStop();

  // put ball to goal
  roll();
  delaySeconds(0.8);
  rollersStop();

  // back off
  forward(100, -1200);
  rollBottom();
  intake();
  stop(0.2);

  // turn to face the wall
  rotateDegrees(180);
  stop(0.2);
  intakeStop();
  rollersStop();

  // straft to 2nd goal
  straft(100, 2050);
  stop(0.2);

  // move to goal
  forward(80);
  delaySeconds(0.7);

  // put ball in 2nd goal
  roll();
  delaySeconds(1);

  // back off
  rollersStop();
  forward(80, -1000);
  stop();
}
                                                                                                                                                                                                                                                                    
