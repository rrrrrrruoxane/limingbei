#ifndef PS2_CONTROLLER_H
#define PS2_CONTROLLER_H

#include "movement.h"
extern PS2X ps2x;

// 按键映射（车轮）
void handleWheels(){
  int rx = ps2x.Analog(PSS_RX);  // 读取右摇杆X轴值(0-255)
  if(abs(rx - 128) < 20) rx = 128;  // 设置死区±20，消除中立点附近的小幅波动
  if (ps2x.Button(PSB_CROSS)) { // 假设按键“X”对应前进
    moveForward(200);
  } else if (ps2x.Button(PSB_TRIANGLE)) { // 假设按键“O”对应后退
    turnRight(200);
  } else if (ps2x.Button(PSB_SQUARE)) { // 假设按键“□”对应左转
    turnLeft(200);
  } else if (ps2x.Button(PSB_CIRCLE)) { // 假设按键“△”对应右转
    moveBackward(200);
  } else if(rx>150){
    moveRight();
  } else if(rx<100){
    moveLeft();
  } else stopAll();
}

//升降电机（由左边遥感的Y方向控制）
void handleLiftControl() {
  int ly = ps2x.Analog(PSS_LY);  // 左摇杆Y轴值（0-255）
  const int deadZone = 15;       // 死区范围（避免抖动）
  const float maxMoveMM = 5.0;   // 最大每帧可移动 5mm
  int center = 128;
  int offset = ly - center;
  if (abs(offset) < deadZone) return;
  float mmDelta = map(offset, -127, 127, maxMoveMM, -maxMoveMM);
  if (mmDelta > 0) {
    raiseLift(mmDelta);
  } else {
    lowerLift(-mmDelta);
  }
}

//机械臂
void handleServoControl() {
  delay(20);
  // 肘部舵机（R1键角度增加，R2键角度减小）
  if (ps2x.Button(PSB_R1)) {
    moveElbowTo(car.elbowAngle + 5);
  } else if (ps2x.Button(PSB_R2)) {
    moveElbowTo(car.elbowAngle - 5);
  }
  // 手腕舵机（L1键角度增加，L2键角度减小）
  if (ps2x.Button(PSB_L1)) {
    moveWristTo(car.wristAngle + 5);
  } else if (ps2x.Button(PSB_L2)) {
    moveWristTo(car.wristAngle - 5);
  }
}

//爪子舵机
void handleClawControl() {
  if (ps2x.Button(PSB_L3)) {
    openClaw();
  } else if (ps2x.Button(PSB_R3)) {
    closeClaw();
  }
}

#endif