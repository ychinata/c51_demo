#include "delay.h"
#include "track.h"
#include "LCD.H"
#include "HC-SR04.H"

uint16 S;                //�������

void main(void)
{
    uchar8 dis_S[6];
    uchar8 Distance_show[]="Distance:";
    uchar8 Distance_Num_show[]="cm"; 
    char code Data_1[]={0x04, 0x1f, 0x15, 0x1f, 0x15, 0x1f, 0x05, 0x07};  //��
    char code Data_2[]={0x1f, 0x02, 0x04, 0x1f, 0x04, 0x14, 0x0c, 0x04};  //��
    char code Data_3[]={0x04, 0x07, 0x0f, 0x02, 0x0f, 0x02, 0x03, 0x02};  //��
    char code Data_4[]={0x04, 0x04, 0x1f, 0x15, 0x1f, 0x04, 0x04, 0x04};  // 
    char code Data_5[]={0x00, 0x1f, 0x04, 0x04, 0x04, 0x04, 0x1f, 0x00};  //�� 
    char code Data_6[]={0x14, 0x1e, 0x14, 0x1f, 0x04, 0x1f, 0x15, 0x15};  //�� 
    char code Data_7[]={0x09, 0x1a, 0x1f, 0x1a, 0x1a, 0x0a, 0x1a, 0x08};  // 
    char code Data_8[]={0x04, 0x08, 0x1f, 0x08, 0x0e, 0x08, 0x0e, 0x08};  //�� 
        
    LCD_Init();
    HC_SR04_Init();
    DRV8833_Init();
    
    LCD_Write_Cmd(0x40);  // 0100 0000;ָ�� 0x40 �� CGRAM ��ַ0 ��ʼд���ַ���ģ��
	for(i=0; i<8; i++){
		LCD_Write_Data(Data_1[i]);  // д���Զ������� ��
    }
    for(i=0; i<8; i++){
	LCD_Write_Data(Data_2[i]);  // д���Զ������� ��
    }
    for(i=0; i<8; i++){
	LCD_Write_Data(Data_3[i]);  // д���Զ������� 
    }
    for(i=0; i<8; i++){
	LCD_Write_Data(Data_4[i]);  // д���Զ������� 
    }    
    for(i=0; i<8; i++){
	LCD_Write_Data(Data_5[i]);  // д���Զ������� 
    }
    for(i=0; i<8; i++){
	LCD_Write_Data(Data_6[i]);  // д���Զ������� 
    }
    for(i=0; i<8; i++){
	LCD_Write_Data(Data_7[i]);  // д���Զ������� 
    }
    for(i=0; i<8; i++){
	LCD_Write_Data(Data_8[i]);  // д���Զ������� 
    }
    
   	LCD_Write_Cmd(0x80+0x4a);  // ����DDRAM��ַ���ڶ��е�10����ʾ�ַ���ģ
	LCD_Write_Data(0);LCD_Write_Data(1);LCD_Write_Data(51);LCD_Write_Data(48);
    LCD_Write_Data(52); LCD_Write_Data(54);                         //����3046
    LCD_Write_Cmd(0x80+0x40);  // ����DDRAM��ַ���ڶ��е�1����ʾ�ַ���ģ
	LCD_Write_Data(2);LCD_Write_Data(3);LCD_Write_Data(4);LCD_Write_Data(5);
    LCD_Write_Data(6); LCD_Write_Data(7);
    
    LCD_Write_Cmd(0x80+0x00);
    for(i=0;i<9;i++){LCD_Write_Data(Distance_show[i]);}
    LCD_Write_Cmd(0x80+0x0e);
    for(i=0;i<2;i++){LCD_Write_Data(Distance_Num_show[i]);}

   
        
    while(1)
    {                
        S=Distance_HC_SR04()*10;//����С�����һλ
        dis_S[0]=S/1000+0x30;
        dis_S[1]=S%1000/100+0x30;
        dis_S[2]=S%1000%100/10+0x30;
        dis_S[3]='.';
        dis_S[4]=S%1000%100%10%10+0x30;
        dis_S[5]='\0';
        LCD_Write_Cmd(0x80+0x09);
        for(i=0;i<5;i++){LCD_Write_Data(dis_S[i]);}//�������������ʾ  
        
        CAR_TrackTask();
//        if (dis_S[0]-0x30==0&&dis_S[1]-0x30==0&&dis_S[2]-0x30<=7){
        if ((dis_S[0]-0x30)*100+(dis_S[1]-0x30)*10+dis_S[2]-0x30<=30){
            if (R1==1) {       //��һ״̬R1
                CAR_Stop();delay_1ms(1500);
                CAR_RightTurn(50);delay_1ms(1000);
          } else  {  //��һ״̬L1
                CAR_Stop();delay_1ms(1500);
                CAR_LeftTurn(50);delay_1ms(1000);
          }   
       }
    }

}
