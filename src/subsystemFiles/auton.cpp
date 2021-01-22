#include "main.h"

void rightHomeRow() {
  intakeSetHold();
//calibrate();
  maneuver(0,-60, 28, 0.9);
  stop();
  intakePositioning(650, 0.25, 1.6, 2, 0.2, 20);
  outtake();
  delaySeconds(0.2);
  intakeStop();
  forward(80, -2000);
  roll();
  stop();
  delaySeconds(0.2);
  rotateDegrees(90);
  rollersStop();
  straft(80, 2400);
  stop();
  outtake();
  delaySeconds(0.1);
  intakeStop();
  forward(80, 1500);
  intakePositioning(0, 0.2, 2, 2, 0.1, 20);
  forward(80, -1000);
  stop();


}
void skills(){
  roll();
  delaySeconds(0.2);
  rollersStop();
  rollBottom();
  forward(80, 700);
  intake();
  forward(80, 2200);
  forwardSeconds(80, 0.3);
  stop();
  delaySeconds(0.3);
  forward(100, -1200);
  stop();
  roll(-12000);
  delaySeconds(0.2);
  rollersStop();
  intakeStop();
  rotateDegrees(60);
  stop();
  intakePositioning(1300, 0.4, 0.8, 2, 0.2, 20);
  forward(100, -500);
  outtake();
  roll();
  forward(100, -2000);
  stop();
  rollersStop();
  intakeStop();
  rotateDegrees(280);
  straft(127);
  delaySeconds(1);
  straft(80);
  delaySeconds(0.5);
  stop();
  delaySeconds(0.3);
  calibrate();
  straft(80, -2500);
  stop();
  delaySeconds(0.5);
  outtake();
  delaySeconds(0.5);
  poop();
  forward(80, 1400);
  rollersStop();
  intake();
  forward(70, 700);
  rollBottom();
  delaySeconds(0.3);
  stop();
  rollersStop();
  intakeStop();
  rotateDegrees(90);
  stop();
  intakePositioning(2300, 0.3, 0.9, 2, 0.3, 20);
  stop();
  forward(80, -1200);
  rotateDegrees(180);
  stop();
  roll();
  forward(110, -4500);
  rollersStop();
  rollBottom();
  forward(80, -1000);
  forward(80);
  delaySeconds(0.3);
  stop();
  rollersStop();
  forward(90, 1200);
  stop();
  rotateDegrees(50);
  stop();
  intakePositioning(2300, 0.3, 0.9, 2, 0.3, 20);
  stop();
  forward(90, -2000);
  rotateDegrees(90);
  stop();


}
