#ifndef __MAIN_H
#define __MAIN_H

#define MOTOR_NO_PID // 不使用PID控制底盘电机

// 标准库
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>

// stm32库
#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_tim.h>
#include <stm32f10x_rcc.h>
#include <misc.h>

// 借来的代码
#include "delay.h"
#include "sys.h"

// 自己的代码
#include <pwm.h>
#include <ps2.h>
#include <motor.h>

#endif

/*
TIM23 -> PWM
L123 -> L298N
             TIM3                 TIM2       ------------L3
B11 B10 (B1 B0 A7 A6) A5 A4 (A3 A2 A1 A0)   (C15 C14 C13|
       PS2              L1               L2  -----|     |     TIM4     
(B12 B13 B14 B15) (A8 A9 A10 A11) (A12 A15 B3 B4) |  B5 ) (B6 B7 B8 B9) 
*/
