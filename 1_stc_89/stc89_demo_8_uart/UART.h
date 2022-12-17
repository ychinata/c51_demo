#ifndef __UART_H__
#define __UART_H__

extern unsigned char rxData;

void UART_Init();
void UART_SendByte(unsigned char Byte);

#endif
