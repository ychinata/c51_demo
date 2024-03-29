// 2023.6.24
#include <REGX52.H>
#include "car_mecanum.h"
#include "delay.h"
#include "drv8833.h"

extern unsigned int g_count;

/* 底盘电机描述2023.6.24 
    xIN1=1, xIN2=0正转时，左边两个轮子向前转，右边两个轮子向后转
    左边两个轮子由 DRV8833_1 控制，右边由DRV8833_2 控制

    动作1：顺时针转——左侧向前，右侧向后

 */

// 顺时针转
void CAR_MEC_RotateClockwise(void)
{
    DRV8833_1_Forward();
    DRV8833_2_Backward();
}

// 逆时针转
void CAR_MEC_RotateAnticlockwise(void)
{
    DRV8833_2_Forward();
    DRV8833_1_Backward();
}

// 前进
void CAR_MEC_Forward(void)
{
    DRV8833_2_Forward();
    DRV8833_1_Forward();
}

// 后退
void CAR_MEC_Backward(void)
{
    DRV8833_2_Backward();
    DRV8833_1_Backward();
}

void CAR_Stop(void)
{
    DRV8833_SetSpeed(0);
}

void CAR_TrunLeft(void)
{
    //车左转：左轮慢，右轮快
    DRV8833_SetSpeedLeft(0);
    DRV8833_SetSpeedRight(20);
    DRV8833_LF_Forward(); 
    DRV8833_RF_Forward();
    DRV8833_LB_Forward();
    DRV8833_RB_Forward();     
}

void CAR_TrunRight(void)
{
    //车右转：左轮快，右轮慢
    DRV8833_SetSpeedLeft(20);
    DRV8833_SetSpeedRight(0);
    DRV8833_LF_Forward(); 
    DRV8833_RF_Forward();
    DRV8833_LB_Forward();
    DRV8833_RB_Forward();     
}


// 向右平移-麦轮
void CAR_MEC_ShiftRight(void)
{
    DRV8833_LF_Forward(); DRV8833_RF_Backward();
    DRV8833_LB_Backward();DRV8833_RB_Forward();           
}

// 向左平移-麦轮
void CAR_MEC_ShiftLeft(void)
{
    DRV8833_LF_Backward(); DRV8833_RF_Forward();
    DRV8833_LB_Forward();  DRV8833_RB_Backward();           
}

// 麦轮-走四方形
void CAR_MEC_Task(void)
{
//    CAR_MEC_RotateClockwise();
//    DELAY_ms(5000);
//    CAR_MEC_RotateAnticlockwise();
//    DELAY_ms(5000);
    
    CAR_MEC_Forward();
    DELAY_ms(5000);
    CAR_MEC_ShiftRight();
    DELAY_ms(5000);
    CAR_MEC_Backward();
    DELAY_ms(5000);  
    CAR_MEC_ShiftLeft();
    DELAY_ms(5000);
    
}

void CAR_NormalTask(void)
{    
//    DRV8833_SetSpeed(20);
//    CAR_MEC_Forward();
//    DELAY_ms(5000);
    
    CAR_TrunLeft();    
    DELAY_ms(5000);
    CAR_Stop();       
    DELAY_ms(5000);    
    CAR_TrunRight();
    DELAY_ms(5000);       

//    CAR_MEC_Backward();
//    DELAY_ms(5000);
}
