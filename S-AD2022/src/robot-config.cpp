#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

// Drivetrain
motor LeftFrontMotor = motor(PORT1, ratio18_1, false);  
motor LeftBackMotor = motor(PORT2, ratio18_1, false);   
motor RightFrontMotor = motor(PORT3, ratio18_1, true); 
motor RightBackMotor = motor(PORT4, ratio18_1, false);
// Motor groups for the drivetrain
motor_group LeftMotors = motor_group(LeftFrontMotor, LeftBackMotor);
motor_group RightMotors = motor_group(RightFrontMotor, RightBackMotor);
//  Drivetrain
drivetrain Drivetrain = drivetrain(LeftMotors, RightMotors, 319.19, 295, 40, mm, 1);

// Thrower
motor LauncherLF = motor(PORT5, ratio6_1, true);
motor LauncherRF = motor(PORT6, ratio6_1, false);
// Thrower group
motor_group Launcher = motor_group(LauncherLF, LauncherRF);

// Trigger & Roller
motor Loader = motor(PORT7, ratio6_1, false);

// Elevator
motor Elevator1 = motor(PORT8, ratio6_1, true);
motor Elevator2 = motor(PORT9, ratio6_1, true);
motor_group Elevator = motor_group(Elevator1, Elevator2);

// Controller
controller Controller1 = controller(primary);

// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

// define variables used for controlling motors based on controller inputs
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;

int offset = 5;

bool Controller1UpDownButtonsControlMotorsStopped = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1(){
  while(true){
    if(RemoteControlCodeEnabled){
      // calculate the drivetrain motor velocities from the controller joystick axies
      // left = Axis3 + Axis1
      // right = Axis3 - Axis1
      int drivetrainLeftSideSpeed =  Controller1.Axis3.position() + Controller1.Axis1.position();
      int drivetrainRightSideSpeed = Controller1.Axis3.position() - Controller1.Axis1.position();

      // check if the value is inside of the deadband range
      if (drivetrainLeftSideSpeed < offset && drivetrainLeftSideSpeed > -offset){
        // check if the left motor has already been stopped
        if (DrivetrainLNeedsToBeStopped_Controller1){
          LeftMotors.stop();  // stop the left drive motor
          DrivetrainLNeedsToBeStopped_Controller1 = false;  // tell the code that the left motor has been stopped
        }
      } else{
        // reset the toggle so that the deadband code knows to stop the left motor nexttime the input is in the deadband range
        DrivetrainLNeedsToBeStopped_Controller1 = true;
      }
      // check if the value is inside of the deadband range
      if (drivetrainRightSideSpeed < offset && drivetrainRightSideSpeed > -offset){
        // check if the right motor has already been stopped
        if (DrivetrainRNeedsToBeStopped_Controller1){
          RightMotors.stop();  // stop the right drive motor
          DrivetrainRNeedsToBeStopped_Controller1 = false;  // tell the code that the right motor has been stopped
        }
      } else{
        // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
        DrivetrainRNeedsToBeStopped_Controller1 = true;
      }

      // only tell the left drive motor to spin if the values are not in the deadband range
      if (DrivetrainLNeedsToBeStopped_Controller1){
        LeftMotors.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftMotors.spin(forward);
      }

      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainRNeedsToBeStopped_Controller1){
        RightMotors.setVelocity(drivetrainRightSideSpeed, percent);
        RightMotors.spin(forward);
      }

      // Trigger and roller long shot
      if (Controller1.ButtonR2.pressing()){        
        // Spin launcher and delay 1 sec
        Launcher.spin(forward, 100, velocityUnits::pct);
        wait(800, msec);
        // Start Loader
        Loader.spin(forward, 100, velocityUnits::pct);
      } else{
        Launcher.stop();
        Loader.stop();
      }

      // Active elevator 
      if (Controller1.ButtonA.pressing()){
        Elevator.spin(forward, 100, percent);
      } else{ Elevator.stop(); }
      
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}


void vexcodeInit(void) {
  // Nothing to initialize
}