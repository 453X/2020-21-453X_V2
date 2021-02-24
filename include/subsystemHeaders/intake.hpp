#include "main.h"

void intakeControl();
void intakeSetHold();
void intake();
void outtake();
void intakeStop();
void intakePositioning(int units, double seconds, double rTotalTime , int loop, double rSeconds, int power) ;
void goalPositioning(int forwardUnits, double seconds, int balls, double rollSeconds);
void resetIntakeEncoders();
double avgIntakeEncoder();
