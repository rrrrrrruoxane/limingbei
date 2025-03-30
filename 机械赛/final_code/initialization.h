#ifndef INITIALIZATION_H
#define INITIALIZATION_H

#include "configuration.h"

extern PS2X ps2x;
extern AccelStepper stepper;
extern Servo servoElbow;
extern Servo servoWrist;
//extern Servo servoClaw;

struct Car{
  int currentHeight;
  int elbowAngle;
  int wristAngle;
  // int clawAngle;
  bool emergencyStop;
};
extern Car car;

void initSerial(){
  Serial.begin(9600);
  Serial.println("串口已开启");
}

void initPS2X(){
 int error=ps2x.config_gamepad(PS2_CLK_PIN,PS2_CMD_PIN,PS2_SEL_PIN,PS2_DAT_PIN,true,true);
  if(error!=0){
    Serial.print("PS2 手柄初始化错误: ");
    Serial.println(error);
  }else{
    Serial.println("PS2 手柄初始化成功");
  }
}

void initStepper(){
  stepper.setMaxSpeed(DEFAULT_STEPPER_SPEED);
  stepper.setAcceleration(DEFAULT_STEPPER_ACCEL);
  pinMode(STEPPER_ENABLE_PIN,OUTPUT);
  digitalWrite(STEPPER_ENABLE_PIN,LOW);
  Serial.println("步进电机初始化完成");
}

void initServos(){
  servoElbow.attach(SERVO_ELBOW_PIN);
  servoWrist.attach(SERVO_WRIST_PIN);
  // servoClaw.attach(SERVO_CLAW_PIN);
  Serial.println("舵机初始化完成");
}

void initMotors(){
  pinMode(L1_IN1,OUTPUT);
  pinMode(L1_IN2,OUTPUT);
  pinMode(L1_ENA,OUTPUT);

  pinMode(R1_IN1,OUTPUT);
  pinMode(R1_IN2,OUTPUT);
  pinMode(R1_ENA,OUTPUT);

  pinMode(L2_IN1,OUTPUT);
  pinMode(L2_IN2,OUTPUT);
  pinMode(L2_ENA,OUTPUT);

  pinMode(R2_IN1,OUTPUT);
  pinMode(R2_IN2,OUTPUT);
  pinMode(R2_ENA,OUTPUT);

  Serial.println("车轮电机引脚初始化完成");
}

void initCar(){
  car.currentHeight=0;
  car.elbowAngle=constrain(90,ELBOW_MIN_ANGLE,ELBOW_MAX_ANGLE);
  car.wristAngle=constrain(90,WRIST_MIN_ANGLE,WRIST_MAX_ANGLE);
  // car.clawAngle=CLAW_MIN_ANGLE;
  car.emergencyStop=false;
  // 移动舵机到初始位置
  servoElbow.write(car.elbowAngle);
  servoWrist.write(car.wristAngle);
  // servoClaw.write(car.clawAngle);

  Serial.println("机器人状态初始化完成");
}

void initAll() {
  initSerial();
  initPS2X();
  initStepper();
  initServos();
  initMotors();
  initCar();
  Serial.println("系统初始化完成");
}

#endif