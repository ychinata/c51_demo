/**************************************************************************************
深圳市普中科技有限公司（PRECHIN 普中）
技术支持：www.prechin.net
PRECHIN
 普中

实验名称：DS1302时钟实验
接线说明：	
实验现象：下载程序后，数码管上显示电子时钟时分秒，格式为“XX-XX-XX”
注意事项：																				  
***************************************************************************************/
#include "public.h"
#include "smg.h"
#include "ds1302.h"
#include "ds18b20.h"
#include "delay.h"


u8 g_time_buf[8];
u8 g_temp_buf[8];
u8 g_tmp[8];// = {1,1,1,1,1};

void DS1302_ShowTime(void);
void DS18B20_ShowTemp(u8 i);

/*******************************************************************************
* 函 数 名       : main
* 函数功能		 : 主函数
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/

void main1()
{	
    u8 i=0;
//  int temp_value;
//	u8 temp_buf[5];
    
	// 初始化
	ds1302_init();//初始化DS1302 // 同时初始化这两个，温度就显示不了
    ds18b20_init();//初始化DS18B20
        //Delay_ms(5000);
	while(1) {
        i++;        
        //DS1302_ShowTime();
        //smg_display(g_time_buf,1);
        DS18B20_ShowTemp(i);        
        smg_display(g_tmp,1); // 放到DS18B20_ShowTemp外面会变成0?
        //思路1，保存两个值
        //思路2，整合到showtemp函数中
        //思路3，全部放在while大循环里-可行
	}		
}


void DS1302_ShowTime(void)
{
    ds1302_read_time();
    g_time_buf[0]=gsmg_code[gDS1302_TIME[2]/16];
    g_time_buf[1]=gsmg_code[gDS1302_TIME[2]&0x0f];
    g_time_buf[2]=0x40;
    g_time_buf[3]=gsmg_code[gDS1302_TIME[1]/16];
    g_time_buf[4]=gsmg_code[gDS1302_TIME[1]&0x0f];
    g_time_buf[5]=0x40;
    g_time_buf[6]=gsmg_code[gDS1302_TIME[0]/16];
    g_time_buf[7]=gsmg_code[gDS1302_TIME[0]&0x0f];
    
    //为了在外部显示数码管
    g_tmp[4] = g_time_buf[4]=gsmg_code[gDS1302_TIME[1]&0x0f];
    g_tmp[5] = g_time_buf[5]=0x40;
    g_tmp[6] = g_time_buf[6]=gsmg_code[gDS1302_TIME[0]/16];
    g_tmp[7] = g_time_buf[7]=gsmg_code[gDS1302_TIME[0]&0x0f];       
    
    //smg_display(g_time_buf,1);
}

void DS18B20_ShowTemp(u8 i)
{
	//u8 i=0;
   	int temp_value;

	//while(1) {				
		//i++;
        //间隔一段时间读取温度值，间隔时间要大于温度传感器转换温度时间
		if(i%50==0)
            //Delay_ms(5);
			temp_value=ds18b20_read_temperture()*10;//保留温度值小数后一位
        //负温度
		if(temp_value<0) {
			temp_value =- temp_value;
			g_temp_buf[0]=0x40;//显示负号	
		} else {
            g_temp_buf[0]=0x00;//不显示
        }
		
//		g_temp_buf[1] = gsmg_code[temp_value/1000];//百位
//		g_temp_buf[2] = gsmg_code[temp_value%1000/100];//十位
//		g_temp_buf[3] = gsmg_code[temp_value%1000%100/10]|0x80;//个位+小数点
//		g_temp_buf[4] = gsmg_code[temp_value%1000%100%10];//小数点后一位
     
        //smg_display(g_temp_buf,4);
        
        //临时测试
//        g_time_buf[0] = g_temp_buf[1];
//        g_time_buf[1] = g_temp_buf[2];
//        g_time_buf[2] = g_temp_buf[3];
//        g_time_buf[3] = g_temp_buf[4];
        

	//}	
}


void DS18B20_GetBuf(u8 i, u8* tmp_buf)
{	
	//u8 i=0;
   	int temp_value;
	u8 temp_buf[5];

		
    if(i%50==0)//间隔一段时间读取温度值，间隔时间要大于温度传感器转换温度时间
        temp_value=ds18b20_read_temperture()*10;//保留温度值小数后一位
    //负温度
    if(temp_value<0) {
        temp_value=-temp_value;
        temp_buf[0]=0x40;//显示负号	
    } else {
        temp_buf[0]=0x00;//不显示
    }
    
    *tmp_buf = temp_buf[1]=gsmg_code[temp_value/1000];//百位
    *(tmp_buf+1) = temp_buf[2]=gsmg_code[temp_value%1000/100];//十位
    *(tmp_buf+2) = temp_buf[3]=gsmg_code[temp_value%1000%100/10]|0x80;//个位+小数点
    *(tmp_buf+3) = temp_buf[4]=gsmg_code[temp_value%1000%100%10];//小数点后一位

}


// 20221202.失败：左4位数码管显示温度(但不会刷新)，右4位数码管显示秒正常：换成OLED试下?
void main()
{	
	u8 i=0;
	u8 temp_buf[5];

	ds18b20_init();//初始化DS18B20
    ds1302_init();

	while(1) {				
		i++;
        DS18B20_GetBuf(i, &temp_buf);
        g_tmp[0] = temp_buf[0];
        g_tmp[1] = temp_buf[1];
        g_tmp[2] = temp_buf[2];
        g_tmp[3] = temp_buf[3];

        //填充温度到buf
        DS1302_ShowTime();
        // 显示8位数码管
        smg_display(g_tmp,1);
	}		
}

// 20221202.成功：左4位数码管显示温度，右4位数码管显示秒
void main_s2()
{	
	u8 i=0;
   	int temp_value;
	u8 temp_buf[5];

	ds18b20_init();//初始化DS18B20
    ds1302_init();

	while(1) {				
		i++;
		if(i%50==0)//间隔一段时间读取温度值，间隔时间要大于温度传感器转换温度时间
			temp_value=ds18b20_read_temperture()*10;//保留温度值小数后一位
        //负温度
		if(temp_value<0) {
			temp_value=-temp_value;
			temp_buf[0]=0x40;//显示负号	
		} else {
            temp_buf[0]=0x00;//不显示
        }
		
		g_tmp[0] = temp_buf[1]=gsmg_code[temp_value/1000];//百位
		g_tmp[1] = temp_buf[2]=gsmg_code[temp_value%1000/100];//十位
		g_tmp[2] = temp_buf[3]=gsmg_code[temp_value%1000%100/10]|0x80;//个位+小数点
		g_tmp[3] = temp_buf[4]=gsmg_code[temp_value%1000%100%10];//小数点后一位
		//smg_display(temp_buf,1);
        
        //填充温度到buf
        DS1302_ShowTime();
        
        smg_display(g_tmp,1);
	}		
}


// 20221202.成功：左4位数码管显示温度，右4位数码管显示秒
void main_s1()
{	
	u8 i=0;
   	int temp_value;
	u8 temp_buf[5];

	ds18b20_init();//初始化DS18B20
    ds1302_init();

	while(1) {				
		i++;
		if(i%50==0)//间隔一段时间读取温度值，间隔时间要大于温度传感器转换温度时间
			temp_value=ds18b20_read_temperture()*10;//保留温度值小数后一位
        //负温度
		if(temp_value<0) {
			temp_value=-temp_value;
			temp_buf[0]=0x40;//显示负号	
		} else {
            temp_buf[0]=0x00;//不显示
        }
		
		g_tmp[0] = temp_buf[1]=gsmg_code[temp_value/1000];//百位
		g_tmp[1] = temp_buf[2]=gsmg_code[temp_value%1000/100];//十位
		g_tmp[2] = temp_buf[3]=gsmg_code[temp_value%1000%100/10]|0x80;//个位+小数点
		g_tmp[3] = temp_buf[4]=gsmg_code[temp_value%1000%100%10];//小数点后一位
		//smg_display(temp_buf,1);
        
        ds1302_read_time();
        g_time_buf[0]=gsmg_code[gDS1302_TIME[2]/16];
        g_time_buf[1]=gsmg_code[gDS1302_TIME[2]&0x0f];
        g_time_buf[2]=0x40;
        g_time_buf[3]=gsmg_code[gDS1302_TIME[1]/16];
        g_tmp[4] = g_time_buf[4]=gsmg_code[gDS1302_TIME[1]&0x0f];
        g_tmp[5] = g_time_buf[5]=0x40;
        g_tmp[6] = g_time_buf[6]=gsmg_code[gDS1302_TIME[0]/16];
        g_tmp[7] = g_time_buf[7]=gsmg_code[gDS1302_TIME[0]&0x0f];        
        
        smg_display(g_tmp,1);
	}		
}

