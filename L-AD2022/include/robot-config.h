using namespace vex;

extern brain Brain;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */

// VEXcode devices
extern drivetrain Drivetrain;
extern motor LeftDriveA;
extern motor LeftDriveB;
extern motor RightDriveA;
extern motor RightDriveB;
extern controller Controller1;

void vexcodeInit(void);
