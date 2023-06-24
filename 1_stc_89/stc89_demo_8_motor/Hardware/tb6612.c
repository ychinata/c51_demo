// 2023.6.24 暂不调试不使用
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
sbit beep=P2^7;                        //蜂鸣器
void init();   //串口初始化
void send(unsigned char a);        //单字节发送函数
void ctrl(); //接收处理函数

void delay(unsigned int x)
{
        unsigned int i,j;
        for(i=x;i>0;i--)
                for(j=110;j>0;j--);
}

void Initialize_time(void)
{        
    EA=1;
    ET0=1;                                       //EA=1;ET0=1；开启总中断、定时器0
    //    TMOD=0x22;                               //M1=1,M1=0;方式2
    TH0 = 0XA3;                                   //定时时间为100us     
    TL0 = 0XA3;                                                                                          
    TR0=1;                         //启动定时器0，开始计数
}

void timer0 (void) interrupt 1            //定时中断0子程序
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

void init()        //串口初始化
{
    ES=0;                                //关中断
    SCON = 0x50;                        // REN=1允许串行接受状态，串口工作模式1,
    //10位UART（1位起始位，8位数据位，1位停止位，无奇偶校验），波特率可
    TMOD = 0x22;                      // 定时器1工作于方式2，8位自动重载模式, 用于产生波特率
    TH1=TL1=0xFD;                   // 波特率9600 （本次测试采用晶振为11.0592）

    PCON &= 0x7f;                          // 波特率不倍增
    TR1 = 1;                            //定时器1开始工作，产生波特率
    //发送标志位置0
    TI=0;                               //接收标志位置0
    RI=0;
    PT1=1;
    ES=1;

}

void send(unsigned char a)        //单字节数据发送
{                                //注意：若单片机TXD（P3.1）无上拉能力，必须在P3.1端接上拉电阻。本次测试需要接上拉电阻
        TI=0;        
        SBUF=a;
        while(TI==0);
        TI=0;

}

void ctrl()                            //接收处理函数
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
//        if(RI==1)                     // 是否有数据到来
//        {
//            RI = 0;
//            tmp = SBUF;                   // 暂存接收到的数据
//            ctrl();
//        }      
//    }
//}
