#ifndef _ds1302_H
#define _ds1302_H

//#include "public.h"
//#include "reg52.h"
#include <REGX52.H>

//管脚定义
sbit DS1302_RST=P3^5;//复位管脚
sbit DS1302_CLK=P3^6;//时钟管脚
sbit DS1302_IO=P3^4;//数据管脚

//变量声明
extern unsigned char gDS1302_TIME[7];//存储时间

//函数声明
void ds1302_init(void);
void ds1302_read_time(void);


#endif