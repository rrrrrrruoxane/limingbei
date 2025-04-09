#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <Arduino.h>
#include "configuration.h"
extern Car car;
extern AccelStepper stepper;
extern Servo servoElbow;
extern Servo servoWrist;
extern Servo servoClaw;

//========== 车轮 ==========
void setMotorSpeed(int in1, int in2, int ena, int speed) {
  if (speed > 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else if (speed < 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    speed = -speed;
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
  analogWrite(ena, constrain(speed, 0, 255));
}
// 前进函数
void moveForward(int speed) {
  MOTOR_FWD(FL_IN1, FL_IN2); MOTOR_FWD(FR_IN1, FR_IN2);
  MOTOR_FWD(BL_IN1, BL_IN2); MOTOR_FWD(BR_IN1, BR_IN2);
}

// 后退函数
void moveBackward(int speed) {
  MOTOR_REV(FL_IN1, FL_IN2); MOTOR_REV(FR_IN1, FR_IN2);
  MOTOR_REV(BL_IN1, BL_IN2); MOTOR_REV(BR_IN1, BR_IN2);
}

//左转函数
void turnLeft(int speed) {
  MOTOR_REV(FL_IN1, FL_IN2); MOTOR_FWD(FR_IN1, FR_IN2);
  MOTOR_REV(BL_IN1, BL_IN2); MOTOR_FWD(BR_IN1, BR_IN2);
}

//右转函数
void turnRight(int speed) {
  MOTOR_FWD(FL_IN1, FL_IN2); MOTOR_REV(FR_IN1, FR_IN2);
  MOTOR_FWD(BL_IN1, BL_IN2); MOTOR_REV(BR_IN1, BR_IN2);
}

//左移函数
void moveLeft() {
  MOTOR_REV(FL_IN1, FL_IN2); MOTOR_FWD(FR_IN1, FR_IN2);
  MOTOR_FWD(BL_IN1, BL_IN2); MOTOR_REV(BR_IN1, BR_IN2);
}

//右移函数
void moveRight() {
  MOTOR_FWD(FL_IN1, FL_IN2); MOTOR_REV(FR_IN1, FR_IN2);
  MOTOR_REV(BL_IN1, BL_IN2); MOTOR_FWD(BR_IN1, BR_IN2);
}

//停下函数
void stopAll() {
  MOTOR_STOP(FL_IN1, FL_IN2); MOTOR_STOP(FR_IN1, FR_IN2);
  MOTOR_STOP(BL_IN1, BL_IN2); MOTOR_STOP(BR_IN1, BR_IN2);
}

//==========  升降步进电机  ==========
void raiseLift(float mm) {
  int steps = (mm / LIFT_STEP_MM) * STEPS_PER_REV;
  stepper.moveTo(stepper.currentPosition() + steps);
  car.currentHeight += mm;
}

void lowerLift(float mm) {
  int steps = (mm / LIFT_STEP_MM) * STEPS_PER_REV;
  stepper.moveTo(stepper.currentPosition() - steps);
  car.currentHeight -= mm;
}

// ========== 舵机控制 ==========

void moveElbowTo(int angle) {
  angle = constrain(angle, ELBOW_MIN_ANGLE, ELBOW_MAX_ANGLE);
  servoElbow.write(angle);
  car.elbowAngle = angle;
}

void moveWristTo(int angle) {
  angle = constrain(angle, WRIST_MIN_ANGLE, WRIST_MAX_ANGLE);
  servoWrist.write(angle);
  car.wristAngle = angle;
}

void openClaw() {
  servoClaw.write(CLAW_MAX_ANGLE);
  car.clawAngle = CLAW_MAX_ANGLE;
}

void closeClaw() {
  servoClaw.write(CLAW_MIN_ANGLE);
  car.clawAngle = CLAW_MIN_ANGLE;
}
#endif