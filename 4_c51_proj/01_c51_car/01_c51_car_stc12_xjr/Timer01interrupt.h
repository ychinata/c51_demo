#ifndef _TIMER01INTERRUPT_H
#define _TIMER01INTERRUPT_H
#include "Timer01interrupt.h"

void DRV8833_Timer1_Init() 
{
	TMOD=0x11;                //设置定时器模式
	TH1=(65536-100)/256;	 //设置定时初值 
	TL1=(65536-100)%256;    //设置定时初值
	ET1= 1;
	EA = 1;
    TR1= 1;
}



#endif