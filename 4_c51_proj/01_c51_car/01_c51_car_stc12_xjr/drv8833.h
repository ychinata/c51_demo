#include <STC12C5A60S2.H>
#ifndef _DRV8833_H
#define _DRV8833_H
#include "Timer01interrupt.h"

int g_count = 0;                            // pwm计数
//unsigned int g_motor_speed = 0;          // 控制四个轮子
int g_motor_speedleft = 0;                // 控制左前/左后（左侧）两个轮子的速度
int g_motor_speedright = 0;              // 控制右前/右后（右侧）两个轮子的速度

int g_motor_clokwiseflag_lf = 1;                       // 左前轮
int g_motor_clokwiseflag_lb = 1;                      // 左后轮
int g_motor_clokwiseflag_rf = 1;                     // 右前轮
int g_motor_clokwiseflag_rb = 1;                    // 右后轮
                                                            //         
//int g_motor_Inertanceclokwiseflag_lf = 1;         // 左前轮
//int g_motor_Inertanceclokwiseflag_lb = 1;        // 左后轮
//int g_motor_Inertanceclokwiseflag_rf = 1;       // 右前轮
//int g_motor_Inertanceclokwiseflag_rb = 1;      // 右后轮

 int L1 = 0;
// int L2 = 0;
 int R1 = 0;
// int R2 = 0;
 
// DRV8833 - 51单片机 

// 根据2轮或4轮驱动，可灵活修改以下映射
// #define MOTOR_LF_PIN1 DRV8833_1_AIN1
// #define MOTOR_LF_PIN2 DRV8833_1_AIN2
// #define MOTOR_LB_PIN1 DRV8833_1_BIN1
// #define MOTOR_RF_PIN1 DRV8833_2_AIN1
// #define MOTOR_RB_PIN1 DRV8833_2_BIN1

////两轮
//sbit DRV8833_1_AIN2 = P2^0; // 使用这个轮或根据实际情况修改
//sbit DRV8833_1_AIN1 = P2^1; // 使用这个轮       
//sbit DRV8833_1_STBY = P3^3;
//sbit DRV8833_1_BIN1 = P2^3;
//sbit DRV8833_1_BIN2 = P2^2; 

//sbit DRV8833_2_AIN2 = P1^1;
//sbit DRV8833_2_AIN1 = P1^2;         
//sbit DRV8833_2_STBY = P1^3;
//sbit DRV8833_2_BIN1 = P2^2; // 使用这个轮
//sbit DRV8833_2_BIN2 = P2^3; // 使用这个轮

//四轮
sbit DRV8833_1_AIN2 = P3^6; // P3.0,P3.1是串口，不可使用.浪费了很多时间调试才发现这个问题...
sbit DRV8833_1_AIN1 = P3^2;         
sbit DRV8833_1_STBY = P3^3;
sbit DRV8833_1_BIN1 = P3^4;
sbit DRV8833_1_BIN2 = P3^5; 

sbit DRV8833_2_AIN2 = P1^1;
sbit DRV8833_2_AIN1 = P1^2;         
sbit DRV8833_2_STBY = P1^3;
sbit DRV8833_2_BIN1 = P1^4;
sbit DRV8833_2_BIN2 = P1^5;

//能动
void DRV8833_1_Forward(void)
{
    DRV8833_1_STBY = 1;
    
    DRV8833_1_AIN1 = 1;
    DRV8833_1_AIN2 = 0;
    DRV8833_1_BIN1 = 1;
    DRV8833_1_BIN2 = 0;
    g_motor_clokwiseflag_lf = 1;                //中断前进后退调速判断
    g_motor_clokwiseflag_lb = 1;                //中断前进后退调速判断
//    g_motor_Inertanceclokwiseflag_lf = 2;       //为2无效，不进入惯性制动判断
//    g_motor_Inertanceclokwiseflag_lb = 2;       //为2无效，不进入惯性制动判断
//    g_motor_Inertanceclokwiseflag_rf = 2;       //为2无效，不进入惯性制动判断
//    g_motor_Inertanceclokwiseflag_rb = 2;       //为2无效，不进入惯性制动判断
}

void DRV8833_2_Forward(void)
{
    DRV8833_2_STBY = 1;
    
    DRV8833_2_AIN1 = 0;
    DRV8833_2_AIN2 = 1;
    DRV8833_2_BIN1 = 0;
    DRV8833_2_BIN2 = 1;
    g_motor_clokwiseflag_rf = 1;                //中断前进后退调速判断
    g_motor_clokwiseflag_rb = 1;                //中断前进后退调速判断
//    g_motor_Inertanceclokwiseflag_lf = 2;       //为2无效，不进入惯性制动判断
//    g_motor_Inertanceclokwiseflag_lb = 2;       //为2无效，不进入惯性制动判断
//    g_motor_Inertanceclokwiseflag_rf = 2;       //为2无效，不进入惯性制动判断
//    g_motor_Inertanceclokwiseflag_rb = 2;       //为2无效，不进入惯性制动判断
}

