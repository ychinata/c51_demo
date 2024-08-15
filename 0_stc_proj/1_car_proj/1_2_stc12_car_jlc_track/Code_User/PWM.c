//微信公众号：物联网零妖
//PWM输出设置 Timer0 输出2kHZ的波形，占空比 0~100% 可调
#include<PWM.h>


#define LF_A_IO P02//左前电机A
#define LF_B_IO P03//左前电机B
#define LB_A_IO P01//左后电机A
#define LB_B_IO P00//左后电机B

#define RF_A_IO P05//右前电机A
#define RF_B_IO P04//右前电机B
#define RB_A_IO P06//右后电机A
#define RB_B_IO P07//右后电机B

extern unsigned char LF_A,LF_B,LB_A,LB_B,RF_A,RF_B,RB_A,RB_B;
static unsigned int PWM_H=0,PWM_L=0;//高电平时间和低电平时间
static unsigned char PWM_IO_1=0;
//初始化PWM定时器
void PWM_Init(void)
{
	PWM_H = 0;
	PWM_L = 0;
	
	//定时器0设置
	TMOD |= 0x01;//设置定时器模式
  TL0 = 0;//设置定时初值
	TH0 = 0;//设置定时初值
	TF0 = 0;//清除TF0标志
  ET0 = 1;//使能定时器中断
	
	LF_A_IO=0;
	LF_B_IO=0;
	LB_A_IO=0;
	LB_B_IO=0;
	RF_A_IO=0;
	RF_B_IO=0;
	RB_A_IO=0;
	RB_B_IO=0;
	
	PWM_IO_1=0;
	
}
//调整占空比
void PWM_Set_ZhanKongBi(unsigned char a)
{
	float ZhanKongBi;
	ZhanKongBi = 100 - a;
	
	if(a<2)
	{
		LF_A_IO=0;
		LF_B_IO=0;
		LB_A_IO=0;
		LB_B_IO=0;
		RF_A_IO=0;
		RF_B_IO=0;
		RB_A_IO=0;
		RB_B_IO=0;
		PWM_IO_1=0;
		TR0 = 0;
	}
	else if(a>98)
	{
		LF_A_IO=1;
		LF_B_IO=1;
		LB_A_IO=1;
		LB_B_IO=1;
		RF_A_IO=1;
		RF_B_IO=1;
		RB_A_IO=1;
		RB_B_IO=1;
		PWM_IO_1=1;
		TR0 = 0;
	}
	else
	{
		ZhanKongBi = 10000 * ZhanKongBi / 100 ;
		PWM_H = 0XFFFF - ZhanKongBi;
		PWM_L = 0XFFFF - 10000 + ZhanKongBi;
		TR0 = 1;
	}
}
void TM0_Isr(void) interrupt 1
{
	if(PWM_IO_1)
	{
		LF_A_IO=0;
		LF_B_IO=0;
		LB_A_IO=0;
		LB_B_IO=0;
		RF_A_IO=0;
		RF_B_IO=0;
		RB_A_IO=0;
		RB_B_IO=0;
		PWM_IO_1=0;
		TL0 = PWM_H;
		TH0 = PWM_H>>8;
	}
	else
	{
		if(LF_A)
			LF_A_IO=1;
		if(LF_B)
			LF_B_IO=1;
		if(LB_A)
			LB_A_IO=1;
		if(LB_B)
			LB_B_IO=1;
		if(RF_A)
			RF_A_IO=1;
		if(RF_B)
			RF_B_IO=1;
		if(RB_A)
			RB_A_IO=1;
		if(RB_B)
			RB_B_IO=1;
		PWM_IO_1=1;
		TL0 = PWM_L;
		TH0 = PWM_L>>8;
	}
}
//







