#include "main.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  selector::init();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  calibrate();
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
   //pros::lcd::initialize();
   calibrate();
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  // selector ::auton == 1 : Red Left
  if (selector::auton == 1) {
    pros::lcd::initialize();
    inertial.reset();
    //forwardPID(2000);
    forwardPD(800);
    //rotateDegreesPD(90);
    delaySeconds(0.3);
    //rotateDegreesPD(180);
  }

  // selector::auton == 2 : Red Right
  if (selector::auton == 2) {
  }

  // selector::auton == 3 : Do Nothing
  if (selector::auton == 3) {
  }

  // selector::auton == 4 : Red Custom
  if (selector::auton == 4) {
    pros::lcd::initialize();
  //  intakePositioning(800, 0.1, 2, 0.4, 30);
  pros::lcd::print(1, "selector::auton == 4");
  maneuver(0,-60, 25, 0.9);
  stop();
  }

  // selector::auton == -1 : Blue Left
  if (selector::auton == -1) {
  }

  // selector::auton == -2 : Blue Right
  if (selector::auton == -2) {
  }

  // selector::auton == -3 : Do Nothing
  if (selector::auton == -3) {
  }

  // selector::auton == -4 : Blue Custom
  if (selector::auton == -4) {
  }

  // selector::auton == 0 : Skills
  if (selector::auton == 0) {
    intakeSetHold();
    skills();
  }
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  driveSetCoast();
  intakeSetHold();
  long t=0;
  while (true) {
    driverControl();
    rollersControl();
    intakeControl();
    // pros::lcd::print(0, "hue --> %lf", optical.get_hue());
    pros::delay(20);

  }
}
