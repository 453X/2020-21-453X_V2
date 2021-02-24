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
  forwardAccel(-2, -1500);
  roll();
  stop();
  delaySeconds(0.2);
  rotateDegreesPD(90);
  rollersStop();
  straftAccel(2, 1550);
  stop();
  outtake();
  delaySeconds(0.1);
  intakeStop();
  intakePositioning(1000, 0.4, 2, 2, 0.1, 20);
  forward(80, -800);
  stop();

  maneuver(-75, 30, 0, 1.4);
  stop(0);
  rotateDegreesPD(270);
  intakeRight.move_voltage(12000);
  straft(120, 1000);
  intake();

  stop();


}
void skills(){
  //1st goal -> back off
  roll();
  delaySeconds(0.2);
  rollersStop();
  straft(80, -800);
  stop();
  forward(90, 500);
  intake();
  forward(90, 700);
  stop();
  rotateDegrees(30);
  stop();

  forward(90, 1700);
  forwardSeconds(90, 0.3);
  stop();
  forwardSeconds(-20, 0.2);
  roll();
  delaySeconds(0.7);
  rollersStop();
  stop();
  forward(90, -1200);
  roll();
  intake();
  forward(90, -1300);
  delaySeconds(0.2);
  stop();


  //2nd goal -> back off
  rollersStop();
  intakeStop();
  rotateDegrees(270);
  stop();
  forward(90, 1500);
  outtake();
  forward(70, 300);
  intake();
  rollBottom();
  forward(70, 1200);
  rollersStop();
  intakeStop();
  rotateDegrees(0);
  stop();
  intakePositioning(2300, 0.3, 0.9, 2, 0.3, 20);
  stop();
  forward(80, -1000);

  //3rd goal -> back off
  rotateDegrees(90);
  stop();
  roll();
  delaySeconds(0.5);
  rollersStop();
  forward(90, -4000);
  rollBottom();
  forward(80, -600);
  forwardSeconds(80, 0.3);
  stop();
  rollersStop();
  forward(90, 2000);
  stop();
  rotateDegrees(310);
  stop();
  intakePositioning(2200, 0.3, 0.6, 2, 0.3, 20);
  stop();
  forward(90, -2500);

  //4th goal -> back off
  rotateDegrees(0);
  roll(12000);
  straft(80, 300);
  forward(80, -2000);
  rollersStop();
  rollBottom();
  stop();
  // delaySeconds(0.4);
  // forward(90, -200);
  // rotateDegrees(270);
  // intakePositioning(2000, 0.3, 0.6, 2, 0.3, 20);
  // rollersStop();
  // stop();
  // forward(80,-1000);
  //
  // //5th goal -> back off
  // rotateDegrees(90);
  // rollBottom();
  // forward(100, -2500);
  // rollersStop();
  // intake();
  // rotateDegrees(225);
  // intakePositioning(2300, 0.3, 0.9, 2, 0.3, 20);
  // intakeStop();
  // stop();


  rotateDegrees(270);
  stop();
  intakePositioning(2000, 0.5, 0.8, 2, 0.3, 20);
  forward(80, -200);
  roll();
  forward(80, -200);
  stop();
  rollersStop();
  rotateDegrees(0);
  stop();
  roll();
  forward(90, -500);
  rollersStop();
  rollBottom();
  forward(90, -2300);
  stop();
  delaySeconds(0.3);
  rollersStop();
  rotateDegrees(235);
  stop();
  intakePositioning(1000, 0.3, 0.9, 2, 0.3, 20);
  forward(100, -1300);
  roll();
  forward(100, -1800);
  stop();
  rollersStop();

  rotateDegrees(90);
  stop();
  outtake();
  rollBottom();
  delaySeconds(0.3);
  poop();
  forward(90, 1100);
  rollersStop();
  intake();
  forward(90, 400);
  rotateDegrees(180);
  intakePositioning(1700, 0.3, 1, 2, 0.3, 20);
  forward(90, -400);
  stop();
  forward(80, -700);
  rotateDegrees(90);
  outtake();
  forward(90, 2800);
  intake();
  delaySeconds(0.4);
  forward(80, -800);
  rotateDegrees(135);
  stop();
  intakePositioning(2000, 0.3, 1, 2, 0.3, 20);
  stop();
  forward(90,-1000);
  rotateDegrees(45);
}

void firstGoal(){
  roll();
  delaySeconds(0.2);
  rollersStop();
}

void secondGoal(){
  straft(80, -800);
  stop();
  forward(90, 500);
  intake();
  forward(90, 700);
  stop();
  rotateDegreesPD(30);
  stop();

  forward(90, 1700);
  forwardSeconds(90, 0.3);
  stop();
  outtake();
  forwardSeconds(-20, 0.2);
  intake();
  roll();
  delaySeconds(0.8);
  rollersStop();
  stop(0.2);
  forward(90, -500);
  stop();
}

void thirdGoal(){
  rotateDegreesPD(75);
  outtake();
  roll(-12000);
  forward(120, -2600);
  intakeStop();
  rollersStop();
  rollBottom();
  forwardPD(-1600);
  rollersStop();
  intakeStop();
  rotateDegreesPD(357);
  stop();
  intakePositioning(2300, 0.3, 0.8, 2, 0.3, 20);
  stop();
}

void fourthGoal(){
  forward(90, -500);
  rotateDegreesPD(45);
  roll(-12000);
  outtake();
  stop(0.4);
  rotateDegreesPD(357);
  straft(100, -300);
  maneuverPD(0, -127, 0, 1700);
  stop();
  intake();
  distancePD(300);
  rollersStop();
  rollBottom();
  maneuverPD(-100, -80, 0, 1400);
  rotateDegreesPD(315);
  stop();
  maneuverPD(70, 35, 0, 1100);
  intakePositioning(0, 0.6, 0.5, 2, 0.25, 20);
  //forwardPD(-500);
  stop();
  forward(90, -500);
  stop();
}

