#ifndef __PWM_H
#define __PWM_H

#include "main.h"

// --------------------------------DEFINE--------------------------------参数定义
#define ARR 20000 // ARR 周期 （0~65535）10K频绿下计10000个数 1秒
#define PSC 72    // PSC 预分频器 （0~65535）72M进行7200分频（20KHz）

// --------------------------------FUNCTION--------------------------------函数定义
// ----------------INIT---------------- PWM初始化函数
void pwm_init(void);

// ----------------CONTROL---------------- 底盘的PWM设置
void pwm_set1(float duty);
void pwm_set2(float duty);
void pwm_set3(float duty);
void pwm_set4(float duty);

// ----------------CONTROL---------------- 发射器的pwm设置

void pwm_set5(float angle);
void pwm_set6(float angle);
void pwm_set7(float duty);

#endif
