#include "main.h"

void driverControl() {
  int leftJoystickX = controller.get_analog(ANALOG_LEFT_X);
  int leftJoystickY = controller.get_analog(ANALOG_LEFT_Y);
  int rightJoystickX = controller.get_analog(ANALOG_RIGHT_X);
  int rightJoystickY = controller.get_analog(ANALOG_RIGHT_Y);

  driveLF.move(rightJoystickY + rightJoystickX + leftJoystickX);
  driveLB.move(rightJoystickY - rightJoystickX + leftJoystickX);
  driveRF.move(-rightJoystickY + rightJoystickX + leftJoystickX);
  driveRB.move(-rightJoystickY - rightJoystickX + leftJoystickX);
}

/**
  parm:
  - power : -127 ~ 127
*/
void turn(int power) {
  driveLF.move(power);
  driveLB.move(power);
  driveRF.move(power);
  driveRB.move(power);
}

void turn(int power, int units) {
  int direction = abs(units) / units;

  resetDriveEncoders();
  while (fabs(driveLF.get_position()) < abs(units)) {
    turn(power * direction);
    pros::delay(10);
  }
}

void driveSetHold() {
  driveLF.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  driveLB.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  driveRF.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  driveRB.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void driveSetBrake() {
  driveLF.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  driveLB.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  driveRF.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  driveRB.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}

void driveSetCoast() {
  driveLF.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  driveLB.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  driveRF.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  driveRB.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void rotateDegrees(double deg) {
  double tolerance = 0.3;
  double bias = 0;
  while (true) {
    double heading = inertial.get_heading();
    bool turnRigh = false;
    double diff = heading - deg;
    if (diff > 0) {
      if (diff > 180) {
        // right
        diff = 360 - diff;
        turnRigh = true;
      } else {
        // left
        turnRigh = false;
      }
    } else {
      if (diff < -180) {
        // left
        diff = 360 + diff;
        turnRigh = false;
      } else {
        // right
        diff = diff * -1;
        turnRigh = true;
      }
    }

    diff += bias;
    if (diff > tolerance) {
      double pow = 0;
      if (turnRigh == false) {
        // turn A(diff) Left
        pow = -20 + diff / -2;
      } else {
        // turn B(diff) right
        pow = 20 + diff / 2;
      }
      turn(pow);
      pros::lcd::print(2, "TURN  >> %5.2f", pow);
    } else {
      turn(0);
      break;
    }
    pros::delay(50);
    pros::lcd::print(0, "heading  >> %5.2f", heading);
    pros::lcd::print(1, "target   >> %5.2f", deg);
    driveSetHold();
    forward(0);
  }
}

void calibrate() {
  // pros::lcd::initialize();
  inertial.reset();
  while (inertial.is_calibrating()) {
    pros::delay(20);
  }
}

void maneuver(int forward, int straft, int turn) {
  driveLF.move(forward + straft + turn);
  driveLB.move(forward - straft + turn);
  driveRF.move(-forward + straft + turn);
  driveRB.move(-forward - straft + turn);
}

void maneuver(int forward, int straft, int turn, int units) {
  while (avgDriveEncoders() < abs(units)) {
    driveLF.move(forward + straft + turn);
    driveLB.move(forward - straft + turn);
    driveRF.move(-forward + straft + turn);
    driveRB.move(-forward - straft + turn);
  }
}

void maneuverForward(int forward, int straft, int units) {
  resetDriveEncoders();
  int direction = abs(units) / units;
  double rotation = inertial.get_rotation();

  while (avgDriveEncoders() < abs(units)) {
    int tune = 5;
    double tolerance = 0.5;
    forward *= direction;
    straft *= direction;

    if (avgDriveEncoders() > abs(units) * 0.7) {
      forward = 50;
      straft = 50;
    }

    // pros::lcd::print(0, "Get encoder  >> %f\n",
    // fabs(driveLF.get_position()));
    pros::lcd::print(0, "rotation  >> %5.2f", inertial.get_rotation());

    if (inertial.get_rotation() > rotation + tolerance) {
      driveLF.move(forward + straft - tune);
      driveLB.move(forward - straft - tune);
      driveRF.move(-forward + straft - tune);
      driveRB.move(-forward - straft - tune);

    } else if (inertial.get_rotation() < rotation - tolerance) {
      driveLF.move(forward + straft + tune);
      driveLB.move(forward - straft + tune);
      driveRF.move(-forward + straft + tune);
      driveRB.move(-forward - straft + tune);

    } else {
      driveLF.move(forward + straft);
      driveLB.move(forward - straft);
      driveRF.move(-forward + straft);
      driveRB.move(-forward - straft);
    }

    pros::delay(10);
  }
  stop(0);
}

void forward(int power) {
  driveLF.move(power);
  driveLB.move(power);
  driveRF.move(-power);
  driveRB.move(-power);
}

void forward(int power,
             int units) { // power in positive, units in positive or negative
  resetDriveEncoders();
  int direction = abs(units) / units;
  double rotation = inertial.get_rotation();
  power *= direction;

  while (avgDriveEncoders() < abs(units)) {
    int tune = 5;
    double tolerance = 0.3;

    if (avgDriveEncoders() > abs(units) * 0.7) {
      power = 50 * direction;
    }

    // pros::lcd::print(0, "Get encoder  >> %f\n",
    // fabs(driveLF.get_position()));
    pros::lcd::print(0, "rotation  >> %5.2f", inertial.get_rotation());

    if (inertial.get_rotation() > rotation + tolerance) {
      driveLF.move(power - tune);
      driveLB.move(power - tune);
      driveRF.move(-power - tune);
      driveRB.move(-power - tune);

    } else if (inertial.get_rotation() < rotation - tolerance) {
      driveLF.move(power + tune);
      driveLB.move(power + tune);
      driveRF.move(-power + tune);
      driveRB.move(-power + tune);

    } else {
      driveLF.move(power);
      driveLB.move(power);
      driveRF.move(-power);
      driveRB.move(-power);
    }

    pros::delay(10);
  }
  stop(0);
}

void straft(int power) {
  driveLF.move(power);
  driveLB.move(-power);
  driveRF.move(power);
  driveRB.move(-power);
}

void straft(int power,
            int units) { // power in positive, units in positive or negative
  resetDriveEncoders();
  int direction = abs(units) / units;
  double rotation = inertial.get_rotation();
  power *= direction;

  while (avgDriveEncoders() < abs(units)) {
    int tune = 5;
    double tolerance = 0.5;

    if (avgDriveEncoders() > abs(units) * 0.7) {
      power = 50 * direction;
    }

    // pros::lcd::print(0, "Get encoder  >> %f\n",
    // fabs(driveLF.get_position()));
    pros::lcd::print(0, "rotation  >> %5.2f", inertial.get_rotation());

    if (inertial.get_rotation() > rotation + tolerance) {
      driveLF.move(power - tune);
      driveLB.move(-power - tune);
      driveRF.move(power - tune);
      driveRB.move(-power - tune);

    } else if (inertial.get_rotation() < rotation - tolerance) {
      driveLF.move(power + tune);
      driveLB.move(-power + tune);
      driveRF.move(power + tune);
      driveRB.move(-power + tune);

    } else {
      driveLF.move(power);
      driveLB.move(-power);
      driveRF.move(power);
      driveRB.move(-power);
    }

    pros::delay(10);
  }
  stop(0);
}

void stop() {
  driveLF.move(0);
  driveLB.move(0);
  driveRF.move(0);
  driveRB.move(0);
}

void stop(double seconds) {
  driveLF.move(0);
  driveLB.move(0);
  driveRF.move(0);
  driveRB.move(0);
  pros::delay(seconds * 1000);
}

void resetDriveEncoders() {
  driveLF.tare_position();
  driveLB.tare_position();
  driveRF.tare_position();
  driveRB.tare_position();
}

void delaySeconds(double seconds) { pros::delay(seconds * 1000); }

double avgDriveEncoders() {
  return (fabs(driveLF.get_position()) + fabs(driveLB.get_position()) +
          fabs(driveRF.get_position()) + fabs(driveRB.get_position())) /
         4;
}
