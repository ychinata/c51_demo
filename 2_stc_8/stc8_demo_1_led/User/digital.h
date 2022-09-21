#ifndef _DIGITAL_H
#define _DIGITAL_H
#include <STC8H.H>
#include "types.h"

void Digital_Init(void);
void showNetwork(const uint8_t pData);
void showLed(uint8_t segment, uint8_t pData, uint8_t flag);

#endif