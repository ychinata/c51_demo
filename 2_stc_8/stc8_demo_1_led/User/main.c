#include <STC8H.H>

// 包含了stc8h.h，就不用包含reg51并声明寄存器
//#include "reg51.h"
//sfr P0M1 = 0x93;
//sfr P0M0 = 0x94;

// 
/*
 * Func:延时函数
 * Author: STC-ISP
 * Date: 2022.9.21
 */
void Delay1000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	//_nop_();
	//_nop_();
	i = 4;
	j = 6;
	k = 203;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


//软延时
void delay()
{
    int i;
    int j;
    for (i = 0; i < 10000; i++) {
        for (j = 0; j < 1000; j++) {
    
        }
    }

}

void LED_Flash()
{
	unsigned char i;
    P2 = 0x01;
    for (i = 0; i < 8; i++) {
        P2 = ~(0x01 << i);
        //delay();
        Delay1000ms();
    }
}

/*
 * Func:闪烁LED灯
 * Author: xy
 * Date: 2022.9.21
 */
void main1()
{
    //P0M0 = 0x00;    //P0口准双向输入输出
    //P0M1 = 0x00;    //P0口准双向输入输出
    P2M0 = 0x00;    //P2口准双向输入输出
    P2M1 = 0x00;    //P2口准双向输入输出
    
    while (1) {
        P2 = 0x00;
        //delay();
        Delay1000ms();
        P2 = 0xff;
        //delay();
        Delay1000ms();
    }
}


void main()
{
    P2M0 = 0x00;    //P2口准双向输入输出
    P2M1 = 0x00;    //P2口准双向输入输出
    while (1) {
        LED_Flash();
    }
}
