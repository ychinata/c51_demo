#include <STC12C5A60S2.H>
#ifndef _DRV8833_H
#define _DRV8833_H
#include "Timer01interrupt.h"

int g_count = 0;                            // pwm����
//unsigned int g_motor_speed = 0;          // �����ĸ�����
int g_motor_speedleft = 0;                // ������ǰ/�����ࣩ�������ӵ��ٶ�
int g_motor_speedright = 0;              // ������ǰ/�Һ��Ҳࣩ�������ӵ��ٶ�

int g_motor_clokwiseflag_lf = 1;                       // ��ǰ��
int g_motor_clokwiseflag_lb = 1;                      // �����
int g_motor_clokwiseflag_rf = 1;                     // ��ǰ��
int g_motor_clokwiseflag_rb = 1;                    // �Һ���
                                                            //         
//int g_motor_Inertanceclokwiseflag_lf = 1;         // ��ǰ��
//int g_motor_Inertanceclokwiseflag_lb = 1;        // �����
//int g_motor_Inertanceclokwiseflag_rf = 1;       // ��ǰ��
//int g_motor_Inertanceclokwiseflag_rb = 1;      // �Һ���

 int L1 = 0;
// int L2 = 0;
 int R1 = 0;
// int R2 = 0;
 
// DRV8833 - 51��Ƭ�� 

// ����2�ֻ�4��������������޸�����ӳ��
// #define MOTOR_LF_PIN1 DRV8833_1_AIN1
// #define MOTOR_LF_PIN2 DRV8833_1_AIN2
// #define MOTOR_LB_PIN1 DRV8833_1_BIN1
// #define MOTOR_RF_PIN1 DRV8833_2_AIN1
// #define MOTOR_RB_PIN1 DRV8833_2_BIN1

////����
//sbit DRV8833_1_AIN2 = P2^0; // ʹ������ֻ����ʵ������޸�
//sbit DRV8833_1_AIN1 = P2^1; // ʹ�������       
//sbit DRV8833_1_STBY = P3^3;
//sbit DRV8833_1_BIN1 = P2^3;
//sbit DRV8833_1_BIN2 = P2^2; 

//sbit DRV8833_2_AIN2 = P1^1;
//sbit DRV8833_2_AIN1 = P1^2;         
//sbit DRV8833_2_STBY = P1^3;
//sbit DRV8833_2_BIN1 = P2^2; // ʹ�������
//sbit DRV8833_2_BIN2 = P2^3; // ʹ�������

//����
sbit DRV8833_1_AIN2 = P3^6; // P3.0,P3.1�Ǵ��ڣ�����ʹ��.�˷��˺ܶ�ʱ����Բŷ����������...
sbit DRV8833_1_AIN1 = P3^2;         
sbit DRV8833_1_STBY = P3^3;
sbit DRV8833_1_BIN1 = P3^4;
sbit DRV8833_1_BIN2 = P3^5; 

sbit DRV8833_2_AIN2 = P1^1;
sbit DRV8833_2_AIN1 = P1^2;         
sbit DRV8833_2_STBY = P1^3;
sbit DRV8833_2_BIN1 = P1^4;
sbit DRV8833_2_BIN2 = P1^5;

//�ܶ�
void DRV8833_1_Forward(void)
{
    DRV8833_1_STBY = 1;
    
    DRV8833_1_AIN1 = 1;
    DRV8833_1_AIN2 = 0;
    DRV8833_1_BIN1 = 1;
    DRV8833_1_BIN2 = 0;
    g_motor_clokwiseflag_lf = 1;                //�ж�ǰ�����˵����ж�
    g_motor_clokwiseflag_lb = 1;                //�ж�ǰ�����˵����ж�
//    g_motor_Inertanceclokwiseflag_lf = 2;       //Ϊ2��Ч������������ƶ��ж�
//    g_motor_Inertanceclokwiseflag_lb = 2;       //Ϊ2��Ч������������ƶ��ж�
//    g_motor_Inertanceclokwiseflag_rf = 2;       //Ϊ2��Ч������������ƶ��ж�
//    g_motor_Inertanceclokwiseflag_rb = 2;       //Ϊ2��Ч������������ƶ��ж�
}

