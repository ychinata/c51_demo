
/*SMC1602A(16*2)ģ����߽��߷�ʽ
������ͼ:	
       ---------------------------------------------------
       |LCM-----51   |	LCM-----51   |	LCM------51      |
       --------------------------------------------------|
       |DB0-----P1.0 |	DB4-----P1.4 |	RW-------P3.4    |
       |DB1-----P1.1 |	DB5-----P1.5 |	RS-------P3.3    |
       |DB2-----P1.2 |	DB6-----P1.6 |	E--------P3.5    |
       |DB3-----P1.3 |	DB7-----P1.7 |	VLCD��1K���赽GND|
       ---------------------------------------------------
���ߣ�ģ��TRIG�� P2.6  ECH0 ��P2.7

������Դ��ֻ��ѧϰ�ο�������Ӧ������ҵ��;��������Ҫ����ϵ���ߡ�

[ע:AT89x51ʹ��12M��11.0592M����,ʵ��ʹ��11.0592M]
=============================================================*/
//#include <AT89x51.H>		//���������ļ�
#include <REGX52.H>
#include <intrins.h>
#include "oled.h"

#define  RX  P2_7
#define  TX  P2_6   

#define Key_Data P2_0 //����Keyboard����
#define Key_CLK  P3_2

void Delay5Ms(void);
void Delay400Ms(void);
void Decode(unsigned char ScanCode);

unsigned char ReadDataLCM(void);
unsigned char ReadStatusLCM(void);
unsigned char code mcustudio[] ={"mcustudio.com.cn"};
unsigned char code email[] =    {"fhwxaoo@163.com "};
unsigned char code Cls[] =      {"                "};
unsigned char code ASCII[15] =    {'0','1','2','3','4','5','6','7','8','9','.','-','M'};

static unsigned char DisNum = 0; //��ʾ��ָ��				  
unsigned int  time=0;
unsigned long S=0;
bit      flag =0;
unsigned char disbuff[4]	   ={ 0,0,0,0,};



//5ms��ʱ
void Delay5Ms(void)
{
	unsigned int TempCyc = 5552;
	while(TempCyc--);
}

//400ms��ʱ
void Delay400Ms(void)
{
	unsigned char TempCycA = 5;
	unsigned int TempCycB;
	while(TempCycA--)
		{
			TempCycB=7269;
			while(TempCycB--);
		};
}
/********************************************************/
void Count(void)
{
	 time=TH0*256+TL0;
	 TH0=0;
	 TL0=0;
	
	 S=(time*1.7)/100;     //�������CM
	 if((S>=700)||flag==1) //����������Χ��ʾ��-��
	 {	 
	  flag=0;
	 
//	  DisplayOneChar(0, 1, ASCII[11]);
//	  DisplayOneChar(1, 1, ASCII[10]);	//��ʾ��
//	  DisplayOneChar(2, 1, ASCII[11]);
//	  DisplayOneChar(3, 1, ASCII[11]);
//	  DisplayOneChar(4, 1, ASCII[12]);	//��ʾM
	 } else {
         OLED_ShowNum(0, 0, S, 4, 16); 
//	  disbuff[0]=S%1000/100;
//	  disbuff[1]=S%1000%100/10;
//	  disbuff[2]=S%1000%10 %10;
//	  DisplayOneChar(0, 1, ASCII[disbuff[0]]);
//	  DisplayOneChar(1, 1, ASCII[10]);	//��ʾ��
//	  DisplayOneChar(2, 1, ASCII[disbuff[1]]);
//	  DisplayOneChar(3, 1, ASCII[disbuff[2]]);
//	  DisplayOneChar(4, 1, ASCII[12]);	//��ʾM
    }
}

/********************************************************/
void zd0() interrupt 1 		 //T0�ж��������������,������෶Χ
{
    flag=1;							 //�ж������־
}
  
/********************************************************/
void  StartModule() 		         //����ģ��
  {
	  TX=1;			                     //����һ��ģ��
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_();
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_();
	  TX=0;
  }
/********************************************************/ 
void delayms(unsigned int ms)
{
	unsigned char i=100,j;
	for(;ms;ms--)
	{
		while(--i)
		{
			j=10;
			while(--j);
		}
	}
}
/*********************************************************/
void main(void)
{
	Delay400Ms(); //��ʱ
    OLED_Init();			//��ʼ��OLED  
    OLED_Clear(); 		//��������    
    SERVO_Init();
    
    while(1)
    {
        TMOD=0x11;		   //��T0Ϊ��ʽ1��GATE=1����ʱ��0��1������
        TH0=0;
        TL0=0;          
        ET0=1;             //����T0�ж�
        EA=1;			   //�������ж�	
        OLED_ShowNum(0, 0, 0, 4, 16);        
        while(1)
        {
            StartModule();
            while(!RX);		//��RXΪ��ʱ�ȴ�
            TR0=1;			    //��������
            while(RX);			//��RXΪ1�������ȴ�
            TR0=0;				//�رռ���
            Count();			//����
            delayms(100);
            OLED_ShowNum(0, 0, 1, 4, 16);   
        }
    }
}



                