/**
 *   PS2数据定义
 *   BYTE   DATA   解释
 *   01     idle
 *   02     0x73   手柄工作模式
 *   03     0x5A   Bit0  Bit1  Bit2  Bit3  Bit4  Bit5  Bit6  Bit7
 *   04     data   SLCT  JOYR  JOYL  STRT   UP   RGIHT  DOWN   L
 *   05     data   L2     R2     L1    R1   Y     B     A      X
 *   06     data   右边摇杆  0x00 = 左    0xff = 右
 *   07     data   右边摇杆  0x00 = 上    0xff = 下
 *   08     data   左边摇杆  0x00 = 左    0xff = 右
 *   09     data   左边摇杆  0x00 = 上    0xff = 下
 *
 * PB12 -> DATA
 * PB13 -> CMD
 * PB14 -> CS
 * PB15 -> CLK
 */

#include "ps2.h"

// --------------------------------DEFINE-------------------------------- 参数定义
// PS2手柄的输入输出口
#define DI() PBin(12) // 数据输入引脚

#define CMD_H() PBout(13) = 1 // 命令位高
#define CMD_L() PBout(13) = 0 // 命令位低

#define CS_H() PBout(14) = 1 // CS拉高(别名ATT)
#define CS_L() PBout(14) = 0 // CS拉低(别名ATT)

#define CLK_H() PBout(15) = 1 // 时钟拉高
#define CLK_L() PBout(15) = 0 // 时钟拉低

// --------------------------------VAULE-------------------------------- 变量定义
const uint8_t ps2_cmd[9] = {0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // 请求获取数据命令
static uint8_t ps2_receive[9];                                                     // 接收数据的缓存

// --------------------------------FUNCTION-------------------------------- 函数定义
// ----------------INIT---------------- PS2初始化
void ps2_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // GPIO配置
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // DATA 信号从手柄到主机   输入口
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // COMMMAND 信号从主机到手柄  输出
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // CS 手柄出发信号 信号在通信期间处于低电平
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // CLK 信号从主机到手柄   输出口
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // 关闭PS2手柄使能
    CS_H();
}

// ----------------CONTROL----------------
/**
 * @brief PS2通信
 *
 * @param send_data 发送数据
 * @return uint8_t 接收数据
 *
 * @note  通信过程中，先发送数据，再读取数据
 */
uint8_t ps2_comm(uint8_t sendData)
{
    volatile uint8_t res = 0;
    volatile uint8_t ref;

    // 写入命令，并读取一个1字节数据
    for (ref = 0x01; ref > 0x00; ref <<= 1)
    {
        ////输出一位数据
        if (ref & sendData)
            CMD_H();
        else
            CMD_L();

        CLK_L();
        delay_us(16);

        // 读取一位数据
        if (DI())
            res |= ref;
        CLK_H();
        delay_us(16);
    }

    // 返回读出数据
    return res;
}

// PS2获取按键及摇杆数值
void ps2_read(ps2_data *ps2Data)
{
    uint8_t i;

    // 使能手柄
    CS_L();

    // 读取PS2数据
    for (i = 0; i < 9; i++)
    {
        ps2_receive[i] = ps2_comm(ps2_cmd[i]);
    }

    // 关闭使能
    CS_H();

    // 数值传递
    ps2Data->mode = ps2_receive[1];
    ps2Data->btn1 = ~ps2_receive[3];
    ps2Data->btn2 = ~ps2_receive[4];
    ps2Data->RJoy_LR = ps2_receive[5];
    ps2Data->RJoy_UD = ps2_receive[6];
    ps2Data->LJoy_LR = ps2_receive[7];
    ps2Data->LJoy_UD = ps2_receive[8];
}
