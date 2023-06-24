//2023.6.24
#include <REGX52.H>

#ifndef __DRV8833_H
#define __DRV8833_H

/*
// DRV8833 - 51��Ƭ�� 

// VM����ӵ�Դ��ֻ����Ƭ��������Ҳ���Թ���������ת�ٽ���

    AIN2 - P31
    AIN1 - P32
    STBY - P33
    BIN1 - P34
    BIN2 - P35
    
 */

sbit DRV8833_1_AIN2 = P3^6; // P3.0,P3.1�Ǵ��ڣ�����ʹ��.�˷��˺ܶ�ʱ����Բŷ����������...
sbit DRV8833_1_AIN1 = P3^2;         
sbit DRV8833_1_STBY = P3^3;
sbit DRV8833_1_BIN1 = P3^4;
sbit DRV8833_1_BIN2 = P3^5;
//sbit beep=P2^7;  

sbit DRV8833_2_AIN2 = P1^1;
sbit DRV8833_2_AIN1 = P1^2;         
sbit DRV8833_2_STBY = P1^3;
sbit DRV8833_2_BIN1 = P1^4;
sbit DRV8833_2_BIN2 = P1^5;


void DRV8833_Timer0_Init();
void DRV8833_Init(void);

void DRV8833_1_Forward(void);
void DRV8833_1_Backward(void);
void DRV8833_1_Stop(void);
void DRV8833_2_Forward(void);
void DRV8833_2_Backward(void);
void DRV8833_2_Stop(void);

void DRV8833_Task(void);

#endif