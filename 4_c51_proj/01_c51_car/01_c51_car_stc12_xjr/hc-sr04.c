#include <STC12C5A60S2.H>
#include "HC-SR04.H"
//#include "delay.h"

double Distance_HC_SR04(void){
    uint8 i;
    uint32 time_sum=0;
//    uint8  j;
//    uint16 time;              //时间变量
    uint16 time_sum_av;
    uint16 time_ALL[10];
    for(i=0;i<=0;i++){
        TMOD=0x11;    //调用定时器0//会不会跟T1冲突？？？？？？？？？？？？
        TH0=0;        
        TL0=0;        
        TR0=0;

        //LCD_Check_Busy(); 
    
        Trig=1;
        //delay(2);
        Trig=0;//20us延时，开始工作
    
        while(!Echo);//高电平开启定时器
        TR0=1;
        while(Echo);//低电平关闭定时器      
        TR0=0;
    
        time_ALL[i]=TH0*256+TL0;//读取数值
//        delay_1ms(80);  
    }
//    for(i=0;i<9;i++){//冒泡升序
//        for(j=i+1;j<10;j++){
//            if(time_ALL[i]>time_ALL[j]){
//                time=time_ALL[i];
//                time_ALL[i]=time_ALL[j];
//                time_ALL[j]=time;
//            }        
//        }
//    }
    for(i=0;i<1;i++){time_sum+=time_ALL[i];}
    time_sum_av=(time_sum/1);//计算时间平均值
    
//    for(i=0;i<10;i++){time_sum+=time_10[i];}
//    time_sum_av=(time_sum/10);//计算时间平均值
    
    
    return (time_sum_av*0.00034/2)*100;//计算距离转换单位0.00034m/us 乘以100为cm
}


void HC_SR04_Init()
{
    Trig=0;
    Echo=1;
}
