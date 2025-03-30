#ifndef PS2_CONTROLLER_H
#define PS2_CONTROLLER_H

#include "movement.h"
extern PS2X ps2x;

// 获取左摇杆的 X/Y 值（0~255）
int getLeftStickX() {
  return ps2x.Analog(PSS_LX);
}

int getLeftStickY() {
  return ps2x.Analog(PSS_LY);
}

// 获取右摇杆的 X/Y 值（0~255）
int getRightStickX() {
  return ps2x.Analog(PSS_RX);
}

int getRightStickY() {
  return ps2x.Analog(PSS_RY);
}
// 按键映射（车轮）（需改键）
void handleWheels(){
  if (ps2x.ButtonPressed(PSB_CROSS)) { // 假设按键“X”对应前进
    moveForward(200);
  } else if (ps2x.ButtonPressed(PSB_CIRCLE)) { // 假设按键“O”对应后退
    moveBackward(200);
  } else if (ps2x.ButtonPressed(PSB_SQUARE)) { // 假设按键“□”对应左转
    turnLeft(200);
  } else if (ps2x.ButtonPressed(PSB_TRIANGLE)) { // 假设按键“△”对应右转
    turnRight(200);
  } else {
    stopMotors(); // 其他按键停止运动
  }
}


#endif