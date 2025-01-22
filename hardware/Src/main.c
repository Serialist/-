/**
 * 主程序
 *
 * 读取ps2数据 -> 执行按键操作 -> 底盘电机运动
 *
 *
 * 引脚定义
 *
 * 使用了PORTA PORTB
 *
 * motor PWM引脚定义
 * 1 -> PA6
 * 2 -> PA7
 * 3 -> PB0
 * 4 -> PB1
 *
 * motor逻辑引脚定义
 * 1 -> PA8 PA9
 * 2 -> PA10 PA11
 * 3 -> PA5 PA4
 * 4 -> PA3 PA2
 *
 * ps2数据引脚定义
 * DATA -> PB12
 * CMD -> PB13
 * CS -> PB14
 * CLK -> PB15
 */

#include "main.h"

char *test = "";

void temp(void)
{
    test = "temp";
}

// --------------------------------VAULE-------------------------------- 变量定义
uint8_t i = 1;          // 用于循环计数读取按键函数
ps2_data ps2Data;       // 用于存储PS2手柄数据
void (*cmd[16])(void) = // 用于存储函数指针
    {
        // btn1
        temp,
        temp,
        temp,
        temp,
        temp,
        temp,
        temp,
        temp,
        // btn2
        temp,
        temp,
        temp,
        temp,
        temp,
        temp,
        temp,
        temp};

uint8_t btn[16] = {0}; //

int main(void)
{
    // ----------------INIT---------------- 初始化
    delay_init();
    pwm_init();
    ps2_init();
    motor_init();

    // ----------------WHILE---------------- 开始运行
    while (1)
    {
        // ---------------- 读取PS2数据
        ps2_read(&ps2Data);

                // ---------------- 按键
        // btn1
        for (i = 0; i < 8; i++)
        {
            if (((ps2Data.btn1 >> i) & 1) != 0)
            {
                btn[i] = 1;
            }
            else if (btn[i] == 1)
            {
                btn[i] = 0;
                cmd[i]();
            }
        }
        // btn2
        for (i = 0; i < 8; i++)
        {
            if (((ps2Data.btn2 >> i) & 1) != 0)
            {
                btn[i + 8] = 1;
            }
            else if (btn[i + 8] == 1)
            {
                btn[i + 8] = 0;
                cmd[i + 8]();
            }
        }

        // ---------------- 底盘移动
        if (ps2Data.mode == 0x73) // 绿灯模式
        {
            motor((float)ps2Data.LJoy_UD, (float)ps2Data.LJoy_LR, (float)ps2Data.RJoy_LR);
        }

        // ----------------延时
        delay_ms(10);
    }
}
