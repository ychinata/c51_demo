#include "APP.h"
#include "Motor.h"

#define	Left_LED	P27
#define Right_LED	P22

// ѭ���������������߻�����û���䣬����ߵ�ƽ1������ֽ���з��䣬����͵�ƽ0��
#define	Left_Flow		P24     // �Ҳഫ����
#define	Right_Flow 	P25         // ��ഫ����

// ʵ��ѭ����Ҫ�߼�
void APP_Loop(void)
{
	if((Left_Flow==1) & (Right_Flow==1)) { // ���ջ���·�������ߣ�ֹͣ
		Motor_Stop();
		Left_LED = 1;
		Right_LED = 1;
		return;
	} if(Left_Flow==1) {    // �Ҳ�ѹ���ߣ���ƫ����Ҫ��ת
		Motor_Right();
		Left_LED = 0;
		Right_LED = 1;
		return;
	} if(Right_Flow==1) {   // ���ѹ���ߣ���ƫ�ң���Ҫ��ת
		Motor_Left();
		Left_LED = 1;
		Right_LED = 0;
		return;
	}
    // û�д�����ѹ���ߣ�С��ֱ�У����Ҳ೵��Ƴ���
	Motor_Forward();
	Left_LED = 0;
	Right_LED = 0;
}




