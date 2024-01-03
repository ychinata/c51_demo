#include <REGX52.H>
#include "timer.h"
#include "delay.h"
#include "oled.h"

//�������Žӿ�
sbit Trig = P2^0;
sbit Echo = P2^1;

/**
  * @brief  HC-SR04��ʼ��
  * @param  ��
  * @retval ��
  */
void HCSR04_Init(void)
{
	TIMER0_Init();
	Trig = 0;
	Echo = 0;
}

/**
  * @brief  HC-SR04����һ��12us�Ĵ����ź�
  * @param  ��
  * @retval ��
  */
void HCSR04_Trig(void)
{
    //��Trig�ڸߵ�ƽ10us���ϣ�������ģ����Զ�����8��40khz�ķ���
	unsigned char i;
	Trig = 1;
	i = 50;while (--i);		//��ʱ12us
    //DELAY_12us();
	Trig = 0;
}

/**
  * @brief  HC-SR04���մ����źŲ�����ز��źŸߵ�ƽʱ��
  * @param  ��
  * @retval ��
  */
void HCSR04_Recv(void)
{
	HCSR04_Trig();
    OLED_ShowNum(0, 0, 1, 4, 16);
	while(!Echo);   // ����������Ϊ0ʱ�ȴ�
    OLED_ShowNum(0, 0, 2, 4, 16);
	TR0 = 1;        // ��������
	while(Echo);    // ����������Ϊ1ʱ��ʱ������
    OLED_ShowNum(0, 0, 3, 4, 16);
	TR0 = 0;        // �رռ���
}

/**
  * @brief  HC-SR04����ģ�����ϰ���ľ���
  * @param  Duration(����ʱ��)	���͵����յļ��ʱ��
  * @param  Distance  ģ�����ϰ���ľ���
  * @retval Distance
  */
float HCSR04_Calc(void)
{
	unsigned int Duration = 0;
	float Distance = 0;
	
	Duration = TH0*256+TL0;
	Distance = Duration*0.017;//ʱ��*����/2������=340m/s=0.034cm/us
	TH0 = 0;
	TL0 = 0;
	
	return Distance;
}

float HCSR04_GetDistance(void)
{   
    float distance = 0.0;
    //HCSR04_Trig();
    HCSR04_Recv();
    distance = HCSR04_Calc();
    return distance;    
}

void HCSR04_Task(void)
{
    //todo
}
