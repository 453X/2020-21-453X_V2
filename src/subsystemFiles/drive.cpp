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
  double tolerance = 0.5;
  double bias = 0;
  while (true) {
    double heading = inertial.get_heading();
    if (heading < -360 || heading > 360) {
      continue;
    }
    bool turnRigh = false;
    double diff = heading - deg;
    // double diff = 60;
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

    // diff += bias;
    if (turnRigh)
      pros::lcd::print(3, "diff  >> %5.2f   RIGHT", diff);
    else
      pros::lcd::print(3, "diff  >> %5.2f   LEFT", diff);

    pros::lcd::print(4, "tole  >> %5.2f", tolerance);

    if (diff > tolerance) {
      double pow = 0;
      if (turnRigh == false) {
        // turn A(diff) Left
        // pow = -20 + diff / -2;
        if (diff < 20) {
          pow = -35;
        } else {
          pow = -70;
        }
      } else {
        // turn B(diff) right
        // pow = 20 + diff / 2;
        if (diff < 20) {
          pow = 35;
        } else {
          pow = 70;
        }
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

void rotateDegreesPD(double deg) {
  double tolerance = 4;
  double bias = 0;

  double error = 0;
  double derivative;
  double prevError = 0;

  double kP = 3.2;
  double kD = 2;

  if (deg >= 180) {
    deg -= 2;
  } else {
    deg += 3;
  }

  while (true) {
    double heading = inertial.get_heading();

    error = heading - deg;

    if (heading < -360 || heading > 360) {
      continue;
    }
    bool turnRigh = false;
    double error = heading - deg;
    // double error = 60;
    if (error > 0) {
      if (error > 180) {
        // right
        error = 360 - error;
        turnRigh = true;
      } else {
        // left
        turnRigh = false;
      }
    } else {
      if (error < -180) {
        // left
        error = 360 + error;
        turnRigh = false;
      } else {
        // right
        error = error * -1;
        turnRigh = true;
      }
    }

    // error += bias;
    if (turnRigh)
      pros::lcd::print(3, "error  >> %5.2f   RIGHT", error);
    else
      pros::lcd::print(3, "error  >> %5.2f   LEFT", error);

    pros::lcd::print(4, "tole  >> %5.2f", tolerance);

    if (error > tolerance) {
      double pow = 0;
      if (turnRigh == false) {
        // turn A(error) Left
        pow = -error * kP - derivative * kD;
        // pow = -20 + error / -2;

      } else {
        // turn B(error) right
        // pow = 20 + error / 2;
        pow = error * kP + derivative * kD;
      }
      turn(pow);
      pros::lcd::print(2, "TURN  >> %5.2f", pow);
    } else {
      turn(0);
      break;
    }
    derivative = error - prevError;
    prevError = error;
    pros::delay(15);
    pros::lcd::print(0, "heading  >> %5.2f", heading);
    pros::lcd::print(1, "target   >> %5.2f", deg);
    driveSetHold();
    forward(0);
  }
}

void forwardAccel(int constant, int pd) {
  forwardAcceleration(2);
  forwardPD(pd);
}

void maneuverAccel(int forward, int straft, int turn, int constant, int pd) {
  maneuverAcceleration(forward, straft, turn, constant);
  maneuverPD(forward, straft, turn, pd);
}

void forwardPD(int units) { // power in positive, units in positive or negative
  resetDriveEncoders();
  int direction = abs(units) / units;
  double rotation = inertial.get_rotation();
  int power = 0;
  int setPoint = abs(units);

  double kP = 0.1;
  double kD = 0.2;

  while (avgDriveEncoders() < abs(units)) {
    int tune = 5;
    double tolerance = 0.3;

    double error = setPoint - avgDriveEncoders();
    double prevError = 0;
    double derivative;

    power = direction * (error * kP + derivative * kD);

    // pros::lcd::print(0, "Get encoder  >> %f\n",
    // fabs(driveLF.get_position()));
    pros::lcd::print(0, "rotation  >> %5.2f", inertial.get_rotation());
    pros::lcd::print(1, "encoder value  >> %5.2f", avgDriveEncoders());
    pros::lcd::print(2, "error   >> %5.2f", error);

    derivative = error - prevError;
    prevError = error;

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

void straftPD(int units) { // power in positive, units in positive or negative
  resetDriveEncoders();
  int direction = abs(units) / units;
  double rotation = inertial.get_rotation();
  int power = 0;
  int setPoint = abs(units);

  double kP = 0.1;
  double kD = 0.2;

  while (avgDriveEncoders() < abs(units)) {
    int tune = power * 0.3;
    double tolerance = 0.3;

    double error = setPoint - avgDriveEncoders();
    double prevError = 0;
    double derivative;

    power = direction * (error * kP + derivative * kD);

    // pros::lcd::print(0, "Get encoder  >> %f\n",
    // fabs(driveLF.get_position()));
    pros::lcd::print(0, "rotation  >> %5.2f", inertial.get_rotation());
    pros::lcd::print(1, "encoder value  >> %5.2f", avgDriveEncoders());
    pros::lcd::print(2, "error   >> %5.2f", error);

    derivative = error - prevError;
    prevError = error;

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

void straftAccel(int constant, int pd) {
  straftAcceleration(constant);
  straftPD(pd);
}

void straftAcceleration(double constant) {
  double timer = 0;
  double rotation = inertial.get_rotation();

  double tolerance = 0.3;

  while (true) {
    double tune = timer * 0.1;

    if (constant >= 0) {
      if (timer >= 127) {
        break;
      } else {
        straft(timer);

        if (inertial.get_rotation() > rotation + tolerance) {
          driveLF.move(timer - tune);
          driveLB.move(-timer - tune);
          driveRF.move(timer - tune);
          driveRB.move(-timer - tune);

        } else if (inertial.get_rotation() < rotation - tolerance) {
          driveLF.move(timer + tune);
          driveLB.move(-timer + tune);
          driveRF.move(timer + tune);
          driveRB.move(-timer + tune);

        } else {
          driveLF.move(timer);
          driveLB.move(-timer);
          driveRF.move(timer);
          driveRB.move(-timer);
        }

        timer += constant * 0.001;
        pros::lcd::print(2, "timer --> %lf", timer);
      }
    } else {
      if (timer <= -127) {
        break;
      } else {
        straft(timer);
        timer += constant * 0.001;
        pros::lcd::print(2, "timer --> %lf", timer);
      }
    }
  }
}

void forwardAcceleration(double constant) {
  double timer = 0;

  while (true) {
    if (constant >= 0) {
      if (timer >= 127) {
        break;
      } else {
        forward(timer);
        timer += constant * 0.001;
        pros::lcd::print(2, "timer --> %lf", timer);
      }
    } else {
      if (timer <= -127) {
        break;
      } else {
        forward(timer);
        timer += constant * 0.001;
        pros::lcd::print(2, "timer --> %lf", timer);
      }
    }
  }
}

void backwardAcceleration(double constant) {
  double timer = 0;

  while (true) {
    if (timer >= -127) {
      break;
    } else {
      forward(timer);
      timer -= constant * 0.001;
      pros::lcd::print(2, "timer --> %lf", timer);
    }
  }
}

void maneuverAcceleration(int forward, int straft, int turn, double constant) {
  int timer = 0;
  double forward2 = 0;
  double straft2 = 0;
  double turn2 = 0;

  while (true) {
    if (timer >= 127) {
      break;
    } else {
      forward2 = timer * (forward * 0.01);
      straft2 = timer * (straft * 0.01);
      turn2 = timer * (turn * 0.01);

      maneuver(forward2, straft2, turn2);
      timer = timer + constant;
    }
  }
}

void distancePD(int setPoint) {
  resetDriveEncoders();
  driveSetHold();

  int direction = abs(setPoint) / setPoint;
  double rotation = inertial.get_rotation();

  double power = 0;

  int tune = 0;
  double tolerance = 10;

  double c = 1;

  double kP = 0.5;
  double kD = 0.5;

  double dist = distance.get();
  double error = dist - setPoint;
  double prevError = 0;
  double derivative;

  while (error >= tolerance) {
    dist = distance.get();
    pros::lcd::print(1, "error   >> %5.2f", error);
    pros::lcd::print(2, "distance   >> %5.2f", dist);

    // Proportional
    error = dist - setPoint;

    // Derivative
    derivative = prevError - error;

    power = c * (error * kP + derivative * kD) * direction;

    if (power >= 127) {
      power = 127;
    } else if (power < 40) {
      power = 40;
    }

    prevError = error;

    tune = power * 0.2;

    if (inertial.get_rotation() > rotation + tolerance) {
      forward(power - tune);

    } else if (inertial.get_rotation() < rotation - tolerance) {
      forward(power + tune);

    } else {
      forward(power);
    }

    pros::delay(15);
  }

  stop();
}

void distance2PD(int setPoint) {
  resetDriveEncoders();
  driveSetHold();

  int direction = abs(setPoint) / setPoint;
  double rotation = inertial.get_rotation();

  double power = 0;

  int tune = 0;
  double tolerance = 10;

  double c = 1;

  double kP = 0.5;
  double kD = 0.5;

  double dist = distance2.get();
  double error = dist - setPoint;
  double prevError = 0;
  double derivative;

  while (error >= tolerance) {
    dist = distance2.get();
    pros::lcd::print(1, "error   >> %5.2f", error);
    pros::lcd::print(2, "distance   >> %5.2f", dist);

    // Proportional
    error = dist - setPoint;

    // Derivative
    derivative = prevError - error;

    power = c * (error * kP + derivative * kD) * direction;

    prevError = error;

    tune = power * 0.2;

    if (inertial.get_rotation() > rotation + tolerance) {
      straft(-power - tune);

    } else if (inertial.get_rotation() < rotation - tolerance) {
      straft(-power + tune);

    } else {
      straft(-power);
    }

    pros::delay(15);
  }

  stop();
}

void maneuverPD(int forward, int straft, int turn, int units) {
  resetDriveEncoders();
  int direction = abs(units) / units;
  double rotation = inertial.get_rotation();
  double power = 0;

  double kP = 0.6;
  double kD = 0.3;

  double error = 0;
  double derivative;
  double prevError = 0;

  double avgEncoder = avgDriveEncoders();
  while (avgEncoder < abs(units)) {

    int tune = 0;
    double tolerance = 0.3;

    error = abs(units) - avgEncoder;

    power = error * kP + derivative * kD;

    if (power >= 127) {
      power = 127;
    } else if (power < 50) {
      power = 50;
    }

    tune = power * 0.1;
    // pros::lcd::print(0, "Get encoder  >> %f\n",
    // fabs(driveLF.get_position()));
    pros::lcd::print(0, "rotation  >> %5.2f", inertial.get_rotation());
    pros::lcd::print(1, "encoder value  >> %5.2f", avgEncoder);
    pros::lcd::print(2, "error   >> %5.2f", error);
    pros::lcd::print(3, "power   >> %5.2f", power);

    derivative = error - prevError;
    prevError = error;

    double total = fabs(forward) + fabs(straft);
    forward = power * forward/total;
    straft = power * straft/total;
    //turn = power * (turn * 0.01);

    if (inertial.get_rotation() > rotation + tolerance) {
      driveLF.move(forward + straft + turn - tune);
      driveLB.move(forward - straft + turn - tune);
      driveRF.move(-forward + straft + turn - tune);
      driveRB.move(-forward - straft + turn - tune);

    } else if (inertial.get_rotation() < rotation - tolerance) {
      driveLF.move(forward + straft + turn + tune);
      driveLB.move(forward - straft + turn + tune);
      driveRF.move(-forward + straft + turn + tune);
      driveRB.move(-forward - straft + turn + tune);

    } else {
      driveLF.move(forward + straft + turn);
      driveLB.move(forward - straft + turn);
      driveRF.move(-forward + straft + turn);
      driveRB.move(-forward - straft + turn);
    }

    pros::delay(15);
    avgEncoder = avgDriveEncoders();
  }
  stop(0);
}

void calibrate() {
  // pros::lcd::initialize();
  inertial.reset();
  while (inertial.is_calibrating()) {
    pros::delay(20);
  }
  delaySeconds(0.5);
}

/**
  parm:
  - power : -127 ~ 127
*/
void turn(double power) {
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

void maneuver(int forward, int straft, int turn) {
  driveLF.move(forward + straft + turn);
  driveLB.move(forward - straft + turn);
  driveRF.move(-forward + straft + turn);
  driveRB.move(-forward - straft + turn);
}

void maneuver(int forward, int straft, int turn, double seconds) {
  driveLF.move(forward + straft + turn);
  driveLB.move(forward - straft + turn);
  driveRF.move(-forward + straft + turn);
  driveRB.move(-forward - straft + turn);
  delaySeconds(seconds);
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
  stop();
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

    // if (avgDriveEncoders() > abs(units) * 0.7) {
    //   power = 50 * direction;
    // }

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
}

void forwardDistance(int power, int mm) {
  while (distance.get() > mm) {
    forward(power);
    pros::delay(10);
  }
  stop();
}

void straft(int power) { // left in positive, right in negative
  driveLF.move(power);
  driveLB.move(-power);
  driveRF.move(power);
  driveRB.move(-power);
}

void straftSeconds(int power,
                   double seconds) { // left in positive, right in negative
  driveLF.move(power);
  driveLB.move(-power);
  driveRF.move(power);
  driveRB.move(-power);
  delaySeconds(seconds);
}

void straft(int power,
            int units) { // power in positive, units in positive or negative
  resetDriveEncoders();
  int direction = abs(units) / units;
  double rotation = inertial.get_rotation();
  while (true) {
    if (rotation > -100000 && rotation < 100000) {
      break;
    }
    rotation = inertial.get_rotation();
  }
  power *= direction;

  while (avgDriveEncoders() < abs(units)) {
    int tune = 5;
    double tolerance = 0.5;

    if (avgDriveEncoders() > abs(units) * 0.7) {
      power = 50 * direction;
    }

    // pros::lcd::print(0, "Get encoder  >> %f\n",
    // fabs(driveLF.get_position()));

    double currentRotation = inertial.get_rotation();
    pros::lcd::print(0, "rotation  >> %5.2f", currentRotation);
    pros::lcd::print(1, "direction  >> %d", direction);
    pros::lcd::print(2, "power  >> %5.2f", power);

    if (currentRotation < -100000 || currentRotation > 100000) {
      continue;
    }

    if (currentRotation > rotation + tolerance) {
      driveLF.move(power - tune);
      driveLB.move(-power - tune);
      driveRF.move(power - tune);
      driveRB.move(-power - tune);

    } else if (currentRotation < rotation - tolerance) {
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

void forwardSeconds(int power, double seconds) {
  forward(power);
  delaySeconds(seconds);
}
