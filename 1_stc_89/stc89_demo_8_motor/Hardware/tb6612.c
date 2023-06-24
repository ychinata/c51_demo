// 2023.6.24 �ݲ����Բ�ʹ��
//http://www.51hei.com/bbs/dpj-188001-1.html
#include <reg51.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
unsigned char tmp;
unsigned int c=0;
uint Count;
uint Degree=50;
sbit PWMA=P2^0;
sbit AIN2=P2^1;
sbit AIN1=P2^2;         
sbit STBY=P2^3;
sbit BIN1=P2^4;
sbit BIN2=P2^5;
sbit PWMB=P2^6;
sbit beep=P2^7;                        //������
void init();   //���ڳ�ʼ��
void send(unsigned char a);        //���ֽڷ��ͺ���
void ctrl(); //���մ�����

void delay(unsigned int x)
{
        unsigned int i,j;
        for(i=x;i>0;i--)
                for(j=110;j>0;j--);
}

void Initialize_time(void)
{        
    EA=1;
    ET0=1;                                       //EA=1;ET0=1���������жϡ���ʱ��0
    //    TMOD=0x22;                               //M1=1,M1=0;��ʽ2
    TH0 = 0XA3;                                   //��ʱʱ��Ϊ100us     
    TL0 = 0XA3;                                                                                          
    TR0=1;                         //������ʱ��0����ʼ����
}

void timer0 (void) interrupt 1            //��ʱ�ж�0�ӳ���
{                                                                                                                                                                                      
    Count++;        
    if(Count>=0 && Count<=Degree)
    {
        PWMA=0;
        PWMB=0;
    } else{
        PWMA=1;
        PWMB=1;
    }
    if(Count==200)        
        Count=0;                                                                                               
}

void init()        //���ڳ�ʼ��
{
    ES=0;                                //���ж�
    SCON = 0x50;                        // REN=1�����н���״̬�����ڹ���ģʽ1,
    //10λUART��1λ��ʼλ��8λ����λ��1λֹͣλ������żУ�飩�������ʿ�
    TMOD = 0x22;                      // ��ʱ��1�����ڷ�ʽ2��8λ�Զ�����ģʽ, ���ڲ���������
    TH1=TL1=0xFD;                   // ������9600 �����β��Բ��þ���Ϊ11.0592��

    PCON &= 0x7f;                          // �����ʲ�����
    TR1 = 1;                            //��ʱ��1��ʼ����������������
    //���ͱ�־λ��0
    TI=0;                               //���ձ�־λ��0
    RI=0;
    PT1=1;
    ES=1;

}

void send(unsigned char a)        //���ֽ����ݷ���
{                                //ע�⣺����Ƭ��TXD��P3.1��������������������P3.1�˽��������衣���β�����Ҫ����������
        TI=0;        
        SBUF=a;
        while(TI==0);
        TI=0;

}

void ctrl()                            //���մ�����
{
    switch(tmp)
    {
        case '1':
        {
            AIN1=1;
            AIN2=0;        
            BIN1=1;
            BIN2=0;               
            PWMA=1;
            PWMB=1;
            send(tmp);


            break;        
        }          
        
        case '8':
        {                                         
            PWMA=0;
            PWMB=0;
            send(tmp);
        }

        break;        

        case '3':
        {                                         
            AIN1=0;
            AIN2=0;        
            BIN1=1;
            BIN2=0;               
            PWMA=1;
            PWMB=1;
            send(tmp);
        }        
        break;        
        case '4':
        {                                         
            AIN1=1;
            AIN2=0;        
            BIN1=0;
            BIN2=0;               
            PWMA=1;
            PWMB=1;
            send(tmp);
        }         
        break;
        
        case '5':
        {                                         
            AIN1=0;
            AIN2=1;        
            BIN1=0;
            BIN2=1;               
            PWMA=1;
            PWMB=1;
            send(tmp);
        }        
        break;    
        
        case '6':
        {                                         
            beep=0;
            delay(50);
            beep=1;
            send(tmp);
        }
        break;        
        
        case '7':
        {                                         
            Degree++;
            if(Degree==180)
            {
                Degree=0;
            }
            send(tmp);
        }
        break;                                                        

    }
}

//void main()                                                   
//{                 
//    PWMA=1;
//    PWMB=1;
//    STBY=1;
//    init();
//    //             Initialize_time();
//    while(1)
//    {               
//        if(RI==1)                     // �Ƿ������ݵ���
//        {
//            RI = 0;
//            tmp = SBUF;                   // �ݴ���յ�������
//            ctrl();
//        }      
//    }
//}
