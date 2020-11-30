#include "main.h"
void intakeControl() {
  bool buttonR1 = controller.get_digital(DIGITAL_R1);
  bool buttonR2 = controller.get_digital(DIGITAL_R2);
  bool buttonY = controller.get_digital(DIGITAL_Y);

  if (buttonR1) {
    intakeLeft.move_voltage(-12000);
    intakeRight.move_voltage(12000);
  } else if (buttonR2) {
     intakeLeft.move_voltage(12000);
    intakeRight.move_voltage(-12000);

  } else if (buttonY) {
    intakeLeft.move_voltage(12000);
    intakeRight.move_voltage(-12000);
    rollersTop.move_voltage(12000);
    rollersBottom.move_voltage(-12000);

  } else {
    intakeLeft.move(0);
    intakeRight.move(0);
  }
}

void intakeHold() {
  intakeLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  intakeRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  intakeLeft.move(0);
  intakeRight.move(0);
}

void intake(){
  intakeLeft.move_voltage(12000);
  intakeRight.move_voltage(-12000);
  pros::delay(10);
}

void intakeStop(){
  intakeLeft.move_voltage(0);
  intakeRight.move_voltage(0);
}
