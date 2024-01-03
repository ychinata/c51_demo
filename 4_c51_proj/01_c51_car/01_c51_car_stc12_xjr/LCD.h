#ifndef _LCD_H_
#define _LCD_H_
#include <STC12C5A60S2.H>

#define LCD_Data P0
sbit LCD_RS = P2^6;  
sbit LCD_RW = P2^5;  
sbit LCD_E = P2^7;

//检忙信号函数，判断LCD是否在工作
void LCD_Check_Busy();

//LCD写指令操作函数
void LCD_Write_Cmd(uchar8 Cmd);

//LCD写数据操作函数
void LCD_Write_Data(uchar8 Data);

//LCD初始化函数
void LCD_Init();


#endif