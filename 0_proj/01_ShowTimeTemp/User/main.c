/**************************************************************************************
���������пƼ����޹�˾��PRECHIN ���У�
����֧�֣�www.prechin.net
PRECHIN
 ����

ʵ�����ƣ�DS1302ʱ��ʵ��
����˵����	
ʵ���������س�������������ʾ����ʱ��ʱ���룬��ʽΪ��XX-XX-XX��
ע�����																				  
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
* �� �� ��       : main
* ��������		 : ������
* ��    ��       : ��
* ��    ��    	 : ��
*******************************************************************************/

void main1()
{	
    u8 i=0;
//  int temp_value;
//	u8 temp_buf[5];
    
	// ��ʼ��
	ds1302_init();//��ʼ��DS1302 // ͬʱ��ʼ�����������¶Ⱦ���ʾ����
    ds18b20_init();//��ʼ��DS18B20
        //Delay_ms(5000);
	while(1) {
        i++;        
        //DS1302_ShowTime();
        //smg_display(g_time_buf,1);
        DS18B20_ShowTemp(i);        
        smg_display(g_tmp,1); // �ŵ�DS18B20_ShowTemp�������0?
        //˼·1����������ֵ
        //˼·2�����ϵ�showtemp������
        //˼·3��ȫ������while��ѭ����-����
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
    
    //Ϊ�����ⲿ��ʾ�����
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
        //���һ��ʱ���ȡ�¶�ֵ�����ʱ��Ҫ�����¶ȴ�����ת���¶�ʱ��
		if(i%50==0)
            //Delay_ms(5);
			temp_value=ds18b20_read_temperture()*10;//�����¶�ֵС����һλ
        //���¶�
		if(temp_value<0) {
			temp_value =- temp_value;
			g_temp_buf[0]=0x40;//��ʾ����	
		} else {
            g_temp_buf[0]=0x00;//����ʾ
        }
		
//		g_temp_buf[1] = gsmg_code[temp_value/1000];//��λ
//		g_temp_buf[2] = gsmg_code[temp_value%1000/100];//ʮλ
//		g_temp_buf[3] = gsmg_code[temp_value%1000%100/10]|0x80;//��λ+С����
//		g_temp_buf[4] = gsmg_code[temp_value%1000%100%10];//С�����һλ
     
        //smg_display(g_temp_buf,4);
        
        //��ʱ����
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

		
    if(i%50==0)//���һ��ʱ���ȡ�¶�ֵ�����ʱ��Ҫ�����¶ȴ�����ת���¶�ʱ��
        temp_value=ds18b20_read_temperture()*10;//�����¶�ֵС����һλ
    //���¶�
    if(temp_value<0) {
        temp_value=-temp_value;
        temp_buf[0]=0x40;//��ʾ����	
    } else {
        temp_buf[0]=0x00;//����ʾ
    }
    
    *tmp_buf = temp_buf[1]=gsmg_code[temp_value/1000];//��λ
    *(tmp_buf+1) = temp_buf[2]=gsmg_code[temp_value%1000/100];//ʮλ
    *(tmp_buf+2) = temp_buf[3]=gsmg_code[temp_value%1000%100/10]|0x80;//��λ+С����
    *(tmp_buf+3) = temp_buf[4]=gsmg_code[temp_value%1000%100%10];//С�����һλ

}


// 20221202.ʧ�ܣ���4λ�������ʾ�¶�(������ˢ��)����4λ�������ʾ������������OLED����?
void main()
{	
	u8 i=0;
	u8 temp_buf[5];

	ds18b20_init();//��ʼ��DS18B20
    ds1302_init();

	while(1) {				
		i++;
        DS18B20_GetBuf(i, &temp_buf);
        g_tmp[0] = temp_buf[0];
        g_tmp[1] = temp_buf[1];
        g_tmp[2] = temp_buf[2];
        g_tmp[3] = temp_buf[3];

        //����¶ȵ�buf
        DS1302_ShowTime();
        // ��ʾ8λ�����
        smg_display(g_tmp,1);
	}		
}

// 20221202.�ɹ�����4λ�������ʾ�¶ȣ���4λ�������ʾ��
void main_s2()
{	
	u8 i=0;
   	int temp_value;
	u8 temp_buf[5];

	ds18b20_init();//��ʼ��DS18B20
    ds1302_init();

	while(1) {				
		i++;
		if(i%50==0)//���һ��ʱ���ȡ�¶�ֵ�����ʱ��Ҫ�����¶ȴ�����ת���¶�ʱ��
			temp_value=ds18b20_read_temperture()*10;//�����¶�ֵС����һλ
        //���¶�
		if(temp_value<0) {
			temp_value=-temp_value;
			temp_buf[0]=0x40;//��ʾ����	
		} else {
            temp_buf[0]=0x00;//����ʾ
        }
		
		g_tmp[0] = temp_buf[1]=gsmg_code[temp_value/1000];//��λ
		g_tmp[1] = temp_buf[2]=gsmg_code[temp_value%1000/100];//ʮλ
		g_tmp[2] = temp_buf[3]=gsmg_code[temp_value%1000%100/10]|0x80;//��λ+С����
		g_tmp[3] = temp_buf[4]=gsmg_code[temp_value%1000%100%10];//С�����һλ
		//smg_display(temp_buf,1);
        
        //����¶ȵ�buf
        DS1302_ShowTime();
        
        smg_display(g_tmp,1);
	}		
}


// 20221202.�ɹ�����4λ�������ʾ�¶ȣ���4λ�������ʾ��
void main_s1()
{	
	u8 i=0;
   	int temp_value;
	u8 temp_buf[5];

	ds18b20_init();//��ʼ��DS18B20
    ds1302_init();

	while(1) {				
		i++;
		if(i%50==0)//���һ��ʱ���ȡ�¶�ֵ�����ʱ��Ҫ�����¶ȴ�����ת���¶�ʱ��
			temp_value=ds18b20_read_temperture()*10;//�����¶�ֵС����һλ
        //���¶�
		if(temp_value<0) {
			temp_value=-temp_value;
			temp_buf[0]=0x40;//��ʾ����	
		} else {
            temp_buf[0]=0x00;//����ʾ
        }
		
		g_tmp[0] = temp_buf[1]=gsmg_code[temp_value/1000];//��λ
		g_tmp[1] = temp_buf[2]=gsmg_code[temp_value%1000/100];//ʮλ
		g_tmp[2] = temp_buf[3]=gsmg_code[temp_value%1000%100/10]|0x80;//��λ+С����
		g_tmp[3] = temp_buf[4]=gsmg_code[temp_value%1000%100%10];//С�����һλ
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

