using namespace vex;

extern brain Brain;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
**/

// VEXcode devices
// Drivetrain
extern motor LeftFrontMotor;
extern motor LeftBackMotor;
extern motor RightFrontMotor;
extern motor RightBackMotor;
extern drivetrain Drivetrain;

// Thrower
extern motor LauncherLF;
extern motor LauncherRF;
extern motor_group Launcher;

// Trigger
extern motor Loader;

// Elevator
extern motor Elevator1; 
extern motor Elevator2; 
extern motor_group Elevator;

// Kicker
extern motor Kick;

extern controller Controller1;
extern int rc_auto_loop_function_Controller1();

void vexcodeInit(void);
