//΢�Ź��ںţ�����������
//PWM������� Timer0 ���2kHZ�Ĳ��Σ�ռ�ձ� 0~100% �ɵ�
#include<PWM.h>


#define LF_A_IO P02//��ǰ���A
#define LF_B_IO P03//��ǰ���B
#define LB_A_IO P01//�����A
#define LB_B_IO P00//�����B

#define RF_A_IO P05//��ǰ���A
#define RF_B_IO P04//��ǰ���B
#define RB_A_IO P06//�Һ���A
#define RB_B_IO P07//�Һ���B

extern unsigned char LF_A,LF_B,LB_A,LB_B,RF_A,RF_B,RB_A,RB_B;
static unsigned int PWM_H=0,PWM_L=0;//�ߵ�ƽʱ��͵͵�ƽʱ��
static unsigned char PWM_IO_1=0;

//��ʼ��PWM��ʱ��
void PWM_Init(void)
{
	PWM_H = 0;
	PWM_L = 0;
	
	//��ʱ��0����
	TMOD |= 0x01;//���ö�ʱ��ģʽ
  TL0 = 0;//���ö�ʱ��ֵ
	TH0 = 0;//���ö�ʱ��ֵ
	TF0 = 0;//���TF0��־
  ET0 = 1;//ʹ�ܶ�ʱ���ж�
	
	LF_A_IO=0;
	LF_B_IO=0;
	LB_A_IO=0;
	LB_B_IO=0;
	RF_A_IO=0;
	RF_B_IO=0;
	RB_A_IO=0;
	RB_B_IO=0;
	
	PWM_IO_1=0;
	
}
//����ռ�ձ�
void PWM_Set_ZhanKongBi(unsigned char a)
{
	float ZhanKongBi;
	ZhanKongBi = 100 - a;
	
	if(a<2) {       // ������ռ�ձ�<2����С������������Ҫ������ʱ��
		LF_A_IO=0;
		LF_B_IO=0;
		LB_A_IO=0;
		LB_B_IO=0;
		RF_A_IO=0;
		RF_B_IO=0;
		RB_A_IO=0;
		RB_B_IO=0;
		PWM_IO_1=0;
		TR0 = 0;
	} else if(a>98) {   // ������ռ�ձ�>98����С��ȫ�٣���Ҫ������ʱ��
		LF_A_IO=1;
		LF_B_IO=1;
		LB_A_IO=1;
		LB_B_IO=1;
		RF_A_IO=1;
		RF_B_IO=1;
		RB_A_IO=1;
		RB_B_IO=1;
		PWM_IO_1=1;
		TR0 = 0;
	} else {            // ������ռ�ձ��������̣���Ҫ������ʱ��
		ZhanKongBi = 10000 * ZhanKongBi / 100 ;
		PWM_H = 0XFFFF - ZhanKongBi;
		PWM_L = 0XFFFF - 10000 + ZhanKongBi;
		TR0 = 1;
	}
}

// PWM��ʱ���ж���Ӧ����
void TM0_Isr(void) interrupt 1
{
    // PWM_IO_1��ʼ��Ϊ0���Ƚ���else��֧������IO����ʱ������ʱ������������if��֧������IO����ʱ����������PWM���Ʋ�����ϸ��
	if(PWM_IO_1)
	{
		LF_A_IO=0;
		LF_B_IO=0;
		LB_A_IO=0;
		LB_B_IO=0;
		RF_A_IO=0;
		RF_B_IO=0;
		RB_A_IO=0;
		RB_B_IO=0;
		PWM_IO_1=0;
		TL0 = PWM_H;
		TH0 = PWM_H>>8;
	} else {
		if(LF_A)    // �ĸ����Ӷ�Ӧ��8��IO�ڣ��ĸ�������Ϊ1���ͽ���ռ�ձ�����
			LF_A_IO=1;
		if(LF_B)
			LF_B_IO=1;
		if(LB_A)
			LB_A_IO=1;
		if(LB_B)
			LB_B_IO=1;
		if(RF_A)
			RF_A_IO=1;
		if(RF_B)
			RF_B_IO=1;
		if(RB_A)
			RB_A_IO=1;
		if(RB_B)
			RB_B_IO=1;
		PWM_IO_1=1;
		TL0 = PWM_L;
		TH0 = PWM_L>>8;
	}
}
