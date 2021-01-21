#include "main.h"

void redHomeRow(){
  straft(80, -800);
  stop();
  rotateDegrees(50);
  stop();
  intakePositioning(1000, 0.2, 2, 0.2, 20);
  forward(80, -2000);
  roll();
  stop();
  delaySeconds(0.2);
  rotateDegrees(90);
  rollersStop();
  straft(80, 2500);
  stop();
  delaySeconds(0.1);
  forward(80, 900);
  intakePositioning(100, 0.2, 2, 0.2, 20);
  forward(80, -2000);
  stop();
  rollersStop();





}
