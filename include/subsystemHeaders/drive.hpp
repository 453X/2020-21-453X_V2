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
void maneuver(int forward, int straft, int turn, double seconds);
void maneuverForward(int forward, int straft, int units);

void forward(int power);
void forward(int power, int units);
void forwardDistance(int power, int mm);
void forwardWithRollers(int power, int units);
void forwardSeconds(int power, double seconds);

void straft(int power);
void straft(int power, int units);

void stop();
void stop(double seconds);

void resetDriveEncoders();
double avgDriveEncoders();

void delaySeconds(double seconds);
