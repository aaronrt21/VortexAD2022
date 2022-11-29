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
// Functions for drivetrain
void move_fordward(int dist){
  Drivetrain.driveFor(directionType::fwd, dist, distanceUnits::cm);
}
void move_backward(int dist){
  Drivetrain.driveFor(directionType::rev, dist, distanceUnits::cm);
}
void turn_left(bool wait){
  Drivetrain.turn(left);
}
void turn_right(bool wait){
  Drivetrain.turn(right);
}

// Functions for roller & trigger
void active_roller(int ang){
  Loader.spinFor(directionType::fwd, ang, rotationUnits::deg);
}
void active_trigger(bool wait){
  Loader.spin(directionType::fwd, 100, velocityUnits::pct);
}

// Functions for Elevator
void active_elevator(bool wait){
  Elevator.spin(directionType::fwd);
}

// Functions for Launcher
void active_launcher(bool wait){
  Launcher.spin(directionType::fwd);
}

// Stop everything
void stop_all(bool wait){
  Drivetrain.stop();
  Launcher.stop();
  Loader.stop();
  Elevator.stop();
}

void auton(void) {
  // Set drivetrain to it's 80% of velocity
  Drivetrain.setDriveVelocity(80, pct);
  // vexDelay(uint32_t timems)
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