void DRV8833_1_InertanceForward(void)
{
    DRV8833_1_STBY = 1;
    
    DRV8833_1_AIN1 = 1;
    DRV8833_1_AIN2 = 0;
    DRV8833_1_BIN1 = 1;
    DRV8833_1_BIN2 = 0;  
//    g_motor_Inertanceclokwiseflag_lf = 1;       //中断前进后退调速判断
//    g_motor_Inertanceclokwiseflag_lb = 1;       //中断前进后退调速判断
    g_motor_clokwiseflag_lf = 2;                //为2无效，不进入慢速制动判断
    g_motor_clokwiseflag_lb = 2;                //为2无效，不进入慢速制动判断
    g_motor_clokwiseflag_rf = 2;                //为2无效，不进入慢速制动判断
    g_motor_clokwiseflag_rb = 2;                //为2无效，不进入慢速制动判断
}

void DRV8833_2_InertanceForward(void)
{
    DRV8833_2_STBY = 1;
    
    DRV8833_2_AIN1 = 0;
    DRV8833_2_AIN2 = 1;
    DRV8833_2_BIN1 = 0;
    DRV8833_2_BIN2 = 1;   
//    g_motor_Inertanceclokwiseflag_rf = 1;       //中断前进后退调速判断
//    g_motor_Inertanceclokwiseflag_rb = 1;       //中断前进后退调速判断
    g_motor_clokwiseflag_lf = 2;                //为2无效，不进入慢速制动判断
    g_motor_clokwiseflag_lb = 2;                //为2无效，不进入慢速制动判断
    g_motor_clokwiseflag_rf = 2;                //为2无效，不进入慢速制动判断
    g_motor_clokwiseflag_rb = 2;                //为2无效，不进入慢速制动判断
}

void DRV8833_1_Backward(void)
{
    DRV8833_1_STBY = 1;
    
    DRV8833_1_AIN1 = 0;
    DRV8833_1_AIN2 = 1;
    DRV8833_1_BIN1 = 0;
    DRV8833_1_BIN2 = 1;
    g_motor_clokwiseflag_lf = 0;                //中断前进后退调速判断
    g_motor_clokwiseflag_lb = 0;                //中断前进后退调速判断
//    g_motor_Inertanceclokwiseflag_lf = 2;       //为2无效，不进入惯性制动判断
//    g_motor_Inertanceclokwiseflag_lb = 2;       //为2无效，不进入惯性制动判断
//    g_motor_Inertanceclokwiseflag_rf = 2;       //为2无效，不进入惯性制动判断
//    g_motor_Inertanceclokwiseflag_rb = 2;       //为2无效，不进入惯性制动判断
}

void DRV8833_2_Backward(void)
{
    DRV8833_2_STBY = 1;
    
    DRV8833_2_AIN1 = 1;
    DRV8833_2_AIN2 = 0;
    DRV8833_2_BIN1 = 1;
    DRV8833_2_BIN2 = 0;
    g_motor_clokwiseflag_rf = 0;                //中断前进后退调速判断
    g_motor_clokwiseflag_rb = 0;                //中断前进后退调速判断
//    g_motor_Inertanceclokwiseflag_lf = 2;       //为2无效，不进入惯性制动判断
//    g_motor_Inertanceclokwiseflag_lb = 2;       //为2无效，不进入惯性制动判断
//    g_motor_Inertanceclokwiseflag_rf = 2;       //为2无效，不进入惯性制动判断
//    g_motor_Inertanceclokwiseflag_rb = 2;       //为2无效，不进入惯性制动判断   
}

void DRV8833_Init(void)
{
    DRV8833_1_Forward();
    DRV8833_2_Forward();
    DRV8833_Timer1_Init();  //100us
//    g_motor_speed = 20;   // 速度较慢    
}
void DRV8833_SetSpeedLeft(int speed)
{
    g_motor_speedleft = speed;
}

void DRV8833_SetSpeedRight(int speed)
{
    g_motor_speedright = speed;
}

void DRV8833_SetSpeed(int speed)
{
//    g_motor_speed = speed;
    DRV8833_SetSpeedLeft(speed);
    DRV8833_SetSpeedRight(speed);
}


