#include <REGX52.H>
#include "AT24C02.h"
//#include "ds1302.h"
#include "ds1302_pz.h"
#include "Delay.h"
#include "DS18B20.h"
#include "Key.h"
#include "LCD1602.h"
#include "Timer0.h"


float T,TShow;
char TLow,THigh;
unsigned char KeyNum;

unsigned char DS1302_Time[6];

/*********************
 * Func.: 时间读取及显示LCD
 * Author:普中科技
 * Date:2022.12.3
 *********************/     
void main3()
{
	LCD_Init();
	LCD_ShowString(1,1,"  -  -  ");//静态字符初始化显示
	LCD_ShowString(2,1,"  :  :  ");	
	ds1302_init();
	
	while(1) {
        
        ds1302_read_time();
        DS1302_Time[0]=gDS1302_TIME[2]/16;
        DS1302_Time[1]=gDS1302_TIME[2]&0x0f;
        DS1302_Time[2]=gDS1302_TIME[1]/16;
        DS1302_Time[3]=gDS1302_TIME[1]&0x0f;
        DS1302_Time[4]=gDS1302_TIME[0]/16;
        DS1302_Time[5]=gDS1302_TIME[0]&0x0f;     
        
		LCD_ShowNum(1,1,DS1302_Time[0],2);//显示年
		LCD_ShowNum(1,4,DS1302_Time[1],2);//显示月
		LCD_ShowNum(1,7,DS1302_Time[2],2);//显示日
		LCD_ShowNum(2,1,DS1302_Time[3],2);//显示时
		LCD_ShowNum(2,4,DS1302_Time[4],2);//显示分
		LCD_ShowNum(2,7,DS1302_Time[5],2);//显示秒
        
	}
}     

/*********************
 * Func.: 时间读取及显示
 * Author:江科大自化协
 * Date:
 *********************/
void main2()
{
	LCD_Init();
	//DS1302_Init();
	LCD_ShowString(1,1,"  -  -  ");//静态字符初始化显示
	LCD_ShowString(2,1,"  :  :  ");	
	//DS1302_SetTime();//设置时间         
	
	while(1)
	{
		//DS1302_ReadTime();//读取时间
		LCD_ShowNum(1,1,DS1302_Time[0],2);//显示年
		LCD_ShowNum(1,4,DS1302_Time[1],2);//显示月
		LCD_ShowNum(1,7,DS1302_Time[2],2);//显示日
		LCD_ShowNum(2,1,DS1302_Time[3],2);//显示时
		LCD_ShowNum(2,4,DS1302_Time[4],2);//显示分
		LCD_ShowNum(2,7,DS1302_Time[5],2);//显示秒
        
	}
}


//K1按键，THigh自增
//K2按键，THigh自减
//K3按键，TLow自增
//K4按键，TLow自减
/*********************
 * Func.: 温度读取及显示
 * Author:江科大自化协
 * Date:
 *********************/
void main()
{
    //DS1302_Init();
    ds1302_init();
    // 初始化-bgn
	DS18B20_ConvertT();		//上电先转换一次温度，防止第一次读数据错误
	Delay(1000);			//等待转换完成
	THigh=AT24C02_ReadByte(0);	//读取温度阈值数据
	TLow=AT24C02_ReadByte(1);
	if(THigh>125 || TLow<-55 || THigh<=TLow)
	{
		THigh=20;			//如果阈值非法，则设为默认值
		TLow=15;
	}
	LCD_Init();
	LCD_ShowString(1,1,"T:");
	LCD_ShowString(2,1,"TH:");
	LCD_ShowString(2,9,"TL:");
	LCD_ShowSignedNum(2,4,THigh,3);
	LCD_ShowSignedNum(2,12,TLow,3);
	Timer0_Init();
	// 初始化-end
    
	while(1)
	{
		KeyNum=Key();
		
		/*温度读取及显示*/
		DS18B20_ConvertT();	//转换温度
		T=DS18B20_ReadT();	//读取温度
		if(T<0)				//如果温度小于0
		{
			LCD_ShowChar(1,3,'-');	//显示负号
			TShow=-T;		//将温度变为正数
		}
		else				//如果温度大于等于0
		{
			LCD_ShowChar(1,3,'+');	//显示正号
			TShow=T;
		}
		LCD_ShowNum(1,4,TShow,3);		//显示温度整数部分
		LCD_ShowChar(1,7,'.');		//显示小数点
		LCD_ShowNum(1,8,(unsigned long)(TShow*100)%100,2);//显示温度小数部分
		
		/*阈值判断及显示*/
		if(KeyNum)
		{
			if(KeyNum==1)	//K1按键，THigh自增
			{
				THigh++;
				if(THigh>125){THigh=125;}
			}
			if(KeyNum==2)	//K2按键，THigh自减
			{
				THigh--;
				if(THigh<=TLow){THigh++;}
			}
			if(KeyNum==3)	//K3按键，TLow自增
			{
				TLow++;
				if(TLow>=THigh){TLow--;}
			}
			if(KeyNum==4)	//K4按键，TLow自减
			{
				TLow--;
				if(TLow<-55){TLow=-55;}
			}
			LCD_ShowSignedNum(2,4,THigh,3);	//显示阈值数据
			LCD_ShowSignedNum(2,12,TLow,3);
			AT24C02_WriteByte(0,THigh);		//写入到At24C02中保存
			Delay(5);
			AT24C02_WriteByte(1,TLow);
			Delay(5);
		}
        //越界判断
		if (T>THigh) {
			LCD_ShowString(1,13,"OV:H");
		} else if(T<TLow) {
			LCD_ShowString(1,13,"OV:L");
		} else {
			LCD_ShowString(1,13,"    ");
		}
	}
}

/*********************
 * Func.: 按键扫描中断
 * Author:江科大自化协
 * Date:
 *********************/
void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	if(T0Count>=20)
	{
		T0Count=0;
		Key_Loop();	//每20ms调用一次按键驱动函数
	}
}
