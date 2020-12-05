#include "main.h"
#include "autoSelect/selection.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initialize() {
  driveSetHold();
  intakeSetHold();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on
  the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  selector::init();
  resetDriveEncoders();
  resetIntakeEncoders();
  resetRollersEncoders();
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

  if (selector::auton == 1) {
    left();
  } // selector ::auton == 1 : Red Left
  if (selector::auton == 2) {
    right();
  } // selector::auton == 2 : Red Right
  if (selector::auton == 3) {
    delaySeconds(13);
    deploy();
  } // selector::auton == 3 : Do Nothing
  if (selector::auton == 4) {

  } // selector::auton == 4 : Red Custom
  if (selector::auton == -1) {
    left();
  } // selector::auton == -1 : Blue Left
  if (selector::auton == -2) {
    right();
  } // selector::auton == -2 : Blue Right
  if (selector::auton == -3) {

  } // selector::auton == -3 : Do Nothing
  if (selector::auton == -4) {
    deploy();

    // move forward
    forward(100, 1200);
    stop(0.3);

    // turn to 1st goal
    rollBottom();
    rotateDegrees(140);
    stop(0.3);
    intake();

    // go to 1st goal
    forward(80, 1550);
    forward(60);
    delaySeconds(0.5);
    intakeStop();
    stop(0.2);
    rollersStop();

    // put ball to goal
    roll();
    delaySeconds(1.7);
    rollersStop();

    // back off
    forward(100, -1200);
    rollBottom();
    intake();
    stop(0.2);
    intakeStop();
    rollersStop();
  } // selector::auton == -4 : Blue Custom
  if (selector::auton == 0) {
    skills();
  } // selector::auton == 0 : Skills
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

  while (true) {
    if (button.get_new_press()) {
      inertial.reset();
      pros::lcd::print(0, "RESET \n");

    } else {

      pros::lcd::print(0, "Get rotation  >> %f\n", inertial.get_rotation());
    }

    driverControl();
    rollersControl();
    intakeControl();
    pros::delay(20);
  }
}