void fifthGoal(){
  rotateDegreesPD(335);
  outtake();
  roll(-12000);
  forward(120, -2500);
  intakeStop();
  rollersStop();
  rollBottom();
  intakeStop();
  forwardPD(-1500);
  intakeStop();
  rotateDegreesPD(270);
  rollersStop();
  stop();
  intakePositioning(2300, 0.2, 0.5, 2, 0.3, 20);
  stop();
  forward(90, -200);
  stop();
}

void sixthGoal(){
  outtake();
  rotateDegreesPD(182);
  // intake();
  // poop();
  // forward(120, 1000);
  // outake();
  // forward(120, 500);
  // stop();
  // intake();
  // forward(120, 300);
  // maneuverPD(70, -10, 0, 1300);
  // distancePD(300);
  // maneuverPD(-80, 100, 0, 800);
  // stop();
  // rotateDegreesPD(225);
  // stop();
  poop();
  forward(90, 1900);
  intake();
  rollersStop();
  forwardPD(1700);
  stop();
  rotateDegreesPD(240);
  stop();

  forward(90, 1700);
  forwardSeconds(90, 0.3);
  stop();
  outtake();
  forwardSeconds(-20, 0.2);
  intake();
  roll();
  delaySeconds(0.8);
  rollersStop();
  stop(0.2);
  forward(90, -500);
  stop();
}

void seventhGoal(){
  rotateDegreesPD(260);
  outtake();
  roll(-12000);
  forward(120, -2600);
  rollersStop();
  intakeStop();
  rollBottom();
  forwardPD(-1900);
  //forward(90, 500);
  rotateDegreesPD(180);
  rollersStop();
  intakeStop();
  stop();
  intakePositioning(2300, 0.3, 0.6, 2, 0.3, 20);
  stop();
}

void eighthGoal(){
  forward(90, -800);
  rotateDegreesPD(225);
  roll(-12000);
  outtake();
  stop(0.4);
  rotateDegreesPD(180);
  rollersStop();
  straft(100, -300);
  maneuverPD(0, -127, 0, 2000);
  stop();
  intake();
  distancePD(300);
  rollersStop();
  rollBottom();
  maneuverPD(-95, -65, 0, 1300);
  rotateDegreesPD(135);
  rollersStop();
  stop();
  maneuverPD(70, 25, 0, 1100);
  intakePositioning(0, 0.3, 0.5, 2, 0.25, 20);
  //forwardPD(-500);
  stop();
  forward(90, -500);
}

void descoreCenter(int balls){
  for(int i = 0; i < balls; i++){
    forward(110);
    delaySeconds(0.5);
    forward(110, -500);
  }
}

void centerGoal(){
  rotateDegreesPD(170);
  roll();
  intake();
  forward(120, -2000);
  intakeStop();
  rollersStop();
  rollBottom();
  forwardPD(-2500);
  rotateDegreesPD(272);
  forwardSeconds(110, 0.7);
  forwardSeconds(-110, 0.4);

  descoreCenter(2);
  outtake();
  maneuver(90, 0, -20, 0.7);
  roll();
  delaySeconds(1);
  rollersStop();
  intakeStop();
  forward(110, -1000);
  stop();

  // forwardPD(-2100);
  // rotateDegreesPD(272);
  // outtake();
  // stop(0.5);
  // forward(120, 700);
  // forwardSeconds(90, 0.5);
  // forwardSeconds(-60, 0.3);
  // stop();
  // intake();
  // roll();
  // delaySeconds(1);
  // poop();
  // delaySeconds(1.5);
  // rollersStop();
  // outtake();
  // stop();
}





void skills126(){
  driveSetHold();

  firstGoal();
  secondGoal();
  thirdGoal();
  fourthGoal();
  fifthGoal();
  sixthGoal();
  seventhGoal();
  eighthGoal();
  centerGoal();



  // intake();
  // rollBottom();
  // forwardAccel(1.5, 900);
  // rotateDegreesPD(90);
  // outtake();
  // forwardAcceleration(1.5);
  // distancePD(300);
  // intake();
  // stop(0.3);
  // maneuver(-90, 90, 0, 0.6);
  // intakeStop();
  // stop();
  // rotateDegreesPD(135);
  // intakePositioning(1200, 0.5, 1.6, 2, 0.2, 20);
  // stop();
  // rollersStop();
  // intakeStop();

  //1st goal -> back off






  // roll(-12000);
  // outtake();
  // forward(90, -700);
  // rotateDegreesPD(357);
  // straftPD(-2500);
  // stop();
  // intake();
  // distancePD(300);
  // rollBottom();
  // maneuverPD(-100, -70, 0, 1200);
  // rotateDegreesPD(345);
  // stop();
  // maneuverPD(70, 20, 0, 1000);
  // intakePositioning(0, 0.3, 0.7, 2, 0.3, 20);
  // forwardPD(-1000);
  // stop();
  // forward(90, -500);
  // stop();
  // rotateDegreesPD(350);
  // roll();
  // forward(120, -2600);
  // rollBottom();
  // forwardPD(-2500);
  // rollersStop();
  // intakeStop();
  // forward(90, 500);
  // rotateDegreesPD(270);
  // stop();
  // intakePositioning(2300, 0.3, 1.0, 2, 0.3, 20);
  // stop();










}
