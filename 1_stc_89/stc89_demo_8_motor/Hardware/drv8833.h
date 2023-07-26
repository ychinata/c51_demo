//2023.6.24
#include <REGX52.H>

#ifndef __DRV8833_H
#define __DRV8833_H

extern unsigned int g_count;
extern unsigned int g_motor_speed;

/*
// DRV8833 - 51单片机 

// VM不外接电源，只靠单片机供电电机也可以工作，但是转速较慢

    AIN2 - P31
    AIN1 - P32
    STBY - P33
    BIN1 - P34
    BIN2 - P35
    
 */

// 根据2轮或4轮驱动，可灵活修改以下映射
// #define MOTOR_LF_PIN1 DRV8833_1_AIN1
// #define MOTOR_LF_PIN2 DRV8833_1_AIN2
// #define MOTOR_LB_PIN1 DRV8833_1_BIN1
// #define MOTOR_RF_PIN1 DRV8833_2_AIN1
// #define MOTOR_RB_PIN1 DRV8833_2_BIN1

sbit DRV8833_1_AIN2 = P3^6; // P3.0,P3.1是串口，不可使用.浪费了很多时间调试才发现这个问题...
sbit DRV8833_1_AIN1 = P3^2;         
sbit DRV8833_1_STBY = P3^3;
sbit DRV8833_1_BIN1 = P3^4;
sbit DRV8833_1_BIN2 = P3^5; 

sbit DRV8833_2_AIN2 = P1^1;
sbit DRV8833_2_AIN1 = P1^2;         
sbit DRV8833_2_STBY = P1^3;
sbit DRV8833_2_BIN1 = P1^4;
sbit DRV8833_2_BIN2 = P1^5;

//函数声明

void DRV8833_SetSpeed(unsigned int speed);
void DRV8833_SetSpeedLeft(unsigned int speed);
void DRV8833_SetSpeedRight(unsigned int speed);

void DRV8833_Timer0_Init();
void DRV8833_Init(void);

void DRV8833_1_Forward(void);
void DRV8833_1_Backward(void);
void DRV8833_1_Stop(void);
void DRV8833_2_Forward(void);
void DRV8833_2_Backward(void);
void DRV8833_2_Stop(void);

// 单轮控制
void DRV8833_LF_Forward(void);
void DRV8833_LB_Forward(void);
void DRV8833_LF_Backward(void);
void DRV8833_LB_Backward(void);
void DRV8833_RF_Forward(void);
void DRV8833_RB_Forward(void);
void DRV8833_RF_Backward(void);
void DRV8833_RB_Backward(void);
//单轮stop-无效
/*
void DRV8833_LF_Stop(void);
void DRV8833_LB_Stop(void);
void DRV8833_RF_Stop(void);
void DRV8833_RB_Stop(void);
*/
void DRV8833_Task(void);

#endif
