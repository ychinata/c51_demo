#ifndef _LCD_H_
#define _LCD_H_
#include <STC12C5A60S2.H>

#define LCD_Data P0
sbit LCD_RS = P2^6;  
sbit LCD_RW = P2^5;  
sbit LCD_E = P2^7;

//��æ�źź������ж�LCD�Ƿ��ڹ���
void LCD_Check_Busy();

//LCDдָ���������
void LCD_Write_Cmd(uchar8 Cmd);

//LCDд���ݲ�������
void LCD_Write_Data(uchar8 Data);

//LCD��ʼ������
void LCD_Init();


#endif