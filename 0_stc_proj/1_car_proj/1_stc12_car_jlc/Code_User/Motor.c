#include "Motor.h"


#define LF_A P02//左前电机A
#define LF_B P03//左前电机B
#define LB_A P01//左后电机A
#define LB_B P00//左后电机B

#define RF_A P05//右前电机A
#define RF_B P04//右前电机B
#define RB_A P06//右后电机A
#define RB_B P07//右后电机B

#define MOTOR_DIR_F 0
#define MOTOR_DIR_B 1

void Motor_LF(unsigned char dir) {
    if (dir == MOTOR_DIR_F) {
        LF_A=1;   
        LF_B=0;	        
    } else {    
        LF_A=0;   
        LF_B=1;	       
    }
}

void Motor_LB(unsigned char dir) {
    if (dir == MOTOR_DIR_F) {
        LB_A=0;	 
        LB_B=1;	             
    } else {    
        LB_A=1;	 
        LB_B=0;	 
    }
}

void Motor_RF(unsigned char dir) {
    if (dir == MOTOR_DIR_F) {
        RF_A=1;   
        RF_B=0;	        
    } else {    
        RF_A=0;   
        RF_B=1;	       
    }
}

void Motor_RB(unsigned char dir) {
    if (dir == MOTOR_DIR_F) {
        RB_A=1;   
        RB_B=0;	        
    } else {    
        RB_A=0;	 
        RB_B=1;	        
    }
}

/*******************************************************************************
* 函 数 名         : Motor_Stop()
* 函数功能		     : 小车停止函数
*******************************************************************************/
void Motor_Stop(void)
{
	 LF_A=0;  
	 LF_B=0;	 
	 LB_A=0;	 
	 LB_B=0;	 
	 RF_A=0;   
	 RF_B=0;	 
	 RB_A=0;	 
	 RB_B=0;	 
}

/*******************************************************************************
* 函 数 名         : Motor_Forward()
* 函数功能		     : 小车前进函数
*******************************************************************************/
void Motor_Forward(void)
{ 
    Motor_LF(MOTOR_DIR_F);
    Motor_LB(MOTOR_DIR_F);	

    Motor_RF(MOTOR_DIR_F);
    Motor_RB(MOTOR_DIR_F);    
}

/*******************************************************************************
* 函 数 名         : Motor_Back()
* 函数功能		     : 小车后退函数
*******************************************************************************/
void Motor_Back(void)
{    
    Motor_LF(MOTOR_DIR_B);
    Motor_LB(MOTOR_DIR_B);	

    Motor_RF(MOTOR_DIR_B);
    Motor_RB(MOTOR_DIR_B); 
}

/*******************************************************************************
* 函 数 名         : Motor_Left()
* 函数功能		     : 小车左转函数
*******************************************************************************/
void Motor_Left(void)
{
    // 左轮后退
    Motor_LF(MOTOR_DIR_B);
    Motor_LB(MOTOR_DIR_B);	
    // 右轮前进
    Motor_RF(MOTOR_DIR_F);
    Motor_RB(MOTOR_DIR_F);     
//	 LF_A=0;  
//	 LF_B=1;	 
//    
//	 LB_A=0;	 
//	 LB_B=1;
//	
//	 RF_A=1;   
//	 RF_B=0;	
//    
//	 RB_A=1;	 
//	 RB_B=0;	 
}

/*******************************************************************************
* 函 数 名         : Motor_Right()
* 函数功能		     : 小车右转函数
*******************************************************************************/
void Motor_Right(void)
{
    // 左轮前进
    Motor_LF(MOTOR_DIR_F);
    Motor_LB(MOTOR_DIR_F);	
    // 右轮后退
    Motor_RF(MOTOR_DIR_B);
    Motor_RB(MOTOR_DIR_B);       
//	 LF_A=1;  
//	 LF_B=0;
//    
//	 LB_A=1;	 
//	 LB_B=0;
//	
//	 RF_A=0;   
//	 RF_B=1;	    
//	 RB_A=0;	 
//	 RB_B=1;	 
}
