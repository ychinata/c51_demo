#include <REGX52.H>
#include <INTRINS.H> 
#include "delay.h"
#include "oled.h"
#include "servo.h"

//2023.6.20
void main(void)
{

    OLED_Init();			//初始化OLED  
    OLED_Clear(); 		//清屏函数
    //舵机
    Timer0_Init();
    SERVO_Init();    
    
    OLED_ShowString(0,0,"Servo SG90 Demo",16);  
    OLED_ShowString(6,3,"2023.6.20",16);      
        
    while(1)		       /*无限循环*/
    {       
        SERVO_Task();
        
    }

}   
