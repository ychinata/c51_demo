#include <STC8H.H>
#include "spi.h"

#define ESPI 0x02
#define FRAME_HEAD 0xEA
#define LED_FLAG  0x80


uint8_t network = 0;
// 4 digital status
uint8_t sData[4][2] = {
	{188, 1}, // show value:0xff power off all led. charging status
	{188, 1},
	{188, 1},
	{188, 1}
};

const uint8_t frame_head = 0xEA;

uint8_t frame_seg  = 0;
uint8_t frame_data = 0;
uint8_t frame_idx  = 0;

extern uint8_t sData[4][2];
extern uint8_t network;

void MX_SPI1_Init()
{
	SPDAT  = 0x00;
	SPCTL  = 0x40;                              //使能SPI从机模式
	SPSTAT = 0xC0;                              //清中断标志
	IE2    = ESPI;                              //使能SPI中断
}

void MX_SPI1_ISR() interrupt 9
{ 
	frame_data = SPDAT;
	
  if(frame_idx == 1) {       // 数据一
		frame_seg = frame_data;
		frame_idx = 2;
	} 
	else if(frame_idx == 2) {  // 数据二
		if(frame_seg == LED_FLAG) {
			network = frame_data;
			frame_idx = 0;
		} else {
			sData[frame_seg][0] = frame_data;
			frame_idx = 3;
		}
	}
	else if(frame_idx == 3) { // 数据三
		if(frame_seg < 4) {
			sData[frame_seg][1] = frame_data;
		}
		frame_idx = 0;
	}
	
	if(frame_head == frame_data) {
		frame_idx  = 1;
		WDT_CONTR = 0x37;                       //清看门狗,否则系统复位
	}
	
	SPSTAT = 0xC0;
}
