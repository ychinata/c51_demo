#ifndef _HCSR04_h_
#define _HCSR04_h_
#include <STC12C5A60S2.H>
#include "typedef.h"

sbit Trig = P1^6;
sbit Echo = P1^7;

// º¯ÊıÉùÃ÷
double Distance_HC_SR04(void);
void HC_SR04_Init();

#endif