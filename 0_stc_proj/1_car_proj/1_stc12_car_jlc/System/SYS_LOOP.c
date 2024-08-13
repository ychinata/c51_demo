//ϵͳ����������ײ��߼�  ΢�Ź��ںţ�����������
#include "SYS_LOOP.h"
#define	SYS_ListCount	2		//�����������ȣ�����ͬʱ���м����ӳ���

struct 
{
	unsigned char Flag[SYS_ListCount];
	void (*Fun_Point_List[SYS_ListCount])(void);
	unsigned int Counter[SYS_ListCount];
	unsigned int Timer[SYS_ListCount];
}SYS_LoopFun_Struct;

static unsigned char SYS_LoopFun_Interrupt_Flag=0;

/********************************************************************************************/

//���һ��ѭ��ִ�еĺ���  �ɹ�����1��ʧ�ܷ���0
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
//ɾ��һ��ѭ��ִ�еĺ���
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

//ϵͳ��ʱ���ж�����ִ�еĺ���
static void SYS_LoopFun_LOOP(void)
{
	unsigned char i=0,j=0;
	if(SYS_LoopFun_Interrupt_Flag == 0)
		return;
	SYS_LoopFun_Interrupt_Flag = 0;
	for(i=0;i<SYS_ListCount;i++) //ѭ����ʱ�ĺ���
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
//��ʼ���ڴ�����
void SYS_LOOP_Init(void)
{
	unsigned char i=0;
	for(i=0;i<SYS_ListCount;i++)
	{
		SYS_LoopFun_Struct.Flag[i] = 0;
		SYS_LoopFun_Struct.Counter[i] = 0;
	}
}
//��Main������ִ��  �ڲ���whileѭ��
void SYS_LOOP_While_APP(void)
{
	while(1)
	{
		SYS_LoopFun_LOOP();
	}
}
//�ŵ���ʱ���ж��еĺ���
void SYS_TimerInterrupt_App(void)
{
	SYS_LoopFun_Interrupt_Flag = 1;
}
//