//////////////////////////////////////////////////////////////////中断服务
void time1()interrupt 3 
{	
//  int pwm_on_off;
    int pwm_on_off_left;
    int pwm_on_off_right;
    int Inertancepwm_on_off_left;
    int Inertancepwm_on_off_right;
    
    g_count++;        
    if(g_count==100)        
        g_count=0;  
    
//PWM赋值-BGN
//    if(g_count > 0 && g_count <= g_motor_speed)
//        pwm_on_off = 1;     // 输出高电平                              
//    else
//        pwm_on_off = 0;     // 输出低电平      
    //                  //                         //    
    if(g_count > 0 && g_count <= g_motor_speedleft)
        pwm_on_off_left = 1;     // 输出高电平                              
    else{
        pwm_on_off_left = 0;     // 输出低电平  
        Inertancepwm_on_off_left = 1;       //惯性制动赋值
    }if(g_count > 0 && g_count <= g_motor_speedright)
        pwm_on_off_right = 1;     // 输出高电平                              
    else{
        pwm_on_off_right = 0;     // 输出低电平
        Inertancepwm_on_off_right = 1;      //惯性制动赋值
    }    
//pwm赋值结束
///////////////////////////////////////////根据前进后退指示使得各个轮前后转(慢速制动00)   
    //左前轮正转否则反转
    if (g_motor_clokwiseflag_lf == 1) {
        DRV8833_1_AIN1 = pwm_on_off_left;
    } else if(g_motor_clokwiseflag_lf == 0){
        DRV8833_1_AIN2 = pwm_on_off_left;
        DRV8833_1_AIN1 = 0;
    } else {
        //无需执行
    }        
    //左后轮正转否则反转
    if (g_motor_clokwiseflag_lb == 1) {
        DRV8833_1_BIN1 = pwm_on_off_left;
        DRV8833_1_BIN2 = 0;
    } else if(g_motor_clokwiseflag_lb == 0){
        DRV8833_1_BIN2 = pwm_on_off_left;
        DRV8833_1_BIN1 = 0;
    } else {
        //无需执行
    } 
    // 右前轮正转否则反转
    if (g_motor_clokwiseflag_rf == 1) {
        DRV8833_2_AIN2 = pwm_on_off_right;
        DRV8833_2_AIN1 = 0;
    } else if(g_motor_clokwiseflag_rf == 0){
        DRV8833_2_AIN1 = pwm_on_off_right;
        DRV8833_2_AIN2 = 0;
    } else {
        //无需执行
    } 
    // 右后轮正转否则反转
    if (g_motor_clokwiseflag_rb == 1) {        
        DRV8833_2_BIN2 = pwm_on_off_right;
        DRV8833_2_BIN1 = 0;       
    } else if(g_motor_clokwiseflag_rb == 0){
        DRV8833_2_BIN1 = pwm_on_off_right;
        DRV8833_2_BIN2 = 0;        
    } else {
        //无需执行
    } 
////////////////////////////////////根据前进后退指示使得各个轮前转没有后转(惯性制动11)    
    //左前轮前进和惯性制动
//    if (g_motor_Inertanceclokwiseflag_lf == 1) {
//        DRV8833_1_AIN1 = pwm_on_off_left;
//        DRV8833_1_AIN2 = 0;
//        if (g_count > g_motor_speedleft) {
//            DRV8833_1_AIN2 = Inertancepwm_on_off_left;
//            DRV8833_1_AIN1 = Inertancepwm_on_off_left;
//        }            
//    } else if (g_motor_Inertanceclokwiseflag_lf == 0){
////        DRV8833_1_AIN2 = pwm_on_off_left;
////        DRV8833_1_AIN1 = 0;
//    }    
//    //左后轮前进和惯性制动
//    if (g_motor_Inertanceclokwiseflag_lb == 1) {
//        DRV8833_1_BIN1 = pwm_on_off_left;
//        DRV8833_1_BIN2 = 0;
//        if(g_count > g_motor_speedleft) {
//            DRV8833_1_BIN2 = Inertancepwm_on_off_left;
//            DRV8833_1_BIN1 = Inertancepwm_on_off_left;
//        }
//    } else if (g_motor_Inertanceclokwiseflag_lb == 0){
////        DRV8833_1_BIN2 = pwm_on_off_left;
////        DRV8833_1_BIN1 = 0;
//    }
//    // 右前轮前进和惯性制动
//    if (g_motor_Inertanceclokwiseflag_rf == 1) {
//        DRV8833_2_AIN2 = pwm_on_off_right;
//        DRV8833_2_AIN1 = 0;
//        if(g_count > g_motor_speedright) {
//            DRV8833_2_AIN1 = Inertancepwm_on_off_right;
//            DRV8833_2_AIN2 = Inertancepwm_on_off_right;
//        }
//    } else if (g_motor_Inertanceclokwiseflag_rf == 0){
////        DRV8833_2_AIN1 = pwm_on_off_right;
////        DRV8833_2_AIN2 = 0;
//    }
//    // 右后轮前进和惯性制动
//    if (g_motor_Inertanceclokwiseflag_rb == 1) {        
//        DRV8833_2_BIN2 = pwm_on_off_right;
//        DRV8833_2_BIN1 = 0;
//        if(g_count > g_motor_speedright) {
//            DRV8833_2_BIN1 = Inertancepwm_on_off_right;
//            DRV8833_2_BIN2 = Inertancepwm_on_off_right;
//        }            
//    } else if (g_motor_Inertanceclokwiseflag_rb == 0){
////        DRV8833_2_BIN1 = pwm_on_off_right;
////        DRV8833_2_BIN2 = 0;        
//    }
    
    TH1=(65536-100)/256;	  //100US定时, 0.1ms
    TL1=(65536-100)%256;
}
#endif
