#include <STC12C5A60S2.H>
#include "HC-SR04.H"
//#include "delay.h"

double Distance_HC_SR04(void){
    uint8 i;
    uint32 time_sum=0;
//    uint8  j;
//    uint16 time;              //ʱ�����
    uint16 time_sum_av;
    uint16 time_ALL[10];
    for(i=0;i<=0;i++){
        TMOD=0x11;    //���ö�ʱ��0//�᲻���T1��ͻ������������������������
        TH0=0;        
        TL0=0;        
        TR0=0;

        //LCD_Check_Busy(); 
    
        Trig=1;
        //delay(2);
        Trig=0;//20us��ʱ����ʼ����
    
        while(!Echo);//�ߵ�ƽ������ʱ��
        TR0=1;
        while(Echo);//�͵�ƽ�رն�ʱ��      
        TR0=0;
    
        time_ALL[i]=TH0*256+TL0;//��ȡ��ֵ
//        delay_1ms(80);  
    }
//    for(i=0;i<9;i++){//ð������
//        for(j=i+1;j<10;j++){
//            if(time_ALL[i]>time_ALL[j]){
//                time=time_ALL[i];
//                time_ALL[i]=time_ALL[j];
//                time_ALL[j]=time;
//            }        
//        }
//    }
    for(i=0;i<1;i++){time_sum+=time_ALL[i];}
    time_sum_av=(time_sum/1);//����ʱ��ƽ��ֵ
    
//    for(i=0;i<10;i++){time_sum+=time_10[i];}
//    time_sum_av=(time_sum/10);//����ʱ��ƽ��ֵ
    
    
    return (time_sum_av*0.00034/2)*100;//�������ת����λ0.00034m/us ����100Ϊcm
}


void HC_SR04_Init()
{
    Trig=0;
    Echo=1;
}
