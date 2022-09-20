/*
 * func: LED breathing light
 * author: h00421956
 * date: 2021.12.9 
 */

#include <REGX52.H>

sbit LED = P2^2;

#define LED_ON 0
#define LED_OFF 1

void Delay(unsigned int t) {
	while(t--);
}

void main() {
	unsigned char Time,i;
	while(1) {
		for (Time=0; Time < 100; Time++) {		//改变亮灭时间，由暗到亮
			for (i=0; i < 20; i++) {			//计次延时
				LED = LED_ON;					//LED亮
				Delay(Time);			//延时Time, 初始亮的时间最少
				LED = LED_OFF;					//LED灭
				Delay(100-Time);		//延时100-Time
			}
		}
		for (Time=100; Time > 0; Time--) {	//改变亮灭时间，由亮到暗
			for (i=0; i<20; i++) {			//计次延时
				LED = LED_ON;					//LED亮
				Delay(Time);			//延时Time，初始亮的时间最多
				LED = LED_OFF;					//LED灭
				Delay(100-Time);		//延时100-Time
			}
		}
	}
}
