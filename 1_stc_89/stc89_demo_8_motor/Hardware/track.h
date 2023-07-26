//2023.7.25

#ifndef __TRACK_H__
#define __TRACK_H__

#include <REGX52.H>
//#include <STC12C5A60S2.H>
//#include <STC12C5A.H>

sfr P4   = 0xC0;

sbit TRACK_PIN_L = P4^4;
sbit TRACK_PIN_C = P4^5;
sbit TRACK_PIN_R = P4^6;


#endif