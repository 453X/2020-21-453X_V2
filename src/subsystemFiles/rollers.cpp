#include "main.h"

void rollersControl() {
  bool buttonL1 = controller.get_digital(DIGITAL_L1);
  bool buttonL2 = controller.get_digital(DIGITAL_L2);
  bool buttonY = controller.get_digital(DIGITAL_Y);

  if (buttonL1) {
    rollersTop.move_voltage(-12000);
    rollersBottom.move_voltage(-12000);

  } else if (buttonL2) {
    rollersTop.move_voltage(12000);
    rollersBottom.move_voltage(12000);

  // } else if (buttonY) {
  //
  //   if (line1.get_value() < 2850) {
  //     rollersBottom.move_voltage(-12000);
  //     intakeLeft.move_voltage(12000);
  //     intakeRight.move_voltage(-12000);
  //     rollersTopHold();
  //   }
  //   if (line2.get_value() < 2860 && line1.get_value() < 2850) {
  //     intakeLeft.move_voltage(12000);
  //     intakeRight.move_voltage(-12000);
  //     rollersTopHold();
  //     rollersBottomHold();
  //   }
  //   if (line3.get_value() < 2865 && line2.get_value() < 2860 && line1.get_value() < 2850) {
  //     rollersTopHold();
  //     rollersBottomHold();
  //     intakeHold();
  //   }
  } else {
    rollersTop.move(0);
    rollersBottom.move(0);
  }
}
void rollersTopHold() {
  rollersTop.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  rollersTop.move(0);
}

void rollersBottomHold() {
  rollersBottom.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  rollersBottom.move(0);
}

void trackingBalls() {
  while (true) {
    bool buttonY = controller.get_digital(DIGITAL_Y);


    if (buttonY) {
      if (line1.get_value() < 2850) {
        rollersTop.move_voltage(0);
        rollersBottom.move_voltage(-12000);
        intakeLeft.move_voltage(12000);
        intakeRight.move_voltage(-12000);

      } else if (line2.get_value() < 2860 && line1.get_value() < 2850) {
        rollersTop.move_voltage(0);
        rollersBottom.move_voltage(0);
        intakeLeft.move_voltage(12000);
        intakeRight.move_voltage(-12000);

      } else if (line3.get_value() < 2865 && line2.get_value() < 2860 && line1.get_value() < 2850) {
        rollersTop.move_voltage(0);
        rollersBottom.move_voltage(0);
        intakeLeft.move_voltage(0);
        intakeRight.move_voltage(0);

      }else {
        rollersTop.move_voltage(-12000);
        rollersBottom.move_voltage(-12000);
        intakeLeft.move_voltage(12000);
        intakeRight.move_voltage(-12000);
      }
    }
    pros::delay(10);
  }
}

void roll(){
  rollersTop.move_voltage(-12000);
  rollersBottom.move_voltage(-12000);
  pros::delay(10);
}

void rollersStop(){
  rollersTop.move_voltage(0);
  rollersBottom.move_voltage(0);
}
