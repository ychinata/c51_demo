#include <REGX52.H>
#include "LCD1602.h"

unsigned char rxData = 0;

void UART_Init_11M0592_1200BPS(void);
void UART_Init_11M0592_2400BPS(void);
void UART_Init_11M0592_4800BPS(void);
void UART_Init_11M0592_9600BPS(void);
void UART_Init_12M_4800BPS(void);

void UART_Init(void)
{
    //UART_Init_11M0592_1200BPS();
    //UART_Init_11M0592_2400BPS();
    //UART_Init_11M0592_4800BPS();
    //UART_Init_11M0592_9600BPS();
    UART_Init_12M_4800BPS();
}

void UART_Init_11M0592_1200BPS(void)		//1200bps@11.0592MHz
{
	PCON |= 0x80;		//使能波特率倍速位SMOD
	SCON = 0x50;		//8位数据,可变波特率
//	AUXR &= 0xBF;		//定时器时钟12T模式
//	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xD0;		//设置定时初始值
	TH1 = 0xD0;		//设置定时重载值
	ET1 = 0;		//禁止定时器%d中断
	TR1 = 1;		//定时器1开始计时
	EA=1;			//打开总中断
	ES=1;			//打开串口中断      
}


void UART_Init_11M0592_2400BPS(void)		//2400bps@11.0592MHz
{
	PCON |= 0x80;		//使能波特率倍速位SMOD
	SCON = 0x50;		//8位数据,可变波特率
	//AUXR &= 0xBF;		//定时器时钟12T模式
	//AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xE8;		//设置定时初始值
	TH1 = 0xE8;		//设置定时重载值
	ET1 = 0;		//禁止定时器%d中断
	TR1 = 1;		//定时器1开始计时
	EA=1;			//打开总中断
	ES=1;			//打开串口中断    
}

// 普中开发板可用
void UART_Init_11M0592_4800BPS(void)///串口初始化，4800bps@11.0592MHz
{
	SCON = 0x50;	//8位数据,可变波特率
	PCON |= 0x80;	//使能波特率倍速位SMOD
	TMOD &= 0x0F;
	TMOD |= 0x20;	//设置定时器模式
	TL1 = 0xF4;		//设定定时初值
	TH1 = 0xF4;		//设定定时器重装值
	ET1 = 0;	 	//打开定时器中断
	TR1 = 1;		//定时器1开始计时
	EA=1;			//打开总中断
	ES=1;			//打开串口中断
}


/**
  * @brief  串口初始化，9600bps@11.0592MHz
            普中开发板可用
  * @param  无
  * @retval 无
  */
void UART_Init_11M0592_9600BPS(void)		
{
	PCON |= 0x80;		//使能波特率倍速位SMOD
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFA;		//设定定时初值
	TH1 = 0xFA;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	EA=1;			//打开总中断
	ES=1;			//打开串口中断
}

/**
  * @brief  : 串口通信
  * @author : 江科大自化协
  * @date   : 2020
  * @history:
  */
void UART_Init_12M_4800BPS(void)		//4800bps@12.000MHz
{
	PCON |= 0x80;		//使能波特率倍速位SMOD
	SCON = 0x50;		//8位数据,可变波特率
//	AUXR &= 0xBF;		//定时器时钟12T模式
//	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xF3;		//设置定时初始值
	TH1 = 0xF3;		//设置定时重载值
	ET1 = 0;		//禁止定时器%d中断
	TR1 = 1;		//定时器1开始计时
	EA=1;			//打开总中断
	ES=1;			//打开串口中断    
}

/**
  * @brief  串口发送一个字节数据
  * @param  Byte 要发送的一个字节数据
  * @retval 无
  */
void UART_SendByte(unsigned char Byte)
{
	SBUF=Byte;
	while(TI==0);
	TI=0;
}

/*串口中断函数模板
void UART_Routine() interrupt 4
{
	if(RI==1)
	{
		
		RI=0;
	}
}
*/
void UART_Routine() interrupt 4	//串口专用中断4
{
    //LCD_ShowString(1, 1, "Light Led:");//放在main函数while循环外
    //如果接收标志位为1，接收到了数据
	if (RI==1) {
//		P2=SBUF;				//读取数据，取反后输出到LED
		rxData = SBUF;
        //将收到的数据发回串口
		UART_SendByte(rxData);
		LCD_ShowHexNum(1, 11, rxData, 2);						
		RI = 0;					//接收标志位清0		
	}
}
