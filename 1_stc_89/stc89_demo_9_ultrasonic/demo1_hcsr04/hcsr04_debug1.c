
/*SMC1602A(16*2)模拟口线接线方式
连接线图:	
       ---------------------------------------------------
       |LCM-----51   |	LCM-----51   |	LCM------51      |
       --------------------------------------------------|
       |DB0-----P1.0 |	DB4-----P1.4 |	RW-------P3.4    |
       |DB1-----P1.1 |	DB5-----P1.5 |	RS-------P3.3    |
       |DB2-----P1.2 |	DB6-----P1.6 |	E--------P3.5    |
       |DB3-----P1.3 |	DB7-----P1.7 |	VLCD接1K电阻到GND|
       ---------------------------------------------------
接线：模块TRIG接 P2.6  ECH0 接P2.7

本程序源码只供学习参考，不得应用于商业用途，如有需要请联系作者。

[注:AT89x51使用12M或11.0592M晶振,实测使用11.0592M]
=============================================================*/
//#include <AT89x51.H>		//器件配置文件
#include <REGX52.H>
#include <intrins.h>
#include "oled.h"

#define  RX  P2_7
#define  TX  P2_6   

#define Key_Data P2_0 //定义Keyboard引脚
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

static unsigned char DisNum = 0; //显示用指针				  
unsigned int  time=0;
unsigned long S=0;
bit      flag =0;
unsigned char disbuff[4]	   ={ 0,0,0,0,};



//5ms延时
void Delay5Ms(void)
{
	unsigned int TempCyc = 5552;
	while(TempCyc--);
}

//400ms延时
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
	
	 S=(time*1.7)/100;     //算出来是CM
	 if((S>=700)||flag==1) //超出测量范围显示“-”
	 {	 
	  flag=0;
	 
//	  DisplayOneChar(0, 1, ASCII[11]);
//	  DisplayOneChar(1, 1, ASCII[10]);	//显示点
//	  DisplayOneChar(2, 1, ASCII[11]);
//	  DisplayOneChar(3, 1, ASCII[11]);
//	  DisplayOneChar(4, 1, ASCII[12]);	//显示M
	 } else {
         OLED_ShowNum(0, 0, S, 4, 16); 
//	  disbuff[0]=S%1000/100;
//	  disbuff[1]=S%1000%100/10;
//	  disbuff[2]=S%1000%10 %10;
//	  DisplayOneChar(0, 1, ASCII[disbuff[0]]);
//	  DisplayOneChar(1, 1, ASCII[10]);	//显示点
//	  DisplayOneChar(2, 1, ASCII[disbuff[1]]);
//	  DisplayOneChar(3, 1, ASCII[disbuff[2]]);
//	  DisplayOneChar(4, 1, ASCII[12]);	//显示M
    }
}

/********************************************************/
void zd0() interrupt 1 		 //T0中断用来计数器溢出,超过测距范围
{
    flag=1;							 //中断溢出标志
}
  
/********************************************************/
void  StartModule() 		         //启动模块
  {
	  TX=1;			                     //启动一次模块
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
	Delay400Ms(); //延时
    OLED_Init();			//初始化OLED  
    OLED_Clear(); 		//清屏函数    
    SERVO_Init();
    
    while(1)
    {
        TMOD=0x11;		   //设T0为方式1，GATE=1；定时器0和1都开启
        TH0=0;
        TL0=0;          
        ET0=1;             //允许T0中断
        EA=1;			   //开启总中断	
        OLED_ShowNum(0, 0, 0, 4, 16);        
        while(1)
        {
            StartModule();
            while(!RX);		//当RX为零时等待
            TR0=1;			    //开启计数
            while(RX);			//当RX为1计数并等待
            TR0=0;				//关闭计数
            Count();			//计算
            delayms(100);
            OLED_ShowNum(0, 0, 1, 4, 16);   
        }
    }
}



                