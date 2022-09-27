#include <REGX52.H>

// 声明
void Delay1ms(unsigned int xms);


void main()
{
    while(1) {
        P2 = 0xFF;	//共阳,全灭
        Delay1ms(500);
        P2 = 0x00;  // 共阳,全亮
        Delay1ms(500);
	}
}

void Delay1ms(unsigned int xms)		//@12.000MHz
{
	unsigned char i, j;
	while(xms) {
		i = 2;
		j = 239;
		do {
			while (--j);
		} while (--i);
		xms--;
	}
}
