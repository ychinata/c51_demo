#include "typedef.h"

void delay_1ms(uint16 c){  //��ʱ��������������

	uchar8 a,b;
	for(c;c>0;c--)
	{ 
		for(b=199;b>0;b--) 
		{ 
			for(a=1;a>0;a--);
		}
	}
}

void delay(uint16 i)   //�Լ���ʱ������10usһ��
{
    while(i--);
}
