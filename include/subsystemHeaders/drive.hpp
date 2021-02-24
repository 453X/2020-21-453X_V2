#include "main.h"

void driverControl();

void calibrate();
void driveSetHold();
void driveSetBrake();
void driveSetCoast();

void rotateDegrees(double deg);
void rotateDegreesPD(double deg);
void turnPID(int setPoint);
void forwardPD(int units);
void straftPD(int units);
void maneuverPD(int forward, int straft, int turn, int units);
void distancePD(int setPoint);

void forwardAcceleration(double constant);
void straftAcceleration(double constant);
void maneuverAcceleration(int forward, int straft, int turn, double constant);

void forwardAccel(int constant, int pd);
void straftAccel(int constant, int pd);
void maneuverAccel(int forward, int straft, int turn, int constant, int pd);

void turn(double power);
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
void straftSeconds(int power, double seconds);

void stop();
void stop(double seconds);

void resetDriveEncoders();
double avgDriveEncoders();

void delaySeconds(double seconds);
