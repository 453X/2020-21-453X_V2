#include "main.h"

void redHomeRow(){
  straft(80, -800);
  stop();
  delaySeconds(0.3);
  rotateDegrees(45);
  stop();
  intake();
  delaySeconds(0.1);
  forward(80, 1000);
  stop();
  roll(11000);
  delaySeconds(0.8);
  forward(-50);
  delaySeconds(0.2);
  forward(50);
  delaySeconds(0.2);
  stop();
  intakeStop();
  rollersStop();
  forward(80, -2000);
  stop();
  delaySeconds(0.2);
  rotateDegrees(90);
  straft(80, 2400);
  stop();
  delaySeconds(0.1);
  intake();
  forward(80, 1500);
  stop();
  sort(5);
  roll();
  forward(-40);
  delaySeconds(0.2);
  forward(40);
  delaySeconds(0.8);
  intakeStop();
  delaySeconds(0.3);
  rollersStop();
  forward(80, -2000);
  stop();





}
