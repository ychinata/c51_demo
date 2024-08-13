//微信公众号：物联网零妖
#include "ProgramLogic.h"
#include "SYS_LOOP.h"
#include "Motor.h"

void Motor_Drive(void)
{
	static unsigned char i=0;
	
	if(i > 8) {
		i = 0;
	}
	i++;
	switch(i){
		case 1:{Motor_Stop();break;}
		case 2:{Motor_Forward();break;}
        case 3:{Motor_Stop();break;}
        case 4:{Motor_Left();break;}
        case 5:{Motor_Stop();break;}
		case 6:{Motor_Back();break;}
		case 7:{Motor_Stop();break;}
		case 8:{Motor_Right();break;}
		default:{Motor_Stop();break;}        
	}
	
	
}

void ProgramLogic_Main(void)
{
	SYS_New_LoopFun(1000,Motor_Drive);
    //SYS_New_LoopFun(1000,Motor_Right); //ok
}

//

