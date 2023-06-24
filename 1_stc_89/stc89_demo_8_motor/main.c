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

    OLED_Init();			//��ʼ��OLED  
    OLED_Clear(); 		//��������
    OLED_ShowString(0,0,"DC Motor Demo",16);  
    OLED_ShowString(6,3,"2023.6.24",16);  
    
    // ֱ�����
    DRV8833_Init();
    
    //���
//    Timer0_Init();
//    SERVO_Init();    
    g_motor_speed = 50;    
        
    while(1)		       /*����ѭ��*/
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
//            // ��ת
//            DRV8833_1_Forward();
//            
//        } else {
//            // ��ת
//            DRV8833_1_Stop();
//        }
//        if(g_count==100)  {      
//            g_count=0;           
//        }
//        DELAY_ms(10);
    }

}
