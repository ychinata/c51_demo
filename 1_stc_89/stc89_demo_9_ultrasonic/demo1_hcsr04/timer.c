#include <REGX52.H>
#include "timer.h"

/* STC89C52中断资源
    interrupt 0 -- Int0
    interrupt 1 -- Timer0
    interrupt 2 -- Int1
    interrupt 3 -- Timer1
    interrupt 4 -- Uart
    interrupt 5 -- Timer2
    interrupt 6 -- Int2
    interrupt 7 -- Int3
 */

// 定时器1初始化？
//void SERVO_Timer0_Init() 
//{
//	TMOD=0X10;
//	TH1=(65536-100)/256;	  //100US定时
//	TL1=(65536-100)%256;
//	TR1= 1;             // 开启T1
//	ET1= 1;             // 允许T1中断
//	EA = 1;             // 开启总中断
//}


void TIMER0_Init(void)
{
	TMOD = 0x01;// 定义计时器0工作方式为1
	TH0 = 0;    // T0高位值
	TL0 = 0;    // T0低位值
	ET0= 1;     // 允许T0中断
	EA = 1;
}
