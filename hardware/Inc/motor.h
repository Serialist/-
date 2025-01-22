#ifndef __MOTOR_H
#define __MOTOR_H

#include "main.h"

// 如果不使用PID控制底盘电机则定义MOTOR_NO_PID

// 初始化电机
void motor_init(void);

// 设置电机速度
void motor(float translation_x, float translation_y, float rotation);

#endif
