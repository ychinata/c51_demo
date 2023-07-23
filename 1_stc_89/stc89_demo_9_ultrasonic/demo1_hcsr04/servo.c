//#include "reg52.h"			//	   ͷ�ļ�
#include <REGX52.H>
#include "delay.h"
#include "servo.h"
#include "timer.h"

sbit Sevro_moto_pwm = P3^7;	   	// ����ź��ߣ���ɫ��

unsigned char pwm_val  = 0;//��������
unsigned char push_val = 14;//������У�����Լ��1.5MS �ź�
				

//void delay1ms(unsigned int k)   //��ʱ1ms������k���ڶ��پ���ʱ����ms
//{
//    unsigned int a,b,c,d;
//	for(d=0;d<k;d++)
//        for(c=1;c>0;c--)
//            for(b=50;b>0;b--)
//                for(a=2;a>0;a--);
//}								   


/**********************************************************************************************
**                              TIMER1�жϷ����Ӻ�������PWM�ź�
**********************************************************************************************/
void time1()interrupt 3 using 2 // using���Բ���
{	
    TH1=(65536-100)/256;	  //100US��ʱ
    TL1=(65536-100)%256;
    pwm_val++;
    
    if(pwm_val<=push_val)	  
        Sevro_moto_pwm=1;   //PWM�źŸߵ�ƽʱ��
    else 
        Sevro_moto_pwm=0;   //PWM�źŸߵ�ƽʱ��
    if(pwm_val>=100)
        pwm_val=0;
}

// ��ʱ��0��ʼ��
//void SERVO_Timer0_Init(void) 
//{
//	TMOD=0X10;
//	TH1=(65536-100)/256;	  //100US��ʱ
//	TL1=(65536-100)%256;
//	TR1= 1;
//	ET1= 1;
//	EA = 1;
//}

// 90�ȶ��
void SERVO_Init() 
{
    TIMER1_Init(void);
    push_val=13;	  //������У�����ִ��ָ�������ڣ�����PWM�ź������
	DELAY_ms(1000);   //��ʱ1S�ö��ת����λ�ã�ͣ��һ��
}

// 90�ȶ��
void SERVO_Set90DegPlus()
{
    push_val=4;	  //�������תԼ90�ȣ�����ִ��ָ�������ڣ�����PWM�ź������
}

// 90�ȶ��
void SERVO_Set90DegMinus()
{
    push_val=22;	  //�����תԼ90�ȣ�����ִ��ָ�������ڣ�����PWM�ź������
}
        

/**********************************************************************************************
**                                       ������
**********************************************************************************************/
void SERVO_Task(void)
{
    SERVO_Set90DegPlus();
    DELAY_ms(2000); //��ʱ500MS�ö��ת����λ��

    SERVO_Set90DegMinus();
    DELAY_ms(2000); //��ʱ500MS�ö��ת����λ��
}   