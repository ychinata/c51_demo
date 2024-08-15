#include "APP.h"
#include "Motor.h"

#define	Left_LED	P27
#define Right_LED	P22

// 循迹传感器，碰黑线或车悬空没反射，输出高电平1；碰白纸或有反射，输出低电平0。
#define	Left_Flow		P24     // 右侧传感器
#define	Right_Flow 	P25         // 左侧传感器

// 实现循迹主要逻辑
void APP_Loop(void)
{
	if((Left_Flow==1) & (Right_Flow==1)) { // 悬空或两路碰到黑线，停止
		Motor_Stop();
		Left_LED = 1;
		Right_LED = 1;
		return;
	} if(Left_Flow==1) {    // 右侧压黑线，车偏左，需要右转
		Motor_Right();
		Left_LED = 0;
		Right_LED = 1;
		return;
	} if(Right_Flow==1) {   // 左侧压黑线，车偏右，需要左转
		Motor_Left();
		Left_LED = 1;
		Right_LED = 0;
		return;
	}
    // 没有传感器压黑线，小车直行，左右侧车大灯常亮
	Motor_Forward();
	Left_LED = 0;
	Right_LED = 0;
}




