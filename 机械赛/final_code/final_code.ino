#include "initialization.h"
#include "ps2_controller.h"

PS2X ps2x;
AccelStepper stepper(1,STEPPER_STEP_PIN,STEPPER_DIR_PIN);
Servo servoElbow,servoWrist,servoClaw;
Car car;

void setup() {
  initAll();
}

void loop() {
  ps2x.read_gamepad(); 
  handleWheels();
  handleLiftControl();
  handleServoControl();
  handleClawControl(); 
  stepper.run();  
}
