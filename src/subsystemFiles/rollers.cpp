#include "main.h"

void rollersControl() {
  bool buttonL1 = controller.get_digital(DIGITAL_L1);
  bool buttonL2 = controller.get_digital(DIGITAL_L2);
  bool buttonY = controller.get_digital(DIGITAL_Y);
  bool buttonUp = controller.get_digital(DIGITAL_UP);
  bool buttonLeft = controller.get_digital(DIGITAL_LEFT);
  bool buttonRight = controller.get_digital(DIGITAL_RIGHT);
  bool buttonDown = controller.get_digital(DIGITAL_DOWN);

  optical.set_led_pwm(100);

  int timer = 0;
  if (buttonY) {

    // delay roll
      // if (timer >= 300) {
      //   roll();
      //
      // } else {
      //   rollTop();
      //   timer += 20;
      //   pros::lcd::print(2, "timer --> %lf", timer);
      // }

      roll();

  } else if (buttonL2) {
    poop();
  } else if (buttonL1) {
    rollBottom();
  } else if (buttonUp) {
    roll();
  } else if (buttonDown) {
    roll(-12000);
  } else if (buttonLeft) {
    poop();
  } else if (buttonRight) {
    poop();
  } else {
    roll(0);
    //timer = 0;
  }
}

void rollMove2(int times, double totalSeconds, double fbSeconds, int power) {
  optical.set_led_pwm(50);
  double timer = 0;

  int fbstatus = 0; // 0:backward , 1:stop , 2:forward
  double nextFBTime = 0;
  int fbTimes = 0;

  while (timer <= totalSeconds) {
    double hue = optical.get_hue();
    pros::lcd::print(1, "hue --> %lf", hue);
    pros::lcd::print(2, "timer --> %lf", timer);

    // forward & backward
    if (timer >= nextFBTime && fbTimes < times) {
      switch (fbstatus) {
      case 0:
        forward(-power);
        nextFBTime += fbSeconds;
        break;
      case 1:
        stop();
        nextFBTime += 0.3;
        break;
      case 2:
        forward(power);
        nextFBTime += fbSeconds;
        fbTimes++;
        break;
      }
      fbstatus++;
      fbstatus %= 3;

    } else if (fbTimes == times) {
      stop();
    }

    // red & skills
    if (hue > 120 && hue < 300) { // blue
      // poop
      rollersTop.move_voltage(-12000);
      rollersBottom.move_voltage(12000);
      delaySeconds(1);
      timer += 1;

    } else { // red
      // roll
      rollersTop.move_voltage(12000);
      rollersBottom.move_voltage(12000);
      delaySeconds(0.1);
      timer += 0.1;
    }
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
  rollersBottom.move_voltage(12000);
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

void rollTop() { rollersTop.move_voltage(12000); }

void poop() {
  rollersTop.move_voltage(-12000);
  rollersBottom.move_voltage(12000);
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
