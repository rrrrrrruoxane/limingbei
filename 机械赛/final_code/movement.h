#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <Arduino.h>
#include "configuration.h"
extern Car car;
extern AccelStepper stepper;
extern Servo servoElbow;
extern Servo servoWrist;
// extern Servo servoClaw;

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
  setMotorSpeed(L1_IN1, L1_IN2, L1_ENA, speed);
  setMotorSpeed(R1_IN1, R1_IN2, R1_ENA, speed);
  setMotorSpeed(L2_IN1, L2_IN2, L2_ENA, speed);
  setMotorSpeed(R2_IN1, R2_IN2, R2_ENA, speed);
}

// 后退函数
void moveBackward(int speed) {
  setMotorSpeed(L1_IN1, L1_IN2, L1_ENA, -speed);
  setMotorSpeed(R1_IN1, R1_IN2, R1_ENA, -speed);
  setMotorSpeed(L2_IN1, L2_IN2, L2_ENA, -speed);
  setMotorSpeed(R2_IN1, R2_IN2, R2_ENA, -speed);
}

//左转函数
void turnLeft(int speed) {
  setMotorSpeed(L1_IN1, L1_IN2, L1_ENA, -speed);
  setMotorSpeed(R1_IN1, R1_IN2, R1_ENA, speed);
  setMotorSpeed(L2_IN1, L2_IN2, L2_ENA, -speed);
  setMotorSpeed(R2_IN1, R2_IN2, R2_ENA, speed);
}

//右转函数
void turnRight(int speed) {
  setMotorSpeed(L1_IN1, L1_IN2, L1_ENA, speed);
  setMotorSpeed(R1_IN1, R1_IN2, R1_ENA, -speed);
  setMotorSpeed(L2_IN1, L2_IN2, L2_ENA, speed);
  setMotorSpeed(R2_IN1, R2_IN2, R2_ENA, -speed);
}

//停下函数
void stopMotors() {
  setMotorSpeed(L1_IN1, L1_IN2, L1_ENA, 0);
  setMotorSpeed(R1_IN1, R1_IN2, R1_ENA, 0);
  setMotorSpeed(L2_IN1, L2_IN2, L2_ENA, 0);
  setMotorSpeed(R2_IN1, R2_IN2, R2_ENA, 0);
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

#endif