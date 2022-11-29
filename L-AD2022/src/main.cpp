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

competition Competition;

void pre_auton(void){
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
}

/* ----------------- AUTONOMOUS PART ----------------- */
void get_roller(bool wait){
  // Move forward 10 cm
  Drivetrain.driveFor(directionType::fwd, 10, distanceUnits::cm);
  // Turn right
  Drivetrain.turn(right);
  // Move forward 10 cm
  Drivetrain.driveFor(directionType::fwd, 10, distanceUnits::cm);
  // Turn right
  Drivetrain.turn(right);
  // Move forward 5 cm
  Drivetrain.driveFor(directionType::fwd, 5, distanceUnits::cm);
  // Make Loader spin 90°
  Loader.spinFor(directionType::fwd, 90, rotationUnits::deg);
}

void disk_collector(bool wait){
  // Start elevator
  Elevator.spin(directionType::fwd);
}

void throw_disks(bool wait){
  // Move forward 10 cm
  Drivetrain.driveFor(directionType::fwd, 10, distanceUnits::cm);
  // Throw 3 disks
  Launcher.driveFor(directionType::fwd, 50, distanceUnits::cm);
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
