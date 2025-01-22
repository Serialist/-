#include "motor.h"

float v1, v2, v3, v4; // 四个电机速度
float vx, vy, vr;

// 初始化电机
void motor_init()
{
    // 初始化L298N逻辑引脚
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_5 | GPIO_Pin_4 | GPIO_Pin_3 | GPIO_Pin_2;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

// 摇杆数据映射函数 [0, 255] -> [255, 0] -> [-1, 1]
static float motor_map(float value)
{
    value = 255 - value;
    if (value >= 128)
    {
        return (value - 128) / 127;
    }
    else
    {
        return (value / 127) - 1;
    }
}

/**
 * @brief 控制底盘电机
 *
 * @param translation_x X轴平移速度
 * @param translation_y Y轴平移速度
 * @param rotation 旋转速度
 *
 * @note 参数实际是遥杆的数据
 */
void motor(float translation_x, float translation_y, float rotation)
{
    // 摇杆数据映射为 [-1 , 1]
    vx = motor_map(translation_x);
    vy = motor_map(translation_y);
    vr = motor_map(rotation) * 0.4;

    // 计算速度
    v1 = (vx + vy) / 2 - vr;
    v2 = (vx - vy) / 2 - vr;
    v3 = (vx - vy) / 2 + vr;
    v4 = (vx + vy) / 2 + vr;

    // 设置电机速度
    pwm_set1(fabs(v1));
    pwm_set2(fabs(v2));
    pwm_set3(fabs(v3));
    pwm_set4(fabs(v4));

    // 设置电机方向
    // motor1
    if (v1 > 0)
    {
        PAout(8) = 1;
        PAout(9) = 0;
    }
    else
    {
        PAout(8) = 0;
        PAout(9) = 1;
    }
    // motor2
    if (v2 > 0)
    {
        PAout(10) = 1;
        PAout(11) = 0;
    }
    else
    {
        PAout(10) = 0;
        PAout(11) = 1;
    }
    // motor3
    if (v3 > 0)
    {
        PAout(5) = 1;
        PAout(4) = 0;
    }
    else
    {
        PAout(5) = 0;
        PAout(4) = 1;
    }
    // motor4
    if (v4 > 0)
    {
        PAout(3) = 1;
        PAout(2) = 0;
    }
    else
    {
        PAout(3) = 0;
        PAout(2) = 1;
    }
}
