#ifndef CONFIGURARION_H
#define CONFIGURATION_H

#include <PS2X_lib.h>
#include <Servo.h>
#include <AccelStepper.h>

//手柄
#define PS2_DAT_PIN 22
#define PS2_CMD_PIN 23
#define PS2_SEL_PIN 24
#define PS2_CLK_PIN 25
//#define PRESSURES      false
//#define RUMBLE         false

//车轮
#define L1_IN1 6
#define L1_IN2 7
#define L1_ENA 10
#define R1_IN1 8
#define R1_IN2 9
#define R1_ENA 11
#define L2_IN1 12
#define L2_IN2 13
#define L2_ENA 14
#define R2_IN1 16
#define R2_IN2 17
#define R2_ENA 15

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


#endif