void DRV8833_2_Forward(void)
{
    DRV8833_2_STBY = 1;
    
    DRV8833_2_AIN1 = 0;
    DRV8833_2_AIN2 = 1;
    DRV8833_2_BIN1 = 0;
    DRV8833_2_BIN2 = 1;
    g_motor_clokwiseflag_rf = 1;                //�ж�ǰ�����˵����ж�
    g_motor_clokwiseflag_rb = 1;                //�ж�ǰ�����˵����ж�
//    g_motor_Inertanceclokwiseflag_lf = 2;       //Ϊ2��Ч������������ƶ��ж�
//    g_motor_Inertanceclokwiseflag_lb = 2;       //Ϊ2��Ч������������ƶ��ж�
//    g_motor_Inertanceclokwiseflag_rf = 2;       //Ϊ2��Ч������������ƶ��ж�
//    g_motor_Inertanceclokwiseflag_rb = 2;       //Ϊ2��Ч������������ƶ��ж�
}

void DRV8833_1_InertanceForward(void)
{
    DRV8833_1_STBY = 1;
    
    DRV8833_1_AIN1 = 1;
    DRV8833_1_AIN2 = 0;
    DRV8833_1_BIN1 = 1;
    DRV8833_1_BIN2 = 0;  
//    g_motor_Inertanceclokwiseflag_lf = 1;       //�ж�ǰ�����˵����ж�
//    g_motor_Inertanceclokwiseflag_lb = 1;       //�ж�ǰ�����˵����ж�
    g_motor_clokwiseflag_lf = 2;                //Ϊ2��Ч�������������ƶ��ж�
    g_motor_clokwiseflag_lb = 2;                //Ϊ2��Ч�������������ƶ��ж�
    g_motor_clokwiseflag_rf = 2;                //Ϊ2��Ч�������������ƶ��ж�
    g_motor_clokwiseflag_rb = 2;                //Ϊ2��Ч�������������ƶ��ж�
}

void DRV8833_2_InertanceForward(void)
{
    DRV8833_2_STBY = 1;
    
    DRV8833_2_AIN1 = 0;
    DRV8833_2_AIN2 = 1;
    DRV8833_2_BIN1 = 0;
    DRV8833_2_BIN2 = 1;   
//    g_motor_Inertanceclokwiseflag_rf = 1;       //�ж�ǰ�����˵����ж�
//    g_motor_Inertanceclokwiseflag_rb = 1;       //�ж�ǰ�����˵����ж�
    g_motor_clokwiseflag_lf = 2;                //Ϊ2��Ч�������������ƶ��ж�
    g_motor_clokwiseflag_lb = 2;                //Ϊ2��Ч�������������ƶ��ж�
    g_motor_clokwiseflag_rf = 2;                //Ϊ2��Ч�������������ƶ��ж�
    g_motor_clokwiseflag_rb = 2;                //Ϊ2��Ч�������������ƶ��ж�
}

void DRV8833_1_Backward(void)
{
    DRV8833_1_STBY = 1;
    
    DRV8833_1_AIN1 = 0;
    DRV8833_1_AIN2 = 1;
    DRV8833_1_BIN1 = 0;
    DRV8833_1_BIN2 = 1;
    g_motor_clokwiseflag_lf = 0;                //�ж�ǰ�����˵����ж�
    g_motor_clokwiseflag_lb = 0;                //�ж�ǰ�����˵����ж�
//    g_motor_Inertanceclokwiseflag_lf = 2;       //Ϊ2��Ч������������ƶ��ж�
//    g_motor_Inertanceclokwiseflag_lb = 2;       //Ϊ2��Ч������������ƶ��ж�
//    g_motor_Inertanceclokwiseflag_rf = 2;       //Ϊ2��Ч������������ƶ��ж�
//    g_motor_Inertanceclokwiseflag_rb = 2;       //Ϊ2��Ч������������ƶ��ж�
}

