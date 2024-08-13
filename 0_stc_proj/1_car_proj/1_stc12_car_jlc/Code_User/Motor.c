#include "Motor.h"


#define LF_A P02//��ǰ���A
#define LF_B P03//��ǰ���B
#define LB_A P01//�����A
#define LB_B P00//�����B

#define RF_A P05//��ǰ���A
#define RF_B P04//��ǰ���B
#define RB_A P06//�Һ���A
#define RB_B P07//�Һ���B

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
* �� �� ��         : Motor_Stop()
* ��������		     : С��ֹͣ����
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
* �� �� ��         : Motor_Forward()
* ��������		     : С��ǰ������
*******************************************************************************/
void Motor_Forward(void)
{ 
    Motor_LF(MOTOR_DIR_F);
    Motor_LB(MOTOR_DIR_F);	

    Motor_RF(MOTOR_DIR_F);
    Motor_RB(MOTOR_DIR_F);    
}

/*******************************************************************************
* �� �� ��         : Motor_Back()
* ��������		     : С�����˺���
*******************************************************************************/
void Motor_Back(void)
{    
    Motor_LF(MOTOR_DIR_B);
    Motor_LB(MOTOR_DIR_B);	

    Motor_RF(MOTOR_DIR_B);
    Motor_RB(MOTOR_DIR_B); 
}

/*******************************************************************************
* �� �� ��         : Motor_Left()
* ��������		     : С����ת����
*******************************************************************************/
void Motor_Left(void)
{
    // ���ֺ���
    Motor_LF(MOTOR_DIR_B);
    Motor_LB(MOTOR_DIR_B);	
    // ����ǰ��
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
* �� �� ��         : Motor_Right()
* ��������		     : С����ת����
*******************************************************************************/
void Motor_Right(void)
{
    // ����ǰ��
    Motor_LF(MOTOR_DIR_F);
    Motor_LB(MOTOR_DIR_F);	
    // ���ֺ���
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
