#ifndef _TIMER01INTERRUPT_H
#define _TIMER01INTERRUPT_H
#include "Timer01interrupt.h"

void DRV8833_Timer1_Init() 
{
	TMOD=0x11;                //���ö�ʱ��ģʽ
	TH1=(65536-100)/256;	 //���ö�ʱ��ֵ 
	TL1=(65536-100)%256;    //���ö�ʱ��ֵ
	ET1= 1;
	EA = 1;
    TR1= 1;
}



#endif