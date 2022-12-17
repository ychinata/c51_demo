#include <REGX52.H>
#include "Delay.h"
#include "UART.h"
#include "LCD1602.h"


// 配置修改：UART_Init

/**
  * @brief  : 串口通信
                通过串口控制LED灯，发送1-8点亮对应的LED，
                发送0点亮全部，发送其它熄灭全部
  * @author : xy
  * @date   : 2022.12.16
  * @history:
  */
void main()
{
	LCD_Init();
 	UART_Init();		//串口初始化
    
    LCD_ShowString(1, 1, "Light Led:");
    
	while(1){
        // 点亮第1-8个LED
		if (rxData >=1 && rxData <= 8){
			P2 = ~(0x01<<(rxData-1));    
        } else if (rxData == 0) { // 全部点亮
            P2 = ~0xff;            
		} else { // 全部熄灭
            P2 = ~0x00;
        }
	}
}


