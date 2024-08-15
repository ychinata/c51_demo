#include "STC89C5xRC_RDP.h"
#include "SYS_LOOP.h"
#include "ProgramLogic.h"

void Tim1_Isr(void) interrupt 3
{
	TL1 = 0x66;//设置定时初值
	TH1 = 0xFC;//设置定时初值
	SYS_TimerInterrupt_App();
}

void main(void)
{
	
	TMOD = 0x10;//设置定时器模式
	TL1 = 0x66;//设置定时初值
	TH1 = 0xFC;//设置定时初值
	TF1 = 0;//清除TF1标志
	ET1 = 1;
	TR1 = 1;//定时器1开始计时
	EA=1;
	SYS_LOOP_Init();
	ProgramLogic_Main();//先执行业务逻辑
	
	SYS_LOOP_While_APP();//循环执行系统调度器
}