#ifndef CONFIGURARION_H
#define CONFIGURATION_H

#include <PS2X_lib.h>
#include <Servo.h>
#include <AccelStepper.h>

//手柄
#define PS2_DAT_PIN 4
#define PS2_CMD_PIN 5
#define PS2_SEL_PIN 6
#define PS2_CLK_PIN 7
#define PRESSURES      false
#define RUMBLE         false
//车轮
#define BL_IN1 33  // 后左电机控制引脚1
#define BL_IN2 32  // 后左电机控制引脚2
#define FL_IN1 35  // 前左电机控制引脚1
#define FL_IN2 34  // 前左电机控制引脚2
#define FR_IN1 37  // 前右电机控制引脚1
#define FR_IN2 36  // 前右电机控制引脚2
#define BR_IN1 39  // 后右电机控制引脚1
#define BR_IN2 38  // 后右电机控制引脚2

//升降
#define STEPPER_DIR_PIN 26//升降方向
#define STEPPER_STEP_PIN 27//升降速度
#define STEPPER_ENABLE_PIN 28//是否启用
#define LIFT_STEP_MM 8.0//完整走一圈
#define STEPS_PER_REV 200//转一圈要走200步
#define DEFAULT_STEPPER_SPEED 400//启动后平稳速度
#define DEFAULT_STEPPER_ACCEL 200//启动时的加速度

//机械臂肘部和腕部
#define SERVO_ELBOW_PIN 9
#define SERVO_WRIST_PIN 10
#define ELBOW_MIN_ANGLE 30
#define ELBOW_MAX_ANGLE 150
#define WRIST_MIN_ANGLE 20
#define WRIST_MAX_ANGLE 160

//机械臂夹爪
#define SERVO_CLAW_PIN 22       // 具体引脚  
#define CLAW_MIN_ANGLE 2.9  // 物理设计，最小无法完全闭合
#define CLAW_MAX_ANGLE 90

// 电机控制宏定义
#define MOTOR_STOP(mA1, mA2) { digitalWrite(mA1, LOW); digitalWrite(mA2, LOW); }  // 停止
#define MOTOR_FWD(mA1, mA2)  { digitalWrite(mA1, HIGH); digitalWrite(mA2, LOW); } // 正转
#define MOTOR_REV(mA1, mA2)  { digitalWrite(mA1, LOW); digitalWrite(mA2, HIGH); } // 反转

#endif