//2023.6.24
#include <REGX52.H>
//#include <STC12C5A.H>
#include "delay.h"
#include "drv8833.h"
#include "oled.h"

unsigned int g_count = 0;
unsigned int g_motor_speed = 0;     //�����ĸ�����
unsigned int g_motor_speedleft = 0; //������ǰ/����������ӵ��ٶ�
unsigned int g_motor_speedright = 0;//������ǰ/�Һ��������ӵ��ٶ�


// ���ӷ�����ǰΪ1�����Ϊ0
unsigned int g_motor_clokwiseflag_lf = 1;   // ��ǰ��
unsigned int g_motor_clokwiseflag_lb = 1;   // �����
unsigned int g_motor_clokwiseflag_rf = 1;   // ��ǰ��
unsigned int g_motor_clokwiseflag_rb = 1;   // �Һ���

//speedΪ5�߲���,10����,50ͦ����
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

// DRV8833_1�����������
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

// DRV8833_2�����Ҳ����ӣ�����Ҫ������෴
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

#if 1 // ���ֿ���-bgn

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

#endif // ���ֿ���-end

void DRV8833_Init(void)
{
    DRV8833_1_Forward();
    DRV8833_2_Forward();
    //DRV8833_2_Backward();
    DRV8833_Timer0_Init();
    g_motor_speed = 20;     // �ٶȽ���
    //�����������ʹ��
    DRV8833_1_STBY = 1; 
    DRV8833_2_STBY = 1; 
    
}

//DRV8833_Task

// 10���𼶵���
void DRV8833_Task_ErgodicVelocity(void)
{
    //DRV8833_1_Forward(); 
    int i = 0;
    int gear = 0;
    // 10���𼶵���
    for (i = 0; i < 10; i++) {
        g_motor_speed += 10;
        if (g_motor_speed >= 100) {
            g_motor_speed = 0;
        }
        gear = g_motor_speed / 10;
        //��ʾ��λ
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
void time1()interrupt 3 using 2 // using���Բ���
{	
    int pwm_on_off;
    int pwm_on_off_left;
    int pwm_on_off_right;
    TH1=(65536-100)/256;	  //100US��ʱ, 0.1ms
    TL1=(65536-100)%256;

    g_count++;        
    if(g_count==100)        
        g_count=0;  
    
    // PWM��ֵ-BGN
    if(g_count > 0 && g_count <= g_motor_speed)
        pwm_on_off = 1;     // ����ߵ�ƽ                              
    else
        pwm_on_off = 0;     // ����͵�ƽ      
    
    if(g_count > 0 && g_count <= g_motor_speedleft)
        pwm_on_off_left = 1;     // ����ߵ�ƽ                              
    else
        pwm_on_off_left = 0;     // ����͵�ƽ  
    
    if(g_count > 0 && g_count <= g_motor_speedright)
        pwm_on_off_right = 1;     // ����ߵ�ƽ                              
    else
        pwm_on_off_right = 0;     // ����͵�ƽ  
    // PWM��ֵ-END    

    // ��ǰ����ת
    if (g_motor_clokwiseflag_lf == 1) {
        DRV8833_1_AIN1 = pwm_on_off_left;
    } else {
        DRV8833_1_AIN2 = pwm_on_off_left;
    }
    // �����ת
    if (g_motor_clokwiseflag_lb == 1) {
        DRV8833_1_BIN1 = pwm_on_off_left;
    } else {
        DRV8833_1_BIN2 = pwm_on_off_left;
    }
    // ��ǰ����ת(�������෴)
    if (g_motor_clokwiseflag_rf == 1) {
        DRV8833_2_AIN2 = pwm_on_off_right;
    } else {
        DRV8833_2_AIN1 = pwm_on_off_right;
    }
    // ��ǰ����ת(�������෴)
    if (g_motor_clokwiseflag_rb == 1) {        
        DRV8833_2_BIN2 = pwm_on_off_right; 
    } else {
        DRV8833_2_BIN1 = pwm_on_off_right;   
    } 
}

// ��ʱ��0��ʼ�� //100US��ʱ
void DRV8833_Timer0_Init() 
{
	TMOD=0X10;              //���ö�ʱ��ģʽ
	TH1=(65536-100)/256;	//���ö�ʱ��ֵ 
	TL1=(65536-100)%256;    //���ö�ʱ��ֵ
	TR1= 1;
	ET1= 1;
	EA = 1;
}

//���ο�
//void Timer0_Init(void)
//{
//	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
//	TMOD |= 0x01;		//���ö�ʱ��ģʽ
//	TL0 = 0x9C;		//���ö�ʱ��ֵ
//	TH0 = 0xFF;		//���ö�ʱ��ֵ
//	TF0 = 0;		//���TF0��־
//	TR0 = 1;		//��ʱ��0��ʼ��ʱ
//	ET0=1;
//	EA=1;
//	PT0=0;
//}
/*��ʱ���жϺ���ģ��
void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x9C;		//���ö�ʱ��ֵ
	TH0 = 0xFF;		//���ö�ʱ��ֵ
	T0Count++;
	if(T0Count>=1000)
	{
		T0Count=0;
		
	}
}
*/
