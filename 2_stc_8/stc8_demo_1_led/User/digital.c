#include "digital.h"

uint8_t num_map[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

uint8_t led_map[2][7][2] = {
  {
    {2,3},{3,2},{4,3},{4,2},{5,2},{5,3},{5,4}
  },
  {
    {1,2},{2,1},{1,3},{3,1},{1,4},{4,1},{5,1}
  }
};

void clearLed(uint8_t segment) {
	switch(segment) {
		case 0:
			P2M1|=0x02;P2M0&=~0x02;//高阻输入
			P2M1|=0x04;P2M0&=~0x04;//高阻输入
			P2M1|=0x08;P2M0&=~0x08;//高阻输入
			P2M1|=0x10;P2M0&=~0x10;//高阻输入
			P2M1|=0x20;P2M0&=~0x20;//高阻输入
			break;
		case 1:
			P2M1|=0x40;P2M0&=~0x40;//高阻输入
			P2M1|=0x80;P2M0&=~0x80;//高阻输入
			P0M1|=0x01;P0M0&=~0x01;//高阻输入
			P0M1|=0x02;P0M0&=~0x02;//高阻输入
			P0M1|=0x04;P0M0&=~0x04;//高阻输入
			break;
		case 2:
			P3M1|=0x10;P3M0&=~0x10;//高阻输入
			P3M1|=0x20;P3M0&=~0x20;//高阻输入
			P3M1|=0x40;P3M0&=~0x40;//高阻输入
			P3M1|=0x80;P3M0&=~0x80;//高阻输入
			P2M1|=0x01;P2M0&=~0x01;//高阻输入
			break;
		case 3:
			P1M1|=0x01;P1M0&=~0x01;//高阻输入
			P1M1|=0x02;P1M0&=~0x02;//高阻输入
			P1M1|=0x40;P1M0&=~0x40;//高阻输入
			P3M1|=0x04;P3M0&=~0x04;//高阻输入
			P3M1|=0x08;P3M0&=~0x08;//高阻输入
			break;
	}
}

void setPin(uint8_t segment, uint8_t pin_high, uint8_t pin_low)
{
	int clk = 120;
	clearLed(segment);
	// 第一个数码管
	if(segment == 0) {
		// 上拉
		if(pin_high == 1) {
			P2M1&=~0x02;P2M0|=0x02;//推挽输出
			P21 = 1;
		}
		else if(pin_high == 2) {
			P2M1&=~0x04;P2M0|=0x04;//推挽输出	
			P22 = 1;
		}
		else if(pin_high == 3) {
			P2M1&=~0x08;P2M0|=0x08;//推挽输出
			P23 = 1;
		}
		else if(pin_high == 4) {
			P2M1&=~0x10;P2M0|=0x10;//推挽输出
			P24 = 1;
		}
		else if(pin_high == 5) {
			P2M1&=~0x20;P2M0|=0x20;//推挽输出
			P25 = 1;
		}
		// 下拉
		if(pin_low == 1) {
			P2M1&=~0x02;P2M0|=0x02;//推挽输出
			P21 = 0;
		}
		else if(pin_low == 2) {
			P2M1&=~0x04;P2M0|=0x04;//推挽输出
			P22 = 0;
		}
		else if(pin_low == 3) {
			P2M1&=~0x08;P2M0|=0x08;//推挽输出
			P23 = 0;
		}
		else if(pin_low == 4){
			P2M1&=~0x10;P2M0|=0x10;//推挽输出
			P24 = 0;
		}
		else if(pin_low == 5) {
			P2M1&=~0x20;P2M0|=0x20;//推挽输出
			P25 = 0;
		}
	}// 第二个数码管
	else if(segment == 1) {
		// 上拉
		if(pin_high == 1) {
			P2M1&=~0x40;P2M0|=0x40;//推挽输出
			P26 = 1;
		}
		else if(pin_high == 2) {
			P2M1&=~0x80;P2M0|=0x80;//推挽输出
			P27 = 1;
		}
		else if(pin_high == 3) {
			P0M1&=~0x01;P0M0|=0x01;//推挽输出
			P00 = 1;
		}
		else if(pin_high == 4) {
			P0M1&=~0x02;P0M0|=0x02;//推挽输出
			P01 = 1;
		}
		else if(pin_high == 5) {
			P0M1&=~0x04;P0M0|=0x04;//推挽输出
			P02 = 1;
		}
		// 下拉
		if(pin_low == 1) {
			P2M1&=~0x40;P2M0|=0x40;//推挽输出
			P26 = 0;
		}
		else if(pin_low == 2) {
			P2M1&=~0x80;P2M0|=0x80;//推挽输出
			P27 = 0;
		}
		else if(pin_low == 3) {
			P0M1&=~0x01;P0M0|=0x01;//推挽输出
			P00 = 0;
		}
		else if(pin_low == 4){
			P0M1&=~0x02;P0M0|=0x02;//推挽输出
			P01 = 0;
		}
		else if(pin_low == 5) {
			P0M1&=~0x04;P0M0|=0x04;//推挽输出
			P02 = 0;
		}
	}
	// 第三个数码管
	else if(segment == 2) {
		// 上拉
		if(pin_high == 1) {
			P3M1&=~0x10;P3M0|=0x10;//推挽输出
			P34 = 1;
		}
		else if(pin_high == 2) {
			P3M1&=~0x20;P3M0|=0x20;//推挽输出
			P35 = 1;
		}
		else if(pin_high == 3) {
			P3M1&=~0x40;P3M0|=0x40;//推挽输出
			P36 = 1;
		}
		else if(pin_high == 4) {
			P3M1&=~0x80;P3M0|=0x80;//推挽输出
			P37 = 1;
		}
		else if(pin_high == 5) {
			P2M1&=~0x01;P2M0|=0x01;//推挽输出
			P20 = 1;
		}
		// 下拉
		if(pin_low == 1) {
			P3M1&=~0x10;P3M0|=0x10;//推挽输出
			P34 = 0;
		}
		else if(pin_low == 2) {
			P3M1&=~0x20;P3M0|=0x20;//推挽输出
			P35 = 0;
		}
		else if(pin_low == 3) {
			P3M1&=~0x40;P3M0|=0x40;//推挽输出
			P36 = 0;
		}
		else if(pin_low == 4){
			P3M1&=~0x80;P3M0|=0x80;//推挽输出
			P37 = 0;
		}
		else if(pin_low == 5) {
			P2M1&=~0x01;P2M0|=0x01;//推挽输出
			P20 = 0;
		}
	}
	// 第四个数码管
	else if(segment == 3) {
		// 上拉
		if(pin_high == 1) {
			P1M1&=~0x01;P1M0|=0x01;//推挽输出
			P10 = 1;
		}
		else if(pin_high == 2) {
			P1M1&=~0x02;P1M0|=0x02;//推挽输出
			P11 = 1;
		}
		else if(pin_high == 3) {
			P1M1&=~0x40;P1M0|=0x40;//推挽输出
			P16 = 1;
		}
		else if(pin_high == 4) {
			P3M1&=~0x04;P3M0|=0x04;//推挽输出
			P32 = 1;
		}
		else if(pin_high == 5) {
			P3M1&=~0x08;P3M0|=0x08;//推挽输出
			P33 = 1;
		}
		// 下拉
		if(pin_low == 1) {
			P1M1&=~0x01;P1M0|=0x01;//推挽输出
			P10 = 0;
		}
		else if(pin_low == 2) {
			P1M1&=~0x02;P1M0|=0x02;//推挽输出
			P11 = 0;
		}
		else if(pin_low == 3) {
			P1M1&=~0x40;P1M0|=0x40;//推挽输出
			P16 = 0;
		}
		else if(pin_low == 4){
			P3M1&=~0x04;P3M0|=0x04;//推挽输出
			P32 = 0;
		}
		else if(pin_low == 5) {
			P3M1&=~0x08;P3M0|=0x08;//推挽输出
			P33 = 0;
		}
	}
	
	while(clk--);
}

void showLed(uint8_t segment, uint8_t pData, uint8_t flag)
{
	int n, i;
	// 熄灭所有灯
  if(pData == 0xff) {
	  clearLed(segment); 
		return;
	}
  // 百分号
  setPin(segment, 2, 5);
  // 充电状态
  if(flag) {
    setPin(segment, 3, 5);
  }
  if(pData / 100) {   // 显示百位
    setPin(segment, 3, 4);
    setPin(segment, 2, 4);
  }
  if(pData > 9) {     //  显示十位
    n = pData % 100 / 10;
    for(i=0; i<7; i++) {
      if(num_map[n][i] == 1) {
        setPin(segment, led_map[0][i][0], led_map[0][i][1]);
      }
    }
  }
  n = pData % 10;
  for(i=0; i<7; i++) {
    if(num_map[n][i] == 1) {
      setPin(segment, led_map[1][i][0], led_map[1][i][1]);
    }
  }
	clearLed(segment); 
}

void Digital_Init(void)
{
	// 网络灯
	P0M1&=~0x08;P0M0|=0x08;//推挽输出
}

void showNetwork(const uint8_t pData)
{
	if(pData == 1) {
		P03 = 1;
	} else {
		P03 = 0;
	}
}
