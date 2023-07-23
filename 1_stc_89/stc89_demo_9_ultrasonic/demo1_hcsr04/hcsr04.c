#include <REGX52.H>
#include "timer.h"
#include "delay.h"
#include "oled.h"

//定义引脚接口
sbit Trig = P2^0;
sbit Echo = P2^1;

/**
  * @brief  HC-SR04初始化
  * @param  无
  * @retval 无
  */
void HCSR04_Init(void)
{
	TIMER0_Init();
	Trig = 0;
	Echo = 0;
}

/**
  * @brief  HC-SR04接收一个12us的触发信号
  * @param  无
  * @retval 无
  */
void HCSR04_Trig(void)
{
    //给Trig口高电平10us以上，超声波模块会自动发出8个40khz的方波
	unsigned char i;
	Trig = 1;
	i = 50;while (--i);		//延时12us
    //DELAY_12us();
	Trig = 0;
}

/**
  * @brief  HC-SR04接收触发信号并计算回波信号高电平时间
  * @param  无
  * @retval 无
  */
void HCSR04_Recv(void)
{
	HCSR04_Trig();
    OLED_ShowNum(0, 0, 1, 4, 16);
	while(!Echo);   // 当接收引脚为0时等待
    OLED_ShowNum(0, 0, 2, 4, 16);
	TR0 = 1;        // 开启计数
	while(Echo);    // 当接收引脚为1时定时器计数
    OLED_ShowNum(0, 0, 3, 4, 16);
	TR0 = 0;        // 关闭计数
}

/**
  * @brief  HC-SR04计算模块与障碍间的距离
  * @param  Duration(持续时间)	发送到接收的间隔时间
  * @param  Distance  模块与障碍间的距离
  * @retval Distance
  */
float HCSR04_Calc(void)
{
	unsigned int Duration = 0;
	float Distance = 0;
	
	Duration = TH0*256+TL0;
	Distance = Duration*0.017;//时间*音速/2，音速=340m/s=0.034cm/us
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
