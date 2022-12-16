#include <REGX52.H>
#include "Delay.h"
#include "UART.h"
#include "LCD1602.h"

unsigned char RXdata;

void main()
{
	LCD_Init();
 	UART_Init();		//串口初始化
    P2=~0xff;
	while(1){
		if(RXdata==0xd){
			P2=~0x01;
		}else if(RXdata==2){
			P2=~0x02;
		}else{}
	}
}

void UART_Routine() interrupt 4	//串口专用中断4
{
	if(RI==1)					//如果接收标志位为1，接收到了数据
	{
//		P2=SBUF;				//读取数据，取反后输出到LED
		RXdata=SBUF;
		UART_SendByte(RXdata);
		LCD_ShowHexNum(1,1,RXdata,2);						//将受到的数据发回串口
		RI=0;					//接收标志位清0
		
	}
}
