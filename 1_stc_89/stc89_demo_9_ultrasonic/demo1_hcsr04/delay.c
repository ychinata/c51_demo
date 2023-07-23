#include "delay.h"
#include <INTRINS.H> 

void DELAY_ms(unsigned int xms)
{
	unsigned char i, j;
	while(xms--)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}
}

void DELAY_12us(void)		//STC12Cxx @11.0592MHz
{
	unsigned char i;

	//_nop_();
	i = 50; //30
	while (--i);
}


//void DELAY_ms(unsigned int k)   //延时1ms函数，k等于多少就延时多少ms
//{
//    unsigned int a,b,c,d;
//	for(d=0;d<k;d++)
//        for(c=1;c>0;c--)
//            for(b=50;b>0;b--)
//                for(a=2;a>0;a--);
//}	
