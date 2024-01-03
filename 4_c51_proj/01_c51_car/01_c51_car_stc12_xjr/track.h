#ifndef __TRACK_H
#define __TRACK_H
#include "drv8833.h"

///////////////////////////////获得小车状态///////////////////////////////////////////
int TRACK_GetStatus3WAY(void)
{
    //0b x    x    x
    //  左路 中路 右路
    //三路有反射，状态为7；三路无反射，状态为0
    int trackStatus;
    //trackStatus = (TRACK_PIN_R << 2 ) | (TRACK_PIN_C << 1) | (TRACK_PIN_L << 0);
    
    trackStatus = (P4 & 0x07);
    //OLED_ShowNum(0,6,trackStatus,2,16);//显示在LCD上方便离线调试
    return trackStatus;
}
///////////////////////////////获得小车状态///////////////////////////////////////////

///////////////////////////////对小车进行指示/////////////////////////////////////////
//////////////////////////////////前进后退////////////////////////////////////////////
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
//////////////////////////////////前进后退////////////////////////////////////////////

///////////////////////////////////左右转/////////////////////////////////////////////
void CAR_TurnRight(int speed)
{
    //车右转：左轮快，右轮慢
    DRV8833_2_Forward();
    DRV8833_1_Forward();
    DRV8833_SetSpeedLeft(speed);
    DRV8833_SetSpeedRight(speed-speed/3);///////////////////////////////note！！！
//    DRV8833_LF_Forward(); 
//    DRV8833_RF_Forward();
//    DRV8833_LB_Forward();
//    DRV8833_RB_Forward();     
}

void CAR_TurnLeft(int speed)
{
    //车左转：左轮慢，右轮快
    DRV8833_2_Forward();
    DRV8833_1_Forward();
    DRV8833_SetSpeedRight(speed);
    DRV8833_SetSpeedLeft(speed-speed/3);///////////////////////////////note！！！
//    DRV8833_LF_Forward(); 
//    DRV8833_RF_Forward();
//    DRV8833_LB_Forward();
//    DRV8833_RB_Forward();     
}
///////////////////////////////////左右转/////////////////////////////////////////////

/////////////////////////////////原地左右转///////////////////////////////////////////
void CAR_LeftTurn(int speed)
{
    DRV8833_2_Forward();
    DRV8833_1_Backward();
    DRV8833_SetSpeedLeft(speed-speed/3);///////////////////////////////note！！！
    DRV8833_SetSpeedRight(speed);
}

void CAR_RightTurn(int speed)
{
    DRV8833_1_Forward();
    DRV8833_2_Backward();
    DRV8833_SetSpeedLeft(speed);
    DRV8833_SetSpeedRight(speed-speed/3);//////////////////////////////note！！！
}
/////////////////////////////////原地左右转///////////////////////////////////////////

////////////////////////////////////停止//////////////////////////////////////////////
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
////////////////////////////////////停止//////////////////////////////////////////////
///////////////////////////////对小车进行指示/////////////////////////////////////////


///////////////////（综合以上两个函数）获得小车状态并进行指示/////////////////////////
void CAR_TrackTask(void)
{   
    int trackStatus;
    trackStatus = TRACK_GetStatus3WAY();
///////////////////////////////////////////////////////////////////////行驶指令
    
      if (trackStatus == 0x00) {            // 出线，->->->+++右或左
          CAR_Forward(25); 
//          if (R1==1) {       //上一状态R1
//            CAR_RightTurn(45);
//    } else if (L1==1) {  //上一状态L1
//            CAR_LeftTurn(40);
//    } else {//有时出线会直走，条件：直线出线，转弯状态未记录。基本可以忽略
//            CAR_Forward(26);   
//    }
    } else if (trackStatus == 0x01) {       // 重左偏->->++右转
        CAR_TurnRight(35);
        R1=1;L1=0;
           
    } else if (trackStatus == 0x02) {       // 在中线，直行
        CAR_Forward(40);

    } else if (trackStatus == 0x03) {       // 左偏->+右转
        CAR_TurnRight(30);
        
    } else if (trackStatus == 0x04) {       // 重右偏->->++左转
        CAR_TurnLeft(35);
        L1=1;R1=0;
        
    } else if (trackStatus == 0x05) {       // 正常情况不会出现，但实际会出现（交叉口）
        CAR_Forward(20);
        
    } else if (trackStatus == 0x06) {       // 右偏->+左转
        CAR_TurnLeft(35);
        
    } else if (trackStatus == 0x07) {       // 十字/悬空，停止
        CAR_Stop();

    }
    
}
///////////////////（综合以上两个函数）获得小车状态并进行指示////////////////////////////

#endif