void DRV8833_2_Backward(void)
{
    DRV8833_2_STBY = 1;
    
    DRV8833_2_AIN1 = 1;
    DRV8833_2_AIN2 = 0;
    DRV8833_2_BIN1 = 1;
    DRV8833_2_BIN2 = 0;
    g_motor_clokwiseflag_rf = 0;                //�ж�ǰ�����˵����ж�
    g_motor_clokwiseflag_rb = 0;                //�ж�ǰ�����˵����ж�
//    g_motor_Inertanceclokwiseflag_lf = 2;       //Ϊ2��Ч������������ƶ��ж�
//    g_motor_Inertanceclokwiseflag_lb = 2;       //Ϊ2��Ч������������ƶ��ж�
//    g_motor_Inertanceclokwiseflag_rf = 2;       //Ϊ2��Ч������������ƶ��ж�
//    g_motor_Inertanceclokwiseflag_rb = 2;       //Ϊ2��Ч������������ƶ��ж�   
}

void DRV8833_Init(void)
{
    DRV8833_1_Forward();
    DRV8833_2_Forward();
    DRV8833_Timer1_Init();  //100us
//    g_motor_speed = 20;   // �ٶȽ���    
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


//////////////////////////////////////////////////////////////////�жϷ���
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
    
//PWM��ֵ-BGN
//    if(g_count > 0 && g_count <= g_motor_speed)
//        pwm_on_off = 1;     // ����ߵ�ƽ                              
//    else
//        pwm_on_off = 0;     // ����͵�ƽ      
    //                  //                         //    
    if(g_count > 0 && g_count <= g_motor_speedleft)
        pwm_on_off_left = 1;     // ����ߵ�ƽ                              
    else{
        pwm_on_off_left = 0;     // ����͵�ƽ  
        Inertancepwm_on_off_left = 1;       //�����ƶ���ֵ
    }if(g_count > 0 && g_count <= g_motor_speedright)
        pwm_on_off_right = 1;     // ����ߵ�ƽ                              
    else{
        pwm_on_off_right = 0;     // ����͵�ƽ
        Inertancepwm_on_off_right = 1;      //�����ƶ���ֵ
    }    
//pwm��ֵ����
///////////////////////////////////////////����ǰ������ָʾʹ�ø�����ǰ��ת(�����ƶ�00)   
    //��ǰ����ת����ת
    if (g_motor_clokwiseflag_lf == 1) {
        DRV8833_1_AIN1 = pwm_on_off_left;
    } else if(g_motor_clokwiseflag_lf == 0){
        DRV8833_1_AIN2 = pwm_on_off_left;
        DRV8833_1_AIN1 = 0;
    } else {
        //����ִ��
    }        
    //�������ת����ת
    if (g_motor_clokwiseflag_lb == 1) {
        DRV8833_1_BIN1 = pwm_on_off_left;
        DRV8833_1_BIN2 = 0;
    } else if(g_motor_clokwiseflag_lb == 0){
        DRV8833_1_BIN2 = pwm_on_off_left;
        DRV8833_1_BIN1 = 0;
    } else {
        //����ִ��
    } 
    // ��ǰ����ת����ת
    if (g_motor_clokwiseflag_rf == 1) {
        DRV8833_2_AIN2 = pwm_on_off_right;
        DRV8833_2_AIN1 = 0;
    } else if(g_motor_clokwiseflag_rf == 0){
        DRV8833_2_AIN1 = pwm_on_off_right;
        DRV8833_2_AIN2 = 0;
    } else {
        //����ִ��
    } 
    // �Һ�����ת����ת
    if (g_motor_clokwiseflag_rb == 1) {        
        DRV8833_2_BIN2 = pwm_on_off_right;
        DRV8833_2_BIN1 = 0;       
    } else if(g_motor_clokwiseflag_rb == 0){
        DRV8833_2_BIN1 = pwm_on_off_right;
        DRV8833_2_BIN2 = 0;        
    } else {
        //����ִ��
    } 
////////////////////////////////////����ǰ������ָʾʹ�ø�����ǰתû�к�ת(�����ƶ�11)    
    //��ǰ��ǰ���͹����ƶ�
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
//    //�����ǰ���͹����ƶ�
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
//    // ��ǰ��ǰ���͹����ƶ�
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
//    // �Һ���ǰ���͹����ƶ�
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
    
    TH1=(65536-100)/256;	  //100US��ʱ, 0.1ms
    TL1=(65536-100)%256;
}
#endif
