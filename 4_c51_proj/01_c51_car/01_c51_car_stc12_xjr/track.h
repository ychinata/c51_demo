#ifndef __TRACK_H
#define __TRACK_H
#include "drv8833.h"

///////////////////////////////���С��״̬///////////////////////////////////////////
int TRACK_GetStatus3WAY(void)
{
    //0b x    x    x
    //  ��· ��· ��·
    //��·�з��䣬״̬Ϊ7����·�޷��䣬״̬Ϊ0
    int trackStatus;
    //trackStatus = (TRACK_PIN_R << 2 ) | (TRACK_PIN_C << 1) | (TRACK_PIN_L << 0);
    
    trackStatus = (P4 & 0x07);
    //OLED_ShowNum(0,6,trackStatus,2,16);//��ʾ��LCD�Ϸ������ߵ���
    return trackStatus;
}
///////////////////////////////���С��״̬///////////////////////////////////////////

///////////////////////////////��С������ָʾ/////////////////////////////////////////
//////////////////////////////////ǰ������////////////////////////////////////////////
void CAR_Forward(int speed)
{
    DRV8833_SetSpeed(speed);
    DRV8833_2_Forward();
    DRV8833_1_Forward();
}

void CAR_Backward(int speed)
{
    DRV8833_SetSpeed(speed);
    DRV8833_2_Backward();
    DRV8833_1_Backward();
}
//////////////////////////////////ǰ������////////////////////////////////////////////

///////////////////////////////////����ת/////////////////////////////////////////////
void CAR_TurnRight(int speed)
{
    //����ת�����ֿ죬������
    DRV8833_2_Forward();
    DRV8833_1_Forward();
    DRV8833_SetSpeedLeft(speed);
    DRV8833_SetSpeedRight(speed-speed/3);///////////////////////////////note������
//    DRV8833_LF_Forward(); 
//    DRV8833_RF_Forward();
//    DRV8833_LB_Forward();
//    DRV8833_RB_Forward();     
}

void CAR_TurnLeft(int speed)
{
    //����ת�������������ֿ�
    DRV8833_2_Forward();
    DRV8833_1_Forward();
    DRV8833_SetSpeedRight(speed);
    DRV8833_SetSpeedLeft(speed-speed/3);///////////////////////////////note������
//    DRV8833_LF_Forward(); 
//    DRV8833_RF_Forward();
//    DRV8833_LB_Forward();
//    DRV8833_RB_Forward();     
}
///////////////////////////////////����ת/////////////////////////////////////////////

/////////////////////////////////ԭ������ת///////////////////////////////////////////
void CAR_LeftTurn(int speed)
{
    DRV8833_2_Forward();
    DRV8833_1_Backward();
    DRV8833_SetSpeedLeft(speed-speed/3);///////////////////////////////note������
    DRV8833_SetSpeedRight(speed);
}

void CAR_RightTurn(int speed)
{
    DRV8833_1_Forward();
    DRV8833_2_Backward();
    DRV8833_SetSpeedLeft(speed);
    DRV8833_SetSpeedRight(speed-speed/3);//////////////////////////////note������
}
/////////////////////////////////ԭ������ת///////////////////////////////////////////

////////////////////////////////////ֹͣ//////////////////////////////////////////////
void CAR_Stop()
{
    DRV8833_SetSpeed(0);
}

void CAR_InertanceStop(int speed)
{
    DRV8833_1_InertanceForward();
    DRV8833_2_InertanceForward();
    DRV8833_SetSpeedLeft(speed);
    DRV8833_SetSpeedRight(speed);
}
////////////////////////////////////ֹͣ//////////////////////////////////////////////
///////////////////////////////��С������ָʾ/////////////////////////////////////////


///////////////////���ۺ������������������С��״̬������ָʾ/////////////////////////
void CAR_TrackTask(void)
{   
    int trackStatus;
    trackStatus = TRACK_GetStatus3WAY();
///////////////////////////////////////////////////////////////////////��ʻָ��
    
      if (trackStatus == 0x00) {            // ���ߣ�->->->+++�һ���
          CAR_Forward(25); 
//          if (R1==1) {       //��һ״̬R1
//            CAR_RightTurn(45);
//    } else if (L1==1) {  //��һ״̬L1
//            CAR_LeftTurn(40);
//    } else {//��ʱ���߻�ֱ�ߣ�������ֱ�߳��ߣ�ת��״̬δ��¼���������Ժ���
//            CAR_Forward(26);   
//    }
    } else if (trackStatus == 0x01) {       // ����ƫ->->++��ת
        CAR_TurnRight(35);
        R1=1;L1=0;
           
    } else if (trackStatus == 0x02) {       // �����ߣ�ֱ��
        CAR_Forward(40);

    } else if (trackStatus == 0x03) {       // ��ƫ->+��ת
        CAR_TurnRight(30);
        
    } else if (trackStatus == 0x04) {       // ����ƫ->->++��ת
        CAR_TurnLeft(35);
        L1=1;R1=0;
        
    } else if (trackStatus == 0x05) {       // �������������֣���ʵ�ʻ���֣�����ڣ�
        CAR_Forward(20);
        
    } else if (trackStatus == 0x06) {       // ��ƫ->+��ת
        CAR_TurnLeft(35);
        
    } else if (trackStatus == 0x07) {       // ʮ��/���գ�ֹͣ
        CAR_Stop();

    }
    
}
///////////////////���ۺ������������������С��״̬������ָʾ////////////////////////////

#endif