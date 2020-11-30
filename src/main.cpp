#include "main.h"
#include "autoSelect/selection.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initialize() {
  selector::init();
  driveSetCoast();
  calibrate();
  resetDriveEncoders();
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
void competition_initialize() {}

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
  calibrate();
  if (selector::auton == 1) {
    pros::lcd::initialize();
    forward(80, 1800);
    stop(1);
    rotateDegrees(225);
    stop(1);
    intake();
    forward(80, 2050);
    forward(60);
    delaySeconds(0.7);
    stop(0.7);
    intakeStop();
    roll();
    delaySeconds(1);
    rollersStop();
    stop(0);
    /*
    stop(0.5);
    //turn(50, -1240);
    rotateDegrees(45);
    stop(0.5);
    intake();
    forward(100, 1950, 45); // problem
    forward(50);
    pros::delay(200);
    stop(0.5);
    // forward(50, -50);
    intakeStop();
    roll();
    pros::delay(3000);
    rollersStop();
    stop(0);
    forward(50, -1800);
    stop(0.5);
    rotateDegrees(315);*/
  } // selector::auton == 1 : Red Front
  if (selector::auton == 2) {

  } // selector::auton == 2 : Red Back
  if (selector::auton == 3) {

  } // selector::auton == 3 : Do Nothing
  if (selector::auton == 4) {

  } // selector::auton == 4 : Red Custom
  if (selector::auton == -1) {

  } // selector::auton == -1 : Blue Front
  if (selector::auton == -2) {

  } // selector::auton == -2 : Blue Back
  if (selector::auton == -3) {

  } // selector::auton == -3 : Do Nothing
  if (selector::auton == -4) {

  } // selector::auton == -4 : Blue Custom
  if (selector::auton == 0) {

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
    // trackingBalls();
    //  pros::lcd::print(0, "Get rotation- ");
    // printf("IMU get rotation: %f degrees\n", inertial.get_rotation());
    pros::delay(20);
  }
}
