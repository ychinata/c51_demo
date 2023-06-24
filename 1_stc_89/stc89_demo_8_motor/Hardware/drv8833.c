//2023.6.24
#include <REGX52.H>
#include "delay.h"
#include "drv8833.h"

unsigned int g_count = 0;
unsigned int g_motor_speed = 0;


void DRV8833_1_Forward(void)
{
    DRV8833_1_STBY = 1;
    
    DRV8833_1_AIN1 = 1;
    DRV8833_1_AIN2 = 0;
    DRV8833_1_BIN1 = 1;
    DRV8833_1_BIN2 = 0;   
}

void DRV8833_1_Backward(void)
{
    DRV8833_1_STBY = 1;   
    
    DRV8833_1_AIN1 = 0;
    DRV8833_1_AIN2 = 1;
    DRV8833_1_BIN1 = 0;
    DRV8833_1_BIN2 = 1;   
}

void DRV8833_1_Stop(void)
{
    DRV8833_1_STBY = 0;
}

void DRV8833_2_Forward(void)
{
    DRV8833_2_STBY = 1;
    
    DRV8833_2_AIN1 = 1;
    DRV8833_2_AIN2 = 0;
    DRV8833_2_BIN1 = 1;
    DRV8833_2_BIN2 = 0;   
}

void DRV8833_2_Backward(void)
{
    DRV8833_2_STBY = 1;   
    
    DRV8833_2_AIN1 = 0;
    DRV8833_2_AIN2 = 1;
    DRV8833_2_BIN1 = 0;
    DRV8833_2_BIN2 = 1;   
}

void DRV8833_2_Stop(void)
{
    DRV8833_2_STBY = 0;
}

void DRV8833_Init(void)
{
    DRV8833_1_Forward();
    DRV8833_2_Forward();
    //DRV8833_2_Backward();
    DRV8833_Timer0_Init();
    g_motor_speed = 100;
    
}

void DRV8833_Task(void)
{
    //DRV8833_1_Forward(); 
    int i = 0;
    // 10级逐级调速
    for (i = 0; i < 10; i++) {
        g_motor_speed += 10;
        if (g_motor_speed >= 100) {
            g_motor_speed = 0;
        }
        DELAY_ms(5000);
    }
    
//        DRV8833_2_Forward();
//        DELAY_ms(2000);
//        DRV8833_2_Backward();
////        DRV8833_1_Stop();
//        DELAY_ms(2000);    
}

//void Timer0_Motor()interrupt 3
void time1()interrupt 3 using 2 // using可以不用
{	
    TH1=(65536-100)/256;	  //100US定时, 0.1ms
    TL1=(65536-100)%256;

    g_count++;        
    if(g_count==100)        
        g_count=0;  
    
    if(g_count > 0 && g_count <= g_motor_speed) {
        // 正转
        DRV8833_1_AIN1 = 1;
        DRV8833_1_BIN1 = 1;
        DRV8833_2_AIN1 = 1;
        DRV8833_2_BIN1 = 1;        
    } else {
        // 正转
        DRV8833_1_AIN1 = 0;
        DRV8833_1_BIN1 = 0;
        DRV8833_2_AIN1 = 0;
        DRV8833_2_BIN1 = 0;              
    }
     
    
}

// 定时器0初始化
void DRV8833_Timer0_Init() 
{
	TMOD=0X10;
	TH1=(65536-100)/256;	  //100US定时
	TL1=(65536-100)%256;
	TR1= 1;
	ET1= 1;
	EA = 1;
}
