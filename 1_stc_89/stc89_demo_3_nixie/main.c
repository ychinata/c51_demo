#include <REGX52.H>
 
 unsigned char code fseg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
 unsigned char code segbit[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
 unsigned char  disbuf[4]={0,0,0,0};


 //-----------------------------------------------------------------------------
// 函数原形定义
#define uchar unsigned char

void main (void);					// 主函数
void LED4_Display (void);			// LED显示
void LED_OUT(uchar X);				// LED单字节串行移位函数

unsigned char code LED_0F[];		// LED字模表

sbit NIXIE_DIO = P1^0;				//串行数据输入
sbit NIXIE_RCLK  = P1^1;				//时钟脉冲信号——上升沿有效
sbit NIXIE_SCLK = P1^2;				//打入信号————上升沿有效

//-----------------------------------------------------------------------------
// 全局变量
uchar LED[8];	//用于LED的8位显示缓存


//*****************************************************************************
// 主程序
//
void main (void) 
{

	LED[0]=1;
	LED[1]=1;
	LED[2]=1;
	LED[3]=1;

	while(1)
	{
		LED4_Display ();
	} 
} 

void LED4_Display (void)
{
	unsigned char code *led_table;          // 查表指针
	uchar i;
	//显示第1位
	led_table = LED_0F + LED[0];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x01);		

	NIXIE_RCLK = 0;
	NIXIE_RCLK = 1;
	//显示第2位
	led_table = LED_0F + LED[1];
	i = *led_table;

	LED_OUT(i);		
	LED_OUT(0x02);		

	NIXIE_RCLK = 0;
	NIXIE_RCLK = 1;
	//显示第3位
	led_table = LED_0F + LED[2];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x04);	

	NIXIE_RCLK = 0;
	NIXIE_RCLK = 1;
	//显示第4位
	led_table = LED_0F + LED[3];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x08);		

	NIXIE_RCLK = 0;
	NIXIE_RCLK = 1;
}

void LED_OUT(uchar X)
{
	uchar i;
	for(i=8;i>=1;i--)
	{
		if (X&0x80) NIXIE_DIO=1; else NIXIE_DIO=0;
		X<<=1;
		NIXIE_SCLK = 0;
		NIXIE_SCLK = 1;
	}
}

unsigned char code LED_0F[] = 
{// 0	 1	  2	   3	4	 5	  6	   7	8	 9	  A	   b	C    d	  E    F    -
	0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x8C,0xBF,0xC6,0xA1,0x86,0xFF,0xbf
};



