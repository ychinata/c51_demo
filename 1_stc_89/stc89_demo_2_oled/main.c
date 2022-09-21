#include <REGX52.H>
#include <INTRINS.H>
#include "oled.h"
//#include "bmp.h"
// reviewed:2022.9.13

void OLED_DemoByITLaozhai();
//void OLED_DemoHelloWorld();
void OLED_DemoFontSize16();

//////////////////////////////////////////////////////////////////////////////////	 
//  ��    ��   : oldZhai
//  ��������   : AT89C51 ����0.96OLED I2C�ӿ���Ļ��ʾ
//              ˵��: 
//              ----------------------------------------------------------------
//              GND    ��Դ��
//              VCC  ��5V��3.3v��Դ
//              D0   P1^0��SCL��
//              D1   P1^1��SDA��      
//							��Ҫ�޸Ĺܽŵ���oled.h���޸�
//              ----------------------------------------------------------------
//https://blog.csdn.net/weixin_45631738/article/details/113703749
//******************************************************************************/
 int main(void)
 {	
    OLED_Init();			//��ʼ��OLED  
    //��ʾͼƬ
    //OLED_DrawBMP(0,0,128,8,BMP1);  //ͼƬ��ʾ(ͼƬ��ʾ���ã����ɵ��ֱ�ϴ󣬻�ռ�ý϶�ռ䣬FLASH�ռ�8K��������)
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
    int charSize = 16; // ������4��
    // 0��0������16
    OLED_ShowString(0,0,"Helloworld!",charSize);
    OLED_ShowString(0,2,"MyFirstOLEDProg",charSize);
    OLED_ShowString(0,4,"BySTC12C5A60S2",charSize);
    OLED_ShowString(0,6,"2022.09.13",charSize);
}

// ��ʾASCII��
// OLED�Ĺ�겻�ǰ����м������ģ��������Ƚ��鷳
void OLED_DemoByITLaozhai()
{
    static u8 t = ' ';
    // t=' ';
    OLED_ShowString(0,0,"I T",16); 
    OLED_ShowCHinese(30,0,0);//��
    OLED_ShowCHinese(48,0,1);//��

    OLED_ShowString(0,3,"0.96' OLED",16);
    OLED_ShowString(0,6,"ASCII:",16);  
    OLED_ShowString(63,6,"CODE:",16);  
    OLED_ShowChar(48,6,t,16);//��ʾASCII�ַ�	   
    t++;
    if(t>'~'){
        t=' ';
    }
    OLED_ShowNum(103,6,t,3,16);//��ʾASCII�ַ�����ֵ 	
    Delay_1ms(10);    
}

