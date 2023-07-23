#include <REGX52.H>
#include <INTRINS.H> 
#include "delay.h"
#include "hcsr04.h"
#include "oled.h"
#include "servo.h"

void ULTRASONIC_Task(void);


/*Ӳ������
//OLED
SCL     --      P2^5     // D0(SCLK) ʱ��
SDA     --      P2^3    // D1��MOSI������
//������
Trig    --      P1^0;
Echo    --      P1^1;

*/

//2023.6.20
void main(void)
{
    
    OLED_Init();			//��ʼ��OLED  
    OLED_Clear(); 		//��������
    HCSR04_Init();
    //���
//    SERVO_Timer0_Init();
//    SERVO_Init();    
    
    //OLED_ShowString(0,0,"Ultrasonic Demo",16);  
    //OLED_ShowNum(0, 0, 253, 4, 16);
    //OLED_ShowString(4,6,"2023.7.22",16);      
    OLED_ShowNum(0, 0, 0, 4, 16);
        
    while(1)		       /*����ѭ��*/
    {       
//        SERVO_Task();
//        ULTRASONIC_Task();               
//    float distance = 0.0;
//    HCSR04_Trig();
    HCSR04_Recv();
//    //distance = HCSR04_Calc();   
    OLED_ShowString(4,6,"2023.7.3",16);     
    DELAY_ms(500);        
        
    }

}   


void ULTRASONIC_Task(void)
{
    float distance = 0.0;
    distance = HCSR04_GetDistance();
    OLED_ShowNum(0, 0, distance, 4, 16);
    //OLED_ShowString(4,6,"2023.7.22",16);  
    DELAY_ms(500);
}
