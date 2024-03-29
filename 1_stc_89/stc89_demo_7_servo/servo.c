//#include "reg52.h"			//	   头文件
#include <REGX52.H>
#include "delay.h"
#include "servo.h"

sbit Sevro_moto_pwm = P3^7;	   	// 舵机信号线（橙色）

unsigned char pwm_val  = 0;//变量定义
unsigned char push_val = 14;//舵机归中，产生约，1.5MS 信号
				

//void delay1ms(unsigned int k)   //延时1ms函数，k等于多少就延时多少ms
//{
//    unsigned int a,b,c,d;
//	for(d=0;d<k;d++)
//        for(c=1;c>0;c--)
//            for(b=50;b>0;b--)
//                for(a=2;a>0;a--);
//}								   


/**********************************************************************************************
**                              TIMER1中断服务子函数产生PWM信号
**********************************************************************************************/
void time1()interrupt 3 using 2 // using可以不用
{	
    TH1=(65536-100)/256;	  //100US定时
    TL1=(65536-100)%256;
    pwm_val++;
    
    if(pwm_val<=push_val)	  
        Sevro_moto_pwm=1;   //PWM信号高电平时间
    else 
        Sevro_moto_pwm=0;   //PWM信号高电平时间
    if(pwm_val>=100)
        pwm_val=0;
}

// 定时器0初始化
void Timer0_Init() 
{
	TMOD=0X10;
	TH1=(65536-100)/256;	  //100US定时
	TL1=(65536-100)%256;
	TR1= 1;
	ET1= 1;
	EA = 1;
}

// 90度舵机
void SERVO_Init() 
{
    push_val=13;	  //舵机归中，机器执行指令有周期，所以PWM信号有误差
	DELAY_ms(1000);   //延时1S让舵机转到其位置，停留一下
}

// 90度舵机
void SERVO_Set90DegPlus()
{
    push_val=4;	  //舵机向正转约90度，机器执行指令有周期，所以PWM信号有误差
}

// 90度舵机
void SERVO_Set90DegMinus()
{
    push_val=22;	  //舵机向反转约90度，机器执行指令有周期，所以PWM信号有误差
}
        

/**********************************************************************************************
**                                       主函数
**********************************************************************************************/
void SERVO_Task(void)
{
    SERVO_Set90DegPlus();
    DELAY_ms(2000); //延时500MS让舵机转到其位置

    SERVO_Set90DegMinus();
    DELAY_ms(2000); //延时500MS让舵机转到其位置
}   
