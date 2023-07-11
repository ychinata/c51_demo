#include <REGX52.H>

//20230711 todo
// �ϲ�LED4_Display��LED8_Display
// �½�nixietube.c
 
unsigned char code fseg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned char code segbit[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
//unsigned char  disbuf[4]={0,0,0,0};
unsigned char  disbuf[8]={0,0,0,0,0,0,0,0}; 


 //-----------------------------------------------------------------------------
// ����ԭ�ζ���
#define uchar unsigned char

void main (void);					// ������
void LED4_Display (void);			// LED��ʾ
void LED8_Display (void);			// LED��ʾ
void LED_OUT(uchar X);				// LED���ֽڴ�����λ����

unsigned char code LED_0F[];		// LED��ģ��

//P1.0-1.2Ҳ��
sbit NIXIE_DIO  = P1^3;				//������������
sbit NIXIE_RCLK = P1^4;				//ʱ�������źš�����������Ч
sbit NIXIE_SCLK = P1^5;				//�����źš���������������Ч

//-----------------------------------------------------------------------------
// ȫ�ֱ���
uchar LED[8];	//����LED��8λ��ʾ����


//*****************************************************************************
// ������
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

//4λ�������ʾ
void LED4_Display(void)
{
	unsigned char code *led_table;          // ���ָ��
	uchar i;
	//��ʾ��1λ
	led_table = LED_0F + LED[0];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x01);		

	NIXIE_RCLK = 0;
	NIXIE_RCLK = 1;
	//��ʾ��2λ
	led_table = LED_0F + LED[1];
	i = *led_table;

	LED_OUT(i);		
	LED_OUT(0x02);		

	NIXIE_RCLK = 0;
	NIXIE_RCLK = 1;
	//��ʾ��3λ
	led_table = LED_0F + LED[2];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x04);	

	NIXIE_RCLK = 0;
	NIXIE_RCLK = 1;
	//��ʾ��4λ
	led_table = LED_0F + LED[3];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x08);		

	NIXIE_RCLK = 0;
	NIXIE_RCLK = 1;
}

//8λ�������ʾ
void LED8_Display (void)
{
	unsigned char code *led_table;          // ���ָ��
	uchar i;
	//��ʾ��1λ
	led_table = LED_0F + LED[0];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x01);		

	NIXIE_RCLK = 0;
	NIXIE_RCLK = 1;
	//��ʾ��2λ
	led_table = LED_0F + LED[1];
	i = *led_table;

	LED_OUT(i);		
	LED_OUT(0x02);		

	NIXIE_RCLK = 0;
	NIXIE_RCLK = 1;
	//��ʾ��3λ
	led_table = LED_0F + LED[2];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x04);	

	NIXIE_RCLK = 0;
	NIXIE_RCLK = 1;
	//��ʾ��4λ
	led_table = LED_0F + LED[3];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x08);		

	NIXIE_RCLK = 0;
	NIXIE_RCLK = 1;
	//��ʾ��5λ
	led_table = LED_0F + LED[4];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x10);	

	NIXIE_RCLK = 0;
	NIXIE_RCLK = 1;
	//��ʾ��6λ
	led_table = LED_0F + LED[5];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x20);	

	NIXIE_RCLK = 0;
	NIXIE_RCLK = 1;
	//��ʾ��7λ
	led_table = LED_0F + LED[6];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x40);	

	NIXIE_RCLK = 0;
	NIXIE_RCLK = 1;
	//��ʾ��8λ
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


