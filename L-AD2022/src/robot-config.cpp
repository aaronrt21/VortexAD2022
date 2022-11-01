#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */

motor LeftFrontMotor = motor(PORT1, ratio18_1, false);
motor LeftBackMotor = motor(PORT2, ratio18_1, false);
motor RightFrontMotor = motor(PORT3, ratio18_1, false);
motor RightBackMotor = motor(PORT4, ratio18_1, false);

motor_group LeftDriveSmart = motor_group(LeftFrontMotor, LeftBackMotor);
motor_group RightDriveSmart = motor_group(RightFrontMotor, RightBackMotor);

controller Controller1 = controller(primary);

// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

// define variables used for controlling motors based on controller inputs
bool DrivetrainLFNeedsToBeStopped_Controller1 = true;
bool DrivetrainLBNeedsToBeStopped_Controller1 = true;
bool DrivetrainRFNeedsToBeStopped_Controller1 = true;
bool DrivetrainRBNeedsToBeStopped_Controller1 = true;

bool Controller1UpDownButtonsControlMotorsStopped = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1()
{
  while(true)
  {
    if(RemoteControlCodeEnabled)
    {
    /*
    int LFM_Speed = Controller1.Axis2.position() + Controller1.Axis1.position() + Controller1.Axis4.position();
    int LBM_Speed = Controller1.Axis2.position() - Controller1.Axis1.position() + Controller1.Axis4.position();
    int RFM_Speed = (-Controller1.Axis2.position()) + Controller1.Axis1.position() + Controller1.Axis4.position();
    int RBM_Speed = (-Controller1.Axis2.position()) - Controller1.Axis1.position() + Controller1.Axis4.position();
    
    LeftFrontMotor.setVelocity(LFM_Speed, percent);
    LeftBackMotor.setVelocity(LBM_Speed, percent);
    RightFrontMotor.setVelocity(RFM_Speed, percent);
    RightBackMotor.setVelocity(RBM_Speed, percent);
    */
    LeftFrontMotor.setVelocity(-Controller1.Axis1.position() + Controller1.Axis2.position() + Controller1.Axis4.position(), percent);
    LeftBackMotor.setVelocity(-Controller1.Axis1.position() - Controller1.Axis2.position() + Controller1.Axis4.position(), percent);
    RightFrontMotor.setVelocity((Controller1.Axis1.position()) + Controller1.Axis2.position() + Controller1.Axis4.position(), percent);
    RightBackMotor.setVelocity((Controller1.Axis1.position()) - Controller1.Axis2.position() + Controller1.Axis4.position(), percent);
    LeftFrontMotor.spin(fwd);
    LeftBackMotor.spin(fwd);
    RightFrontMotor.spin(fwd);
    RightBackMotor.spin(fwd);
    }
    wait(20,msec);
    
  }
  return 0;
}
void vexcodeInit(void) {
  // Nothing to initialize
}