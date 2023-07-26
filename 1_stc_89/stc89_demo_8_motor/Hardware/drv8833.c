//2023.6.24
#include <REGX52.H>
//#include <STC12C5A.H>
#include "delay.h"
#include "drv8833.h"
#include "oled.h"

unsigned int g_count = 0;
unsigned int g_motor_speed = 0;     //控制四个轮子
unsigned int g_motor_speedleft = 0; //控制左前/左后两个轮子的速度
unsigned int g_motor_speedright = 0;//控制右前/右后两个轮子的速度


// 轮子方向，向前为1，向后为0
unsigned int g_motor_clokwiseflag_lf = 1;   // 左前轮
unsigned int g_motor_clokwiseflag_lb = 1;   // 左后轮
unsigned int g_motor_clokwiseflag_rf = 1;   // 右前轮
unsigned int g_motor_clokwiseflag_rb = 1;   // 右后轮

//speed为5走不动,10很慢,50挺快了
void DRV8833_SetSpeed(unsigned int speed)
{
    g_motor_speed = speed;
    DRV8833_SetSpeedLeft(speed);
    DRV8833_SetSpeedRight(speed);
}

void DRV8833_SetSpeedLeft(unsigned int speed)
{
    g_motor_speedleft = speed;
}

void DRV8833_SetSpeedRight(unsigned int speed)
{
    g_motor_speedright = speed;
}

// DRV8833_1控制左侧轮子
void DRV8833_1_Forward(void)
{
    DRV8833_1_STBY = 1;
    
    DRV8833_1_AIN1 = 1;
    DRV8833_1_AIN2 = 0;
    DRV8833_1_BIN1 = 1;
    DRV8833_1_BIN2 = 0;   
    g_motor_clokwiseflag_lf = 1;
    g_motor_clokwiseflag_lb = 1;
}

void DRV8833_1_Backward(void)
{
    DRV8833_1_STBY = 1;   
    
    DRV8833_1_AIN1 = 0;
    DRV8833_1_AIN2 = 1;
    DRV8833_1_BIN1 = 0;
    DRV8833_1_BIN2 = 1;   
    g_motor_clokwiseflag_lf = 0;
    g_motor_clokwiseflag_lb = 0;    
}

void DRV8833_1_Stop(void)
{
    DRV8833_1_STBY = 0;
}

// DRV8833_2控制右侧轮子，方向要跟左侧相反
void DRV8833_2_Forward(void)
{
    DRV8833_2_STBY = 1;
    
    DRV8833_2_AIN1 = 0;
    DRV8833_2_AIN2 = 1;
    DRV8833_2_BIN1 = 0;
    DRV8833_2_BIN2 = 1;   
    g_motor_clokwiseflag_rf = 1;
    g_motor_clokwiseflag_rb = 1;    
}

void DRV8833_2_Backward(void)
{
    DRV8833_2_STBY = 1;   
    
    DRV8833_2_AIN1 = 1;
    DRV8833_2_AIN2 = 0;
    DRV8833_2_BIN1 = 1;
    DRV8833_2_BIN2 = 0;   
    g_motor_clokwiseflag_rf = 0;
    g_motor_clokwiseflag_rb = 0;      
}

void DRV8833_2_Stop(void)
{
    DRV8833_2_STBY = 0;
}

#if 1 // 单轮控制-bgn

void DRV8833_LF_Forward(void)
{
    DRV8833_1_AIN1 = 1;
    DRV8833_1_AIN2 = 0;
    g_motor_clokwiseflag_lf = 1; 
}

void DRV8833_LF_Backward(void)
{    
    DRV8833_1_AIN1 = 0;
    DRV8833_1_AIN2 = 1;
    g_motor_clokwiseflag_lf = 0;
}

void DRV8833_LF_Stop(void)
{    
    DRV8833_1_AIN1 = 0;
    DRV8833_1_AIN2 = 0;
    //g_motor_clokwiseflag_lf = 0;
}

void DRV8833_LB_Forward(void)
{
    DRV8833_1_BIN1 = 1;
    DRV8833_1_BIN2 = 0;   
    g_motor_clokwiseflag_lb = 1;    
}

void DRV8833_LB_Backward(void)
{    
    DRV8833_1_BIN1 = 0;
    DRV8833_1_BIN2 = 1;   
    g_motor_clokwiseflag_lb = 0;    
}

void DRV8833_LB_Stop(void)
{    
    DRV8833_1_BIN1 = 1;
    DRV8833_1_BIN2 = 1;   
    //g_motor_clokwiseflag_lb = 0;    
}

void DRV8833_RF_Forward(void)
{    
    DRV8833_2_AIN1 = 0;
    DRV8833_2_AIN2 = 1;
    g_motor_clokwiseflag_rf = 1;
}

void DRV8833_RF_Backward(void)
{    
    DRV8833_2_AIN1 = 1;
    DRV8833_2_AIN2 = 0;
    g_motor_clokwiseflag_rf = 0;
}

void DRV8833_RF_Stop(void)
{    
    DRV8833_2_AIN1 = 1;
    DRV8833_2_AIN2 = 1;
    //g_motor_clokwiseflag_rf = 0;
}

void DRV8833_RB_Forward(void)
{    
    DRV8833_2_BIN1 = 0;
    DRV8833_2_BIN2 = 1;   
    g_motor_clokwiseflag_rb = 1;    
}

void DRV8833_RB_Backward(void)
{    
    DRV8833_2_BIN1 = 1;
    DRV8833_2_BIN2 = 0;   
    g_motor_clokwiseflag_rb = 0;      
}

void DRV8833_RB_Stop(void)
{    
    DRV8833_2_BIN1 = 1;
    DRV8833_2_BIN2 = 1;   
    //g_motor_clokwiseflag_rb = 0;      
}

#endif // 单轮控制-end

void DRV8833_Init(void)
{
    DRV8833_1_Forward();
    DRV8833_2_Forward();
    //DRV8833_2_Backward();
    DRV8833_Timer0_Init();
    g_motor_speed = 20;     // 速度较慢
    //开启电机驱动使能
    DRV8833_1_STBY = 1; 
    DRV8833_2_STBY = 1; 
    
}

//DRV8833_Task

// 10级逐级调速
void DRV8833_Task_ErgodicVelocity(void)
{
    //DRV8833_1_Forward(); 
    int i = 0;
    int gear = 0;
    // 10级逐级调速
    for (i = 0; i < 10; i++) {
        g_motor_speed += 10;
        if (g_motor_speed >= 100) {
            g_motor_speed = 0;
        }
        gear = g_motor_speed / 10;
        //显示档位
        OLED_ShowNum(50,3,gear,2,16);
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
    int pwm_on_off;
    int pwm_on_off_left;
    int pwm_on_off_right;
    TH1=(65536-100)/256;	  //100US定时, 0.1ms
    TL1=(65536-100)%256;

    g_count++;        
    if(g_count==100)        
        g_count=0;  
    
    // PWM赋值-BGN
    if(g_count > 0 && g_count <= g_motor_speed)
        pwm_on_off = 1;     // 输出高电平                              
    else
        pwm_on_off = 0;     // 输出低电平      
    
    if(g_count > 0 && g_count <= g_motor_speedleft)
        pwm_on_off_left = 1;     // 输出高电平                              
    else
        pwm_on_off_left = 0;     // 输出低电平  
    
    if(g_count > 0 && g_count <= g_motor_speedright)
        pwm_on_off_right = 1;     // 输出高电平                              
    else
        pwm_on_off_right = 0;     // 输出低电平  
    // PWM赋值-END    

    // 左前轮正转
    if (g_motor_clokwiseflag_lf == 1) {
        DRV8833_1_AIN1 = pwm_on_off_left;
    } else {
        DRV8833_1_AIN2 = pwm_on_off_left;
    }
    // 左后轮转
    if (g_motor_clokwiseflag_lb == 1) {
        DRV8833_1_BIN1 = pwm_on_off_left;
    } else {
        DRV8833_1_BIN2 = pwm_on_off_left;
    }
    // 右前轮正转(跟左轮相反)
    if (g_motor_clokwiseflag_rf == 1) {
        DRV8833_2_AIN2 = pwm_on_off_right;
    } else {
        DRV8833_2_AIN1 = pwm_on_off_right;
    }
    // 右前轮正转(跟左轮相反)
    if (g_motor_clokwiseflag_rb == 1) {        
        DRV8833_2_BIN2 = pwm_on_off_right; 
    } else {
        DRV8833_2_BIN1 = pwm_on_off_right;   
    } 
}

// 定时器0初始化 //100US定时
void DRV8833_Timer0_Init() 
{
	TMOD=0X10;              //设置定时器模式
	TH1=(65536-100)/256;	//设置定时初值 
	TL1=(65536-100)%256;    //设置定时初值
	TR1= 1;
	ET1= 1;
	EA = 1;
}

//供参考
//void Timer0_Init(void)
//{
//	TMOD &= 0xF0;		//设置定时器模式
//	TMOD |= 0x01;		//设置定时器模式
//	TL0 = 0x9C;		//设置定时初值
//	TH0 = 0xFF;		//设置定时初值
//	TF0 = 0;		//清除TF0标志
//	TR0 = 1;		//定时器0开始计时
//	ET0=1;
//	EA=1;
//	PT0=0;
//}
/*定时器中断函数模板
void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x9C;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	T0Count++;
	if(T0Count>=1000)
	{
		T0Count=0;
		
	}
}
*/
