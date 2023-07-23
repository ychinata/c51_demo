#include <REGX52.H>
#ifndef __SERVO_H
#define __SERVO_H


void SERVO_Timer0_Init();
void SERVO_Set90DegPlus();
void SERVO_Set90DegMinus();
void SERVO_Task(void);

#endif