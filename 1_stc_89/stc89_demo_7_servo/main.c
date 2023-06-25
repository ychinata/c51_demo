#include <REGX52.H>
#include <INTRINS.H> 
#include "delay.h"
#include "oled.h"
#include "servo.h"

//2023.6.20
void main(void)
{

    OLED_Init();			//��ʼ��OLED  
    OLED_Clear(); 		//��������
    //���
    Timer0_Init();
    SERVO_Init();    
    
    OLED_ShowString(0,0,"Servo SG90 Demo",16);  
    OLED_ShowString(6,3,"2023.6.20",16);      
        
    while(1)		       /*����ѭ��*/
    {       
        SERVO_Task();
        
    }

}   
