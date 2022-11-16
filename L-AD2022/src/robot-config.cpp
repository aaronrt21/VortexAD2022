#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

/*
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
*/

motor LeftFrontMotor = motor(PORT1, ratio18_1, false);
motor LeftBackMotor = motor(PORT2, ratio18_1, false);
motor RightFrontMotor = motor(PORT3, ratio18_1, false);
motor RightBackMotor = motor(PORT4, ratio18_1, false);

motor LauncherLF = motor(PORT5, ratio6_1, false);
motor LauncherLB = motor(PORT6, ratio6_1, false);
motor LauncherRF = motor(PORT7, ratio6_1, true);
motor LauncherRB = motor(PORT8, ratio6_1, true);

motor_group LauncherLeft = motor_group(LauncherLF, LauncherLB);
motor_group LauncherRight = motor_group(LauncherRF, LauncherRB);

drivetrain Launcher = drivetrain(LauncherLeft, LauncherRight);

controller Controller1 = controller(primary);

// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

// define variables used for controlling motors based on controller inputs
bool LFM_NeedsToBeStopped_Controller1 = true;
bool LBM_NeedsToBeStopped_Controller1 = true;
bool RFM_NeedsToBeStopped_Controller1 = true;
bool RBM_NeedsToBeStopped_Controller1 = true;

bool Controller1UpDownButtonsControlMotorsStopped = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1()
{
  while(true)
  {
    if(RemoteControlCodeEnabled)
    {
      
      int LFM_Speed = -Controller1.Axis4.position() + Controller1.Axis3.position() + Controller1.Axis1.position();
      int LBM_Speed = -Controller1.Axis4.position() - Controller1.Axis3.position() + Controller1.Axis1.position();
      int RFM_Speed = Controller1.Axis4.position() + Controller1.Axis3.position() + Controller1.Axis1.position();
      int RBM_Speed = Controller1.Axis4.position() - Controller1.Axis3.position() + Controller1.Axis1.position();
      
      // check if the values are inside of the deadband range
      if (LFM_Speed < 5 && LFM_Speed > -5) {
        // check if the left motor has already been stopped
        if (LFM_NeedsToBeStopped_Controller1) {
          // stop the left drive motor
          LeftFrontMotor.stop(brakeType::hold);
          // tell the code that the left motor has been stopped
          LFM_NeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the left motor nexttime the input is in the deadband range
        LFM_NeedsToBeStopped_Controller1 = true;
      }

      if (LBM_Speed < 5 && LBM_Speed > -5) {
        // check if the left motor has already been stopped
        if (LBM_NeedsToBeStopped_Controller1) {
          // stop the left drive motor
          LeftBackMotor.stop(brakeType::hold);
          // tell the code that the left motor has been stopped
          LBM_NeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the left motor nexttime the input is in the deadband range
        LBM_NeedsToBeStopped_Controller1 = true;
      }

      if (RFM_Speed < 5 && RFM_Speed > -5) {
        // check if the left motor has already been stopped
        if (RFM_NeedsToBeStopped_Controller1) {
          // stop the left drive motor
          RightFrontMotor.stop(brakeType::hold);
          // tell the code that the left motor has been stopped
          RFM_NeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the left motor nexttime the input is in the deadband range
        RFM_NeedsToBeStopped_Controller1 = true;
      }

      if (RBM_Speed < 5 && RBM_Speed > -5) {
        // check if the left motor has already been stopped
        if (RBM_NeedsToBeStopped_Controller1) {
          // stop the left drive motor
          RightBackMotor.stop(brakeType::hold);
          // tell the code that the left motor has been stopped
          RBM_NeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the left motor nexttime the input is in the deadband range
        RBM_NeedsToBeStopped_Controller1 = true;
      }

      // only tell the left drive motor to spin if the values are not in the deadband range
      if (LFM_NeedsToBeStopped_Controller1) {
        LeftFrontMotor.setVelocity(LFM_Speed, percent);
        LeftFrontMotor.spin(forward);
      }

      if (LBM_NeedsToBeStopped_Controller1) {
        LeftBackMotor.setVelocity(LBM_Speed, percent);
        LeftBackMotor.spin(forward);
      }

      if (RFM_NeedsToBeStopped_Controller1) {
        RightFrontMotor.setVelocity(RFM_Speed, percent);
        RightFrontMotor.spin(forward);
      }

      if (RBM_NeedsToBeStopped_Controller1) {
        RightBackMotor.setVelocity(RBM_Speed, percent);
        RightBackMotor.spin(forward);
      }

      // Shoot far
      if (Controller1.ButtonR2.pressing())
      {
        Launcher.setDriveVelocity(100, percent);
        Launcher.driveFor(500, distanceUnits::cm);
      }

      // Shoot close
      else if (Controller1.ButtonL2.pressing())
      {
        Launcher.setDriveVelocity(60, percent);
        Launcher.driveFor(500, distanceUnits::cm);
      }
    }
    wait(20,msec);
    
  }
  return 0;
}
void vexcodeInit(void) {
  // Nothing to initialize
}