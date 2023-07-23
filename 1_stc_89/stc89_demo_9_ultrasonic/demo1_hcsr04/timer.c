#include <REGX52.H>
#include "timer.h"

/* STC89C52�ж���Դ
    interrupt 0 -- Int0
    interrupt 1 -- Timer0
    interrupt 2 -- Int1
    interrupt 3 -- Timer1
    interrupt 4 -- Uart
    interrupt 5 -- Timer2
    interrupt 6 -- Int2
    interrupt 7 -- Int3
 */

// ��ʱ��1��ʼ����
//void SERVO_Timer0_Init() 
//{
//	TMOD=0X10;
//	TH1=(65536-100)/256;	  //100US��ʱ
//	TL1=(65536-100)%256;
//	TR1= 1;             // ����T1
//	ET1= 1;             // ����T1�ж�
//	EA = 1;             // �������ж�
//}


void TIMER0_Init(void)
{
	TMOD = 0x01;// �����ʱ��0������ʽΪ1
	TH0 = 0;    // T0��λֵ
	TL0 = 0;    // T0��λֵ
	ET0= 1;     // ����T0�ж�
	EA = 1;
}
