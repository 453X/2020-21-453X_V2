#include "main.h"

void intakeControl() {
  bool buttonR1 = controller.get_digital(DIGITAL_R1);
  bool buttonR2 = controller.get_digital(DIGITAL_R2);
  bool buttonY = controller.get_digital(DIGITAL_Y);

  if (buttonR1) {
    intakeLeft.move_voltage(-12000);
    intakeRight.move_voltage(12000);
  }

  else if (buttonR2) {
    intakeLeft.move_voltage(12000);
    intakeRight.move_voltage(-12000);

  } else {
    intakeLeft.move(0);
    intakeRight.move(0);
  }
}

void intakeSetHold() {
  intakeLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  intakeRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void intake() {
  intakeLeft.move_voltage(12000);
  intakeRight.move_voltage(-12000);
  pros::delay(10);
}

void outtake(){
  intakeLeft.move_voltage(-12000);
  intakeRight.move_voltage(12000);
  pros::delay(10);
}
void intakeStop() {
  intakeLeft.move_voltage(0);
  intakeRight.move_voltage(0);
}

void resetIntakeEncoders() {
  intakeLeft.tare_position();
  intakeRight.tare_position();
}

double avgIntakeEncoder() {
  return (fabs(intakeLeft.get_position()) + fabs(intakeRight.get_position())) /
         2;
}

void intakePositioning(int units, double seconds, double rTotalTime , int loop, double rSeconds, int power) {
  intake();
  delaySeconds(0.7);
  forward(80, units);
  forwardSeconds(80, seconds);
  forwardSeconds(-50, 0.2);
  stop();
  //rollMove(loop, rSeconds, power);
  rollMove2(loop, rTotalTime, rSeconds,power) ;
  intakeStop();
}
