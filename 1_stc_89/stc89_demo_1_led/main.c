#include <REGX52.H>

// ����
void Delay1ms(unsigned int xms);


void main()
{
    while(1) {
        P2 = 0xFF;	//����,ȫ��
        Delay1ms(500);
        P2 = 0x00;  // ����,ȫ��
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
