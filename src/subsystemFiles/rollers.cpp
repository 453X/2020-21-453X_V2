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

  } else if (buttonL1) { // auto sort
  //   double hue = optical.get_hue();
  //
  //   if (selector::auton >= 0) {      // red & skills
  //     if (hue > 120 && hue < 300) { // blue
  //       // poop
  //       rollersTop.move_voltage(-12000);
  //       rollersBottom.move_voltage(12000);
  //     } else { // red
  //       // roll
  //       rollersTop.move_voltage(12000);
  //       rollersBottom.move_voltage(12000);
  //     }
  //
  //   } else {
  //     if (hue > 300 || hue < 60) { // red
  //       // poop
  //       rollersTop.move_voltage(-12000);
  //       rollersBottom.move_voltage(12000);
  //
  //     } else { // blue
  //       // roll
  //       rollersTop.move_voltage(12000);
  //       rollersBottom.move_voltage(12000);
  //     }
  //   }
  //
  // } else {
  //   rollersTop.move(0);
  //   rollersBottom.move(0);
  // }

  double hue = optical.get_hue();
  bool color = true;

  if(optical.get_proximity() < 100){
    if (selector::auton >= 0) {      // red & skills
      if (hue > 120 && hue < 300) { // blue
        color = false;
      } else { // red
        color = true;
      }

    } else {
      if (hue > 300 || hue < 60) { // red
        color = false;
      } else { // blue
        color = true;
      }
    }
  }

  if(color){
    roll();
  } else {
    poop();
  }



} else {
  rollersTop.move(0);
  rollersBottom.move(0);
}
}

void sort(int units) {
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

void rollMove(int times, double seconds, int power) {
  roll();
  for (int i = 0; i < times; i++) {
    forward(-power);
    delaySeconds(seconds);
    stop(0.3);
    forward(power);
    delaySeconds(seconds);
  }
  rollersStop();
  stop();
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

void rollTop(){

}

void poop(){
  rollersTop.move_voltage(-12000);
  rollersBottom.move_voltage(12000);
}

void delayRoll(){
  resetRollersEncoders();

  while(rollersTop.get_position() < 1000){
    rollTop();
  }

  roll();
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
