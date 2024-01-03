#include <STC12C5A60S2.H>
#include "delay.h"
#include "LCD.H"

void LCD_Check_Busy(){  //检忙信号函数，判断LCD是否在工作

	uchar8 temp;         //中间变量，读取P0/P1/P2/P3值

	LCD_Data = 0xff;
	LCD_RS = 0;
	LCD_RW = 1;

	do{
		LCD_E = 1;		  //使能
		temp = LCD_Data;  //中间变量，读取P0/P1/P2/P3值
		LCD_E = 0;		  //使能
	}while(temp & 0x80);  //按位与判断
}


void LCD_Write_Cmd(uchar8 Cmd){//LCD写指令操作函数

//	LCD_Check_Busy();  //检忙

	LCD_RS = 0;  // 0 指令寄存器 
	LCD_RW = 0;  // 0 写操作

	LCD_E = 0;   // 0 准备 
	LCD_Data = Cmd;  //D0-D7将要发送的数据
	delay_1ms(2);
	
	LCD_E = 1;  // 正跳变，开始接受
	delay_1ms(7);

	LCD_E = 0;  //负跳变，指令写入完毕
}



void LCD_Write_Data(uchar8 Data){//LCD写数据操作函数

//	LCD_Check_Busy();  // 检忙

	LCD_RS = 1;  // 1 数据寄存器 
	LCD_RW = 0;  // 0 写操作

	LCD_E = 0;   // 0 写操作准备开始
	LCD_Data = Data;  // D0-D7将要发送的数据
	delay_1ms(2);
	
	LCD_E = 1;  // 正跳变，开始工作
	delay_1ms(7);

	LCD_E = 0;  //  负跳变，数据写入完毕
}


void LCD_Init(){         //LCD初始化函数

	LCD_Write_Cmd(0x01); //指令5（清屏指令/清除DDRAM），00 0000 0001
	LCD_Write_Cmd(0x06); //指令3（写入模式设置指令），00 0000 0110（1I/DS）
	LCD_Write_Cmd(0x0c); //指令2（显示开关指令），00 0000 1100 （1DCB）
	LCD_Write_Cmd(0x38); //指令1（工作模式设置指令），00 0011 1000（1DLNF）
//	LCD_Write_Cmd(0x80); //指令8（DDRAM地址设置指令），00 1000 0000
}
