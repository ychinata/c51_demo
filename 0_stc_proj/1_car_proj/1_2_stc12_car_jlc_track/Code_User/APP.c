#include "APP.h"
#include "Motor.h"

#define	Left_LED	P27
#define Right_LED	P22

#define	Left_Flow		P24
#define	Right_Flow 	P25

// 实现循迹主要逻辑
void APP_Loop(void)
{
	if((Left_Flow==1) & (Right_Flow==1))
	{
		Motor_Stop();
		Left_LED = 1;
		Right_LED = 1;
		return;
	}
	if(Left_Flow==1)
	{
		Motor_Right();
		Left_LED = 0;
		Right_LED = 1;
		return;
	}
	if(Right_Flow==1)
	{
		Motor_Left();
		Left_LED = 1;
		Right_LED = 0;
		return;
	}
	Motor_Forward();
	Left_LED = 0;
	Right_LED = 0;
}




