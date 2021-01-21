#include "main.h"

void rollersControl() {
  bool buttonL1 = controller.get_digital(DIGITAL_L1);
  bool buttonL2 = controller.get_digital(DIGITAL_L2);
  bool buttonY = controller.get_digital(DIGITAL_Y);

  optical.set_led_pwm(50);


  if (buttonY) {
    rollersTop.move_voltage(12000);
    rollersBottom.move_voltage(12000);

  } else if (buttonL2) {
    rollersTop.move_voltage(-12000);
    rollersBottom.move_voltage(-12000);

  } else if (buttonL1) { //auto sort
    double hue = optical.get_hue();

    if (selector::auton < 5) {     // red & skills
      if (hue > 120 && hue < 300) { // blue
        // poop
        rollersTop.move_voltage(-12000);
        rollersBottom.move_voltage(12000);
      } else { // red
        // roll
        rollersTop.move_voltage(12000);
        rollersBottom.move_voltage(12000);
      }

    } else {
      if (hue > 300 || hue < 60) { // red
        // poop
        rollersTop.move_voltage(-12000);
        rollersBottom.move_voltage(12000);

      } else { // blue
        // roll
        rollersTop.move_voltage(12000);
        rollersBottom.move_voltage(12000);
      }
    }

  } else {
    rollersTop.move(0);
    rollersBottom.move(0);
  }
}


void sort(int units){
  optical.set_led_pwm(50);

  for (int i = 0; i < 10000 * units; i++) {
    double hue = optical.get_hue();
    pros::lcd::print(2, "hue --> %lf", hue);
    pros::lcd::print(1, "i --> %d", i);

         // red & skills
    if (hue > 120 && hue < 300) { // blue
      // poop
      rollersTop.move_voltage(-12000);
      rollersBottom.move_voltage(12000);
      delaySeconds(1);
      break;

    } else { // red
      // roll
      rollersTop.move_voltage(12000);
      rollersBottom.move_voltage(12000);
    }

  }
  // else {
  //   if (hue > 300 || hue < 60) { // red
  //     // poop
  //     rollersTop.move_voltage(-12000);
  //     rollersBottom.move_voltage(12000);
  //
  //   } else { // blue
  //     // roll
  //     rollersTop.move_voltage(12000);
  //     rollersBottom.move_voltage(12000);
  //   }
  // }
}

void rollMove(int times, double seconds, int power){
  roll();
  for(int i = 0; i < times; i++){
    forward(-power);
    delaySeconds(seconds);
    stop(0.3);
    forward(power);
    delaySeconds(seconds);
  }
  rollersStop();
  stop();
}

void rollersSetCoast() {
  rollersTop.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  rollersBottom.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void rollersTopHold() {
  rollersTop.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  rollersTop.move(0);
}

void rollersBottomHold() {
  rollersBottom.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  rollersBottom.move(0);
}

void roll() {
  rollersTop.move_voltage(12000);
  rollersBottom.move_voltage(12000);
  pros::delay(10);
}

void rollBottom() {
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
