//΢�Ź��ںţ�����������
#include "ProgramLogic.h"
#include "SYS_LOOP.h"
#include "APP.h"
#include "PWM.h"

void ProgramLogic_Main(void)
{
	PWM_Init();
	PWM_Set_ZhanKongBi(20); //����ռ�ձ�
	SYS_New_LoopFun(2,APP_Loop);
}

//

