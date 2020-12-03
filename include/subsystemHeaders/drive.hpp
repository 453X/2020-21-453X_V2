#include "main.h"

void driverControl();
void calibrate();
void driveSetHold();
void driveSetBrake();
void driveSetCoast();
void rotateDegrees(double deg);
void turn(int power);
void turn(int power, int units);
void maneuver(int forward, int straft, int turn);
void maneuver(int forward, int straft, int turn, int units);
void maneuverForward(int forward, int straft, int units);
void forward(int power);
void forward(int power, int units);
void straft(int power);
void straft(int power, int units);
void stop();
void stop(double seconds);
void resetDriveEncoders();
void delaySeconds(double seconds);
double avgDriveEncoders();