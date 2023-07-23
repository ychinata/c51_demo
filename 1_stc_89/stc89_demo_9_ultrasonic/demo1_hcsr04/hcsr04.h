#ifndef _HCSR04_H_
#define _HCSR04_H_
#include <REGX52.H>

void HCSR04_Init(void);
void HCSR04_Trig(void);
void HCSR04_Recv(void);
float HCSR04_Calc(void);
float HCSR04_GetDistance(void);

void HCSR04_Task(void);


#endif