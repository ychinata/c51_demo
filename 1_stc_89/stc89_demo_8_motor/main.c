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
    
    //舵机
//    Timer0_Init();
//    SERVO_Init();    
    g_motor_speed = 50;    
        
    while(1)		       /*无限循环*/
    {       
        //SERVO_Task();
        //DRV8833_Task();
        DRV8833_2_Forward();
        DELAY_ms(2000);
        DRV8833_2_Backward();
//        DRV8833_1_Stop();
        DELAY_ms(2000);
        
//        g_count++;        
//        if(g_count >= 0 && g_count <= g_motor_speed)
//        {
//            // 正转
//            DRV8833_1_Forward();
//            
//        } else {
//            // 正转
//            DRV8833_1_Stop();
//        }
//        if(g_count==100)  {      
//            g_count=0;           
//        }
//        DELAY_ms(10);
    }

}
