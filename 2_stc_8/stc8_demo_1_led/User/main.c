#include <STC8H.H>

// 包含了stc8h.h，就不用包含reg51并声明寄存器
//#include "reg51.h"
//sfr P0M1 = 0x93;
//sfr P0M0 = 0x94;

#define uchar unsigned char
#define uint unsigned int
#define LED_PORT P2

void LED_WaterfallFancy();


void main()
{
    P2M0 = 0x00;    //P2口准双向输入输出
    P2M1 = 0x00;    //P2口准双向输入输出
    while (1) {
        // LED_BlinkSimple();
		LED_WaterfallFancy();
    }
}

// 
/*
 * Func:延时函数
 * Author: STC-ISP
 * Date: 2022.9.21
	2022.9.26 改成约100ms，等替换成传参的
 */
void Delay1000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	//_nop_();
	//_nop_();
	i = 10; // 4很快
	j = 6;
	k = 203;
	do {
		do {
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay500ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 22;
	j = 3;
	k = 227;
	do {
		do {
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

// 暂不采用定时器延时
void timerDelay()
{
	Delay1000ms();
}

/* 普通流水灯 */
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
 * Func:闪烁LED灯，全亮全灭
 * Author: xy
 * Date: 2022.9.21
 */
void LED_BlinkSimple()
{
    //P0M0 = 0x00;    //P0口准双向输入输出
    //P0M1 = 0x00;    //P0口准双向输入输出
    //P2M0 = 0x00;    //P2口准双向输入输出
    //P2M1 = 0x00;    //P2口准双向输入输出
    int i = 0;
	for (i = 0; i < 5; i++) {
		P2 = 0x00;
		//delay();
		Delay1000ms();
		P2 = 0xff;
		//delay();
		Delay1000ms();	
	}
}

/*
 * Func:闪烁LED灯，单双交替
 * Author: xy
 * Date: 2022.9.21
 */
void LED_BlinkOddEven()
{
    int i = 0;
	for (i = 0; i < 2; i++) {
		P2 = 0x55;
		//delay();
		Delay500ms();
		P2 = 0xaa;
		//delay();
		Delay500ms();
	}	
}


/*
 * Func：LED花式流水灯
 * Author: xy
 * Date: 2022.9.26
 */
void LED_WaterfallFancy()
{
	uchar index = 0;//索引
	static uchar initData = 0x00;

	//样式1：从左向右流水，从右向左流水
	for (index; index > 7; index++) {
		LED_PORT = ~(0x01 << index);
		timerDelay();
	}
	for (index; index > 0; index--) {
		LED_PORT = ~(0x01 << index);
		timerDelay();
	}

	//样式2：
	for(index = 0;index < 7; index++){
		LED_PORT = (0xFF & ~(0x01 << index)) & (0xFF & ~(0x80 >> index));
		timerDelay();
	}

	//样式3：
	for(index = 0;index < 8; index++){
		LED_PORT = ~(initData += 0x01 << index);
		timerDelay();
	}
	for(;index > 0;index--){
		LED_PORT = ~(initData -= 0x01 << index);
		timerDelay();
	}
	
	// 样式4：
	LED_BlinkSimple();
	
	// 样式5：
	LED_BlinkOddEven();
	
	
}

