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

  } else if (buttonY) {
    if (line1.get_value() < 2200) { // if ball on top

      if (line2.get_value() < 2700) { // if ball on bottom and on top
        rollersTop.move(0);
        rollersBottom.move(0);
        intake();

      } else { // if ball on top but not on bottom
        rollersTop.move(0);
        rollersBottom.move_voltage(-12000);
        intake();
      }

    } else { // if ball not on top or bottom
      roll();
      intake();
    }

    pros::delay(10);

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
  pros::lcd::initialize();
  pros::lcd::print(0, "line1  >> %5d", line1.get_value());
  pros::lcd::print(1, "line2  >> %5d", line2.get_value());

  if (line1.get_value() < 2200) { // if ball on top

    if (line2.get_value() < 2700) { // if ball on bottom and on top
      rollersTop.move(0);
      rollersBottom.move(0);
      intake();

    } else { // if ball on top but not on bottom
      rollersTop.move(0);
      rollersBottom.move_voltage(-12000);
      intake();
    }

  } else { // if ball not on top or bottom
    roll();
    intake();

  }

  pros::delay(10);
}

void roll() {
  rollersTop.move_voltage(-12000);
  rollersBottom.move_voltage(-12000);
  pros::delay(10);
}

void rollBottom(){
  rollersBottom.move_voltage(-12000);
  pros::delay(10);
}

void roll(int voltage) {
  rollersTop.move_voltage(voltage);
  rollersBottom.move_voltage(voltage);
  pros::delay(10);
}

void roll(int voltage, int units) {
  resetRollersEncoders();
  while (avgRollerEncoder() < abs(units)) {
    rollersTop.move_voltage(voltage);
    rollersBottom.move_voltage(voltage);
    pros::delay(10);
  }
}

void rollersStop() {
  rollersTop.move_voltage(0);
  rollersBottom.move_voltage(0);
}

double avgRollerEncoder() {
  return (fabs(rollersTop.get_position()) +
          fabs(rollersBottom.get_position())) /
         2;
}

void resetRollersEncoders() {
  rollersTop.tare_position();
  rollersBottom.tare_position();
}
