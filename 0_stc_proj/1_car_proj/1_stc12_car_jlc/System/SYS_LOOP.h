//ϵͳ����������ײ��߼�  ΢�Ź��ںţ�����������
#ifndef __SYS_LOOP_H__
#define __SYS_LOOP_H__

unsigned char SYS_New_LoopFun(unsigned int Time,void (*Fun)(void));
unsigned char SYS_Del_LoopFun(void (*Fun)(void));
unsigned char SYS_New_DelayFun(unsigned int Time,void (*Fun)(void));
unsigned char SYS_New_MessageFun(unsigned char Message,void (*Fun)(void));
unsigned char SYS_Del_MessageFun(void (*Fun)(void));
unsigned char SYS_SendMessage(unsigned char Message);

void SYS_LOOP_Init(void);
void SYS_LOOP_While_APP(void);
void SYS_TimerInterrupt_App(void);

#endif