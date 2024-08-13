#include "STC89C5xRC_RDP.h"
#include "SYS_LOOP.h"
#include "ProgramLogic.h"
#include "delay.h"
#include "Motor.h"

void Tim1_Isr(void) interrupt 3
{
	TL1 = 0x66;//���ö�ʱ��ֵ
	TH1 = 0xFC;//���ö�ʱ��ֵ
	SYS_TimerInterrupt_App();
}

void main2(void)
{	
	while (1) {
        Motor_Forward();
        Delay_ms(1000);
        Motor_Stop();
        Delay_ms(1000);        
    }
}

void main(void)
{
	
	TMOD = 0x10;//���ö�ʱ��ģʽ
	TL1 = 0x66;//���ö�ʱ��ֵ
	TH1 = 0xFC;//���ö�ʱ��ֵ
	TF1 = 0;//���TF1��־
	ET1 = 1;
	TR1 = 1;//��ʱ��1��ʼ��ʱ
	EA=1;
	SYS_LOOP_Init();
    
	ProgramLogic_Main();//��ִ��ҵ���߼�
	
	SYS_LOOP_While_APP();//ѭ��ִ��ϵͳ������
}




