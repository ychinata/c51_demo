// 2023.6.24
#include <REGX52.H>
#include "car_mecanum.h"
#include "delay.h"
#include "drv8833.h"

extern unsigned int g_count;

/* ���̵������2023.6.24 
    xIN1=1, xIN2=0��תʱ���������������ǰת���ұ������������ת
    ������������� DRV8833_1 ���ƣ��ұ���DRV8833_2 ����

    ����1��˳ʱ��ת���������ǰ���Ҳ����

 */

// ˳ʱ��ת
void CAR_MEC_RotateClockwise(void)
{
    DRV8833_1_Forward();
    DRV8833_2_Backward();
}

// ��ʱ��ת
void CAR_MEC_RotateAnticlockwise(void)
{
    DRV8833_2_Forward();
    DRV8833_1_Backward();
}

// ǰ��
void CAR_MEC_Forward(void)
{
    DRV8833_2_Forward();
    DRV8833_1_Forward();
}

// ����
void CAR_MEC_Backward(void)
{
    DRV8833_2_Backward();
    DRV8833_1_Backward();
}


// ����ƽ��
void CAR_MEC_ShiftRight(void)
{
    DRV8833_LF_Forward(); DRV8833_RF_Backward();
    DRV8833_LB_Backward();DRV8833_RB_Forward();           
}

// ����ƽ��
void CAR_MEC_ShiftLeft(void)
{
    DRV8833_LF_Backward(); DRV8833_RF_Forward();
    DRV8833_LB_Forward();  DRV8833_RB_Backward();           
}

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