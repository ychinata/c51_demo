#include <STC12C5A60S2.H>
#include "delay.h"
#include "LCD.H"

void LCD_Check_Busy(){  //��æ�źź������ж�LCD�Ƿ��ڹ���

	uchar8 temp;         //�м��������ȡP0/P1/P2/P3ֵ

	LCD_Data = 0xff;
	LCD_RS = 0;
	LCD_RW = 1;

	do{
		LCD_E = 1;		  //ʹ��
		temp = LCD_Data;  //�м��������ȡP0/P1/P2/P3ֵ
		LCD_E = 0;		  //ʹ��
	}while(temp & 0x80);  //��λ���ж�
}


void LCD_Write_Cmd(uchar8 Cmd){//LCDдָ���������

//	LCD_Check_Busy();  //��æ

	LCD_RS = 0;  // 0 ָ��Ĵ��� 
	LCD_RW = 0;  // 0 д����

	LCD_E = 0;   // 0 ׼�� 
	LCD_Data = Cmd;  //D0-D7��Ҫ���͵�����
	delay_1ms(2);
	
	LCD_E = 1;  // �����䣬��ʼ����
	delay_1ms(7);

	LCD_E = 0;  //�����䣬ָ��д�����
}



void LCD_Write_Data(uchar8 Data){//LCDд���ݲ�������

//	LCD_Check_Busy();  // ��æ

	LCD_RS = 1;  // 1 ���ݼĴ��� 
	LCD_RW = 0;  // 0 д����

	LCD_E = 0;   // 0 д����׼����ʼ
	LCD_Data = Data;  // D0-D7��Ҫ���͵�����
	delay_1ms(2);
	
	LCD_E = 1;  // �����䣬��ʼ����
	delay_1ms(7);

	LCD_E = 0;  //  �����䣬����д�����
}


void LCD_Init(){         //LCD��ʼ������

	LCD_Write_Cmd(0x01); //ָ��5������ָ��/���DDRAM����00 0000 0001
	LCD_Write_Cmd(0x06); //ָ��3��д��ģʽ����ָ���00 0000 0110��1I/DS��
	LCD_Write_Cmd(0x0c); //ָ��2����ʾ����ָ���00 0000 1100 ��1DCB��
	LCD_Write_Cmd(0x38); //ָ��1������ģʽ����ָ���00 0011 1000��1DLNF��
//	LCD_Write_Cmd(0x80); //ָ��8��DDRAM��ַ����ָ���00 1000 0000
}
