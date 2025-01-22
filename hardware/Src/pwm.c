#include "pwm.h"

// --------------------------------FUNCTION--------------------------------函数定义
// ----------------INIT---------------- pwm初始化
void pwm_init(void)
{
    // TIM时钟初始化
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); // 开启TIM3时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // GPIO时钟初始化
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 开启GPIOA时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // 开启GPIOB时钟

    // GPIO配置初始化
    GPIO_InitTypeDef GPIO_InitStructure;              // 结构体变量
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   // 复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 输出速度
    // 设置GPIOA
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // 设置端口PA6，PA7
    GPIO_Init(GPIOA, &GPIO_InitStructure);                 // GPIOA初始化
    // 设置GPIOB
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; // 设置端口PB0,PB1
    GPIO_Init(GPIOB, &GPIO_InitStructure);                 // GPIOB初始化

    // TIM定时器初始化
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure; // 结构体

    TIM_InternalClockConfig(TIM3);                                  // 内部时钟TIM3驱动
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // 1分频
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 计数器模式 向上计数
    TIM_TimeBaseInitStructure.TIM_Period = ARR - 1;                 // ARR 周期 （0~65535）10K频绿下计10000个数 1秒
    TIM_TimeBaseInitStructure.TIM_Prescaler = PSC - 1;              // PSC 预分频器 （0~65535）72M进行7200分频（20KHz）
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;            // 重复计数器（高级计数器才有）
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

    // PWM初始化
    TIM_OCInitTypeDef TIM_OCInitStructure;                        // 结构体
    TIM_OCStructInit(&TIM_OCInitStructure);                       // 结构体赋初始值(防止结构体不完整从而出现奇怪的问题)
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;             // 设置输出比较模式 PWM模式1
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     // 设置输出比较的极性 高极性
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // 设置输出使能
    TIM_OCInitStructure.TIM_Pulse = 0;                            // 初始化设置 CCR 寄存器值
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);                      // TIM3通道1初始化完成
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);                      // TIM3通道2初始化完成
    TIM_OC3Init(TIM3, &TIM_OCInitStructure);                      // TIM3通道3初始化完成
    TIM_OC4Init(TIM3, &TIM_OCInitStructure);                      // TIM3通道4初始化完成

    // 定时器赋能
    TIM_Cmd(TIM3, ENABLE); // 定时器开始工作
}

// ----------------CONTROL---------------- 底盘的PWM设置
// 占空比(0, 1)
// 电机*4
void pwm_set1(float duty)
{
    TIM_SetCompare1(TIM3, (uint16_t)(duty * ARR - 1));
}
void pwm_set2(float duty)
{
    TIM_SetCompare2(TIM3, (uint16_t)(duty * ARR - 1));
}
void pwm_set3(float duty)
{
    TIM_SetCompare3(TIM3, (uint16_t)(duty * ARR - 1));
}
void pwm_set4(float duty)
{
    TIM_SetCompare4(TIM3, (uint16_t)(duty * ARR - 1));
}
