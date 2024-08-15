//系统程序调度器底层逻辑  微信公众号：物联网零妖
#include "SYS_LOOP.h"
#define	SYS_ListCount	2		//程序调度器深度，决定同时运行几个子程序

struct 
{
	unsigned char Flag[SYS_ListCount];
	void (*Fun_Point_List[SYS_ListCount])(void);
	unsigned int Counter[SYS_ListCount];
	unsigned int Timer[SYS_ListCount];
}SYS_LoopFun_Struct;

static unsigned char SYS_LoopFun_Interrupt_Flag=0;

/********************************************************************************************/

//添加一个循环执行的函数  成功返回1，失败返回0
unsigned char SYS_New_LoopFun(unsigned int Time,void (*Fun)(void))
{
	unsigned char i=0;
	for(i=0;i<SYS_ListCount;i++)
	{
		if(SYS_LoopFun_Struct.Flag[i] == 0)
		{
			SYS_LoopFun_Struct.Flag[i] = 1;
			SYS_LoopFun_Struct.Counter[i] = 0;
			SYS_LoopFun_Struct.Fun_Point_List[i] = Fun;
			SYS_LoopFun_Struct.Timer[i] = Time-1;
			return 1;
		}
	}
	return 0;
}
//删除一个循环执行的函数
unsigned char SYS_Del_LoopFun(void (*Fun)(void))
{
	unsigned char i=0;
	for(i=0;i<SYS_ListCount;i++)
	{
		if(SYS_LoopFun_Struct.Fun_Point_List[i] == Fun)
		{
			SYS_LoopFun_Struct.Flag[i] = 0;
			SYS_LoopFun_Struct.Counter[i] = 0;
			SYS_LoopFun_Struct.Fun_Point_List[i] = 0;
			SYS_LoopFun_Struct.Timer[i] = 0;
			return 1;
		}
	}
	return 0;
}

/********************************************************************************************/

//系统定时器中断里面执行的函数
static void SYS_LoopFun_LOOP(void)
{
	unsigned char i=0,j=0;
	if(SYS_LoopFun_Interrupt_Flag == 0)
		return;
	SYS_LoopFun_Interrupt_Flag = 0;
	for(i=0;i<SYS_ListCount;i++) //循环定时的函数
	{
		if(SYS_LoopFun_Struct.Flag[i])
		{
			SYS_LoopFun_Struct.Counter[i] ++ ;
			if(SYS_LoopFun_Struct.Counter[i] > SYS_LoopFun_Struct.Timer[i])
			{
				SYS_LoopFun_Struct.Counter[i] = 0;
				SYS_LoopFun_Struct.Fun_Point_List[i]();
			}
		}
	}
}
//初始化内存数据
void SYS_LOOP_Init(void)
{
	unsigned char i=0;
	for(i=0;i<SYS_ListCount;i++)
	{
		SYS_LoopFun_Struct.Flag[i] = 0;
		SYS_LoopFun_Struct.Counter[i] = 0;
	}
}
//在Main函数中执行  内部带while循环
void SYS_LOOP_While_APP(void)
{
	while(1)
	{
		SYS_LoopFun_LOOP();
	}
}
//放到定时器中断中的函数
void SYS_TimerInterrupt_App(void)
{
	SYS_LoopFun_Interrupt_Flag = 1;
}
//


