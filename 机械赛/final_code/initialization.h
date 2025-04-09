#ifndef INITIALIZATION_H
#define INITIALIZATION_H

#include "configuration.h"

extern PS2X ps2x;
extern AccelStepper stepper;
extern Servo servoElbow;
extern Servo servoWrist;
extern Servo servoClaw;

struct Car{
  int currentHeight;
  int elbowAngle;
  int wristAngle;
  int clawAngle;
  bool emergencyStop;
};
extern Car car;

void testMotorDirection() {
  Serial.println("Testing FL motor...");
  MOTOR_FWD(FL_IN1, FL_IN2); delay(1000); MOTOR_STOP(FL_IN1, FL_IN2);

  Serial.println("Testing FR motor...");
  MOTOR_FWD(FR_IN1, FR_IN2); delay(1000); MOTOR_STOP(FR_IN1, FR_IN2);

  Serial.println("Testing BL motor...");
  MOTOR_FWD(BL_IN1, BL_IN2); delay(1000); MOTOR_STOP(BL_IN1, BL_IN2);

  Serial.println("Testing BR motor...");
  MOTOR_FWD(BR_IN1, BR_IN2); delay(1000); MOTOR_STOP(BR_IN1, BR_IN2);
}

void initSerial(){
  Serial.begin(9600);
  Serial.println("串口已开启");
}



void initPS2X(){
  int error = 0;       // PS2控制器连接错误标志
  byte type = 0;       // 控制器类型
  byte vibrate = 0;    // 震动强度
  delay(300);  // 短延时确保稳定
  error = ps2x.config_gamepad(PS2_CLK_PIN, PS2_CMD_PIN, PS2_SEL_PIN, PS2_DAT_PIN, PRESSURES, RUMBLE);
  if(error == 0) {
    Serial.println("PS2 Controller Found");
  } else {
    Serial.println("PS2 Controller Error");
    Serial.println(error);
    while (1);  // 如果初始化失败，停止运行
  }
  
  // 电机转向测试（上电后运行一次）
  testMotorDirection();
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
  servoClaw.attach(SERVO_CLAW_PIN);
  Serial.println("舵机初始化完成");
}


//车轮
void initMotors(){
  pinMode(BL_IN1, OUTPUT); pinMode(BL_IN2, OUTPUT);
  pinMode(FL_IN1, OUTPUT); pinMode(FL_IN2, OUTPUT);
  pinMode(FR_IN1, OUTPUT); pinMode(FR_IN2, OUTPUT);
  pinMode(BR_IN1, OUTPUT); pinMode(BR_IN2, OUTPUT);

  Serial.println("车轮初始化成功");
}

void initCar(){
  car.currentHeight=0;
  car.elbowAngle=constrain(90,ELBOW_MIN_ANGLE,ELBOW_MAX_ANGLE);
  car.wristAngle=constrain(90,WRIST_MIN_ANGLE,WRIST_MAX_ANGLE);
  car.clawAngle= constrain(90, CLAW_MIN_ANGLE, CLAW_MAX_ANGLE);
  car.emergencyStop=false;
  // 移动舵机到初始位置
  servoElbow.write(car.elbowAngle);
  servoWrist.write(car.wristAngle);
  servoClaw.write(car.clawAngle);

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