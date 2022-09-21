#include <REGX52.H>
#include <INTRINS.H>
#include "oled.h"
//#include "bmp.h"
// reviewed:2022.9.13

void OLED_DemoByITLaozhai();
//void OLED_DemoHelloWorld();
void OLED_DemoFontSize16();

//////////////////////////////////////////////////////////////////////////////////	 
//  作    者   : oldZhai
//  功能描述   : AT89C51 驱动0.96OLED I2C接口屏幕显示
//              说明: 
//              ----------------------------------------------------------------
//              GND    电源地
//              VCC  接5V或3.3v电源
//              D0   P1^0（SCL）
//              D1   P1^1（SDA）      
//							需要修改管脚的在oled.h中修改
//              ----------------------------------------------------------------
//https://blog.csdn.net/weixin_45631738/article/details/113703749
//******************************************************************************/
 int main(void)
 {	
    OLED_Init();			//初始化OLED  
    //显示图片
    //OLED_DrawBMP(0,0,128,8,BMP1);  //图片显示(图片显示慎用，生成的字表较大，会占用较多空间，FLASH空间8K以下慎用)
    Delay_1ms(2000);
    OLED_Clear();
	 
    while(1) {		
        OLED_DemoFontSize16();
    }	  
}

// 2022.9.13
void OLED_DemoFontSize1()
{
    OLED_ShowString(0,0,"a",1);
    OLED_ShowString(8,0,"a",1);
    OLED_ShowString(0,1,"b",1); 
    OLED_ShowString(0,2,"c",1);
    OLED_ShowString(0,3,"d",1);
}

void OLED_DemoFontSize16()
{
    int charSize = 16; // 可排列4行
    // 0列0行字体16
    OLED_ShowString(0,0,"Helloworld!",charSize);
    OLED_ShowString(0,2,"MyFirstOLEDProg",charSize);
    OLED_ShowString(0,4,"BySTC12C5A60S2",charSize);
    OLED_ShowString(0,6,"2022.09.13",charSize);
}

// 显示ASCII码
// OLED的光标不是按几行几列来的，用起来比较麻烦
void OLED_DemoByITLaozhai()
{
    static u8 t = ' ';
    // t=' ';
    OLED_ShowString(0,0,"I T",16); 
    OLED_ShowCHinese(30,0,0);//老
    OLED_ShowCHinese(48,0,1);//翟

    OLED_ShowString(0,3,"0.96' OLED",16);
    OLED_ShowString(0,6,"ASCII:",16);  
    OLED_ShowString(63,6,"CODE:",16);  
    OLED_ShowChar(48,6,t,16);//显示ASCII字符	   
    t++;
    if(t>'~'){
        t=' ';
    }
    OLED_ShowNum(103,6,t,3,16);//显示ASCII字符的码值 	
    Delay_1ms(10);    
}

