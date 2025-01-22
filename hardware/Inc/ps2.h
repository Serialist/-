/**
 *   PS2数据定义
 *   BYTE   DATA   解释
 *   01     idle
 *   02     0x73   手柄工作模式
 *   03     0x5A   Bit0  Bit1  Bit2  Bit3  Bit4  Bit5  Bit6  Bit7
 *   04     data   SLCT  JOYR  JOYL  STRT   UP  RGIHT  DOWN  LEFT
 *   05     data    L2    R2    L1    R1    Y     B     A     X
 *   06     data   右边摇杆  0x00 = 左    0xff = 右
 *   07     data   右边摇杆  0x00 = 上    0xff = 下
 *   08     data   左边摇杆  0x00 = 左    0xff = 右
 *   09     data   左边摇杆  0x00 = 上    0xff = 下
 *
 * PA4 -> DI
 * PA5 -> CMD
 * PA6 -> CS
 * PA7 -> CLK
 */

#ifndef __PS2_H
#define __PS2_H

#include "main.h"

// --------------------------------VAULE--------------------------------
// 变量定义PS2手柄键值数据结构体
typedef struct
{
    uint8_t mode; /* 手柄的工作模式 */
                  /* Bit0  Bit1  Bit2  Bit3  Bit4  Bit5  Bit6  Bit7 */
    uint8_t btn1; /* SLCT  JOYR  JOYL  STRT   UP  RIGHT  DOWN  LEFT */

    uint8_t btn2; /*  L2    R2    L1    R1    Y     A     B     X   */

    uint8_t RJoy_LR; /* 右边摇杆  0x00 = 左    0xff = 右 */

    uint8_t RJoy_UD; /* 右边摇杆  0x00 = 上    0xff = 下 */

    uint8_t LJoy_LR; /* 左边摇杆  0x00 = 左    0xff = 右 */

    uint8_t LJoy_UD; /* 左边摇杆  0x00 = 上    0xff = 下 */

} ps2_data;

// --------------------------------FUNCTION-------------------------------- 函数定义
// ----------------INIT---------------- PS2初始化
void ps2_init(void);

// ----------------CONTROL----------------
uint8_t ps2_comm(uint8_t sendData); // PS2通信
void ps2_read(ps2_data *ps2Data);   // PS2获取按键及摇杆数值

#endif
