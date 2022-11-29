/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Vortex team                                               */
/*    Created:      Mon Oct 31 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
//  ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;

// A global instance of competition
competition Competition;

void pre_auton(void){
  // Initializing Robot Configuration.
  vexcodeInit();
}


/* ----------------- AUTONOMOUS PART ----------------- */
void get_roller(bool wait){
  // Turn left
  Drivetrain.turn(left);
  // Move forward 1 cm
  Drivetrain.driveFor(directionType::fwd, 1, distanceUnits::cm);
  // Make Loader spin 90°
  Loader.spinFor(directionType::fwd, 90, rotationUnits::deg);
}

void disk_collector(bool wait){
  // Start elevator
  Elevator.spin(directionType::fwd);
}

void auton(void) {
  // Set drivetrain to it's 80% of velocity
  Drivetrain.setDriveVelocity(80, pct);
}

/* ------------------ CONTROL PART ------------------ */
void usercontrol(void){
  rc_auto_loop_function_Controller1();
}

int main() {
  pre_auton();
  //auton();
  usercontrol();
}
