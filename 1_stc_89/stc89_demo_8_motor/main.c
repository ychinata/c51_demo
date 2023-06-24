#include <REGX52.H>
#include <INTRINS.H> 
#include "delay.h"
#include "drv8833.h"
#include "oled.h"
#include "servo.h"


extern unsigned int g_count;
extern unsigned int g_motor_speed;


//2023.6.20
void main(void)
{

    OLED_Init();			//初始化OLED  
    OLED_Clear(); 		//清屏函数
    OLED_ShowString(0,0,"DC Motor Demo",16);  
    OLED_ShowString(6,3,"2023.6.24",16);  
    
    // 直流电机
    DRV8833_Init();
    g_motor_speed = 0;
    
    //舵机
//    Timer0_Init();
//    SERVO_Init();    
 
        
    while(1)		       /*无限循环*/
    {       
        //SERVO_Task();
        DRV8833_Task();
        

        
    }

}
