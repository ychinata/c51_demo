#include <REGX52.H>

//20230711 todo
// 合并LED4_Display和LED8_Display
// 新建nixietube.c
 
unsigned char code fseg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned char code segbit[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
//unsigned char  disbuf[4]={0,0,0,0};
unsigned char  disbuf[8]={0,0,0,0,0,0,0,0}; 


 //-----------------------------------------------------------------------------
// 函数原形定义
#define uchar unsigned char

void main (void);					// 主函数
void LED4_Display (void);			// LED显示
void LED8_Display (void);			// LED显示
void LED_OUT(uchar X);				// LED单字节串行移位函数

unsigned char code LED_0F[];		// LED字模表

//P1.0-1.2也可
sbit NIXIE_DIO  = P1^3;				//串行数据输入
sbit NIXIE_RCLK = P1^4;				//时钟脉冲信号——上升沿有效
sbit NIXIE_SCLK = P1^5;				//打入信号————上升沿有效

//-----------------------------------------------------------------------------
// 全局变量
uchar LED[8];	//用于LED的8位显示缓存


//*****************************************************************************
// 主程序
//
void main (void) 
{

	LED[0]=1;
	LED[1]=2;
	LED[2]=3;
	LED[3]=4;
	LED[4]=5;
	LED[5]=6;
	LED[6]=7;
	LED[7]=8;    

	while(1)
	{
		LED4_Display();
        //LED8_Display();
	} 
} 

//4位数码管显示
void LED4_Display(void)
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

//8位数码管显示
void LED8_Display (void)
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
	//显示第5位
	led_table = LED_0F + LED[4];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x10);	

	NIXIE_RCLK = 0;
	NIXIE_RCLK = 1;
	//显示第6位
	led_table = LED_0F + LED[5];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x20);	

	NIXIE_RCLK = 0;
	NIXIE_RCLK = 1;
	//显示第7位
	led_table = LED_0F + LED[6];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x40);	

	NIXIE_RCLK = 0;
	NIXIE_RCLK = 1;
	//显示第8位
	led_table = LED_0F + LED[7];
	i = *led_table;

	LED_OUT(i);		
	LED_OUT(0x80);	

	NIXIE_RCLK = 0;
	NIXIE_RCLK = 1;
}

void LED_OUT(uchar X)
{
	uchar i;
	for(i=8;i>=1;i--)
	{
		if (X&0x80) 
            NIXIE_DIO=1; 
        else 
            NIXIE_DIO=0;
		X<<=1;
		NIXIE_SCLK = 0;
		NIXIE_SCLK = 1;
	}
}

unsigned char code LED_0F[] = 
{// 0	 1	  2	   3	4	 5	  6	   7	8	 9	  A	   b	C    d	  E    F    -
	0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x8C,0xBF,0xC6,0xA1,0x86,0xFF,0xbf
};



