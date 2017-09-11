#include "stepmotor_core.h"
#include "stepmotor_dev.h"
#include "delay.h"

//#define MOTOR_ONE_CLKPIN PAout(1)
#define MOTOR_ONE_CWPIN PAout(4)

//#define MOTOR_TWO_CLKPIN PAout(7)
#define MOTOR_TWO_CWPIN PAout(6)

//#define MOTOR_THR_CLKPIN PAout(8)
#define MOTOR_THR_CWPIN PAout(11)


#define MOTOR_ONE_CLKH MOTOR_ONE_CLKPIN=1
#define MOTOR_ONE_CLKL MOTOR_ONE_CLKPIN=0
#define MOTOR_ONE_CLKT MOTOR_ONE_CLKPIN=!MOTOR_ONE_CLKPIN
#define MOTOR_ONE_CWH MOTOR_ONE_CWPIN=1
#define MOTOR_ONE_CWL MOTOR_ONE_CWPIN=0

#define MOTOR_TWO_CLKH MOTOR_TWO_CLKPIN=1
#define MOTOR_TWO_CLKL MOTOR_TWO_CLKPIN=0
#define MOTOR_TWO_CLKT MOTOR_TWO_CLKPIN=!MOTOR_TWO_CLKPIN
#define MOTOR_TWO_CWH MOTOR_TWO_CWPIN=1
#define MOTOR_TWO_CWL MOTOR_TWO_CWPIN=0

#define MOTOR_THR_CLKH MOTOR_THR_CLKPIN=1
#define MOTOR_THR_CLKL MOTOR_THR_CLKPIN=0
#define MOTOR_THR_CLKT MOTOR_THR_CLKPIN=!MOTOR_THR_CLKPIN
#define MOTOR_THR_CWH MOTOR_THR_CWPIN=1
#define MOTOR_THR_CWL MOTOR_THR_CWPIN=0

//#define MINFrequency 200        //最小频率  110HZ
//#define MAXFrequency 100000    //最大频率   7200Khz
//#define ADTIMELADDERNUM 10					//加减速阶梯数


MOTORINFO_Type Motor_one={
	2,
	200,
	100000,
	10,
	(APB1_CLK/TIME2_ARR),
	0,0,
	8,
	CW,OFF,
	800,
};


MOTORINFO_Type Motor_two={
	3,
	200,
	100000,
	10,
	(APB1_CLK/TIME3_ARR),
	0,0,
	8,
	CW,OFF,
	800,
};
MOTORINFO_Type Motor_thr={
	4,
	200,
	100000,
	10,
	(APB1_CLK/TIME4_ARR),
	0,0,
	8,
	CW,OFF,
	300,
};


void stepMotorInit(void)
{
	timer_init();
	ctrlGPIO_Init();
}
void stepMotorRun(void)
{
//	DRVA(&Motor_one,2*200,1000);
//	pluseStart(&Motor_one);
//	PAUSE(&Motor_one);
//	delay_ms(1000);
//	DRVA(&Motor_one,0,1650);
//	pluseStart(&Motor_one);
//	PAUSE(&Motor_one);
//	delay_ms(1000);
		DRVI(&Motor_one,2*200,1000);
		pluseStart(&Motor_one);
		PAUSE(&Motor_one);
		delay_ms(500);
		DRVI(&Motor_one,-2*200,1000);
		pluseStart(&Motor_one);
		PAUSE(&Motor_one);
		delay_ms(500);
}
void setSlope(u8 n,u16 atime)
{
	switch(n)
	{
		case 2:
			Motor_one.accelerateTime=atime;
			break;
		case 3:
			Motor_two.accelerateTime=atime;
			break;
		case 4:
			Motor_thr.accelerateTime=atime;
			break;
	}
}

void setPSC(u8 n,u16 psc)
{
	switch(n)
	{
		case 2:
			TIM2->PSC=psc;
			break;
		case 3:
			TIM3->PSC=psc;
			break;
		case 4:
			TIM4->PSC=psc;
			break;
	}
}

void setDir(u8 n,DIR_Type m)
{
	switch(n)
	{
		case 2:
			if(m == CW) MOTOR_ONE_CWH;
			else MOTOR_ONE_CWL;
			break;
		case 3:
			if(m == CW) MOTOR_TWO_CWH;
			else MOTOR_TWO_CWL;
			break;
		case 4:
			if(m == CW) MOTOR_THR_CWH;
			else MOTOR_THR_CWL;
			break;
	}
}
void PAUSE(MOTORINFO_Type *Motor)
{
	while(Motor->RunFlag == ON)delay_ms(20);
}
void DRVI(MOTORINFO_Type *Motor,long target,unsigned int hz)
{
	DRVA(Motor,Motor->Current+target,hz);
}
void DRVA(MOTORINFO_Type *Motor,long target,unsigned int hz)
{
	u16 h,i;
	u32 j;
	long offset=target-Motor->Current;
	if((offset!=0)&&(Motor->RunFlag==OFF))
	{
		Motor->Target=target;
		if(hz<Motor->MINFrequency) hz=Motor->MINFrequency;
		else if(hz>Motor->MAXFrequency) hz=Motor->MAXFrequency;
		
		Motor->ladderNum=Motor->accelerateTime/10;
		j=(hz-Motor->MINFrequency)/Motor->ladderNum;
		for(i=0;i<Motor->ladderNum;i++)
		{
			Motor->ladderFreq[i]=i*j+Motor->MINFrequency;
			Motor->ladderPSC[i]=(Motor->CLK_DATA/Motor->ladderFreq[i])-1;
		}
		Motor->ladderFreq[Motor->ladderNum]=hz;
		Motor->ladderPSC[Motor->ladderNum]=Motor->CLK_DATA/hz-1;
		
		if(offset>0)
		{
			Motor->Dir=CW;
			setDir(Motor->num,CW);
			Motor->ladderTarget[0]=Motor->Current+Motor->MINFrequency/100;
			for(i=1;i<Motor->ladderNum;i++){
				Motor->ladderTarget[i]=Motor->ladderTarget[i-1]+Motor->ladderFreq[i]/100;
			}
			while(offset<=((Motor->ladderTarget[Motor->ladderNum-1]-Motor->Current)<<1))
			{
				Motor->ladderNum--;
			}
			for (i=0,h=Motor->ladderNum<<1;i<Motor->ladderNum;i++,h--)
			{
				Motor->ladderPSC[h]=Motor->ladderPSC[i];
			}
			Motor->ladderTarget[Motor->ladderNum<<1]=Motor->Target;
			for (i=(Motor->ladderNum<<1)-1,h=0;i>Motor->ladderNum;i--,h++)
			{
				Motor->ladderTarget[i]=Motor->ladderTarget[i+1]-Motor->ladderFreq[h]/100;
			}
			
		}else
		{
			Motor->Dir=CCW;
			setDir(Motor->num,CCW);
			Motor->ladderTarget[0]=Motor->Current-Motor->MINFrequency/100;
			for(i=1;i<Motor->ladderNum;i++){
				Motor->ladderTarget[i]=Motor->ladderTarget[i-1]-Motor->ladderFreq[i]/100;
			}
			while(offset>=((Motor->ladderTarget[Motor->ladderNum-1]-Motor->Current)<<1))
			{
				Motor->ladderNum--;
			}
			for (i=0,h=Motor->ladderNum<<1;i<Motor->ladderNum;i++,h--)
			{
				Motor->ladderPSC[h]=Motor->ladderPSC[i];
			}
			Motor->ladderTarget[Motor->ladderNum<<1]=Motor->Target;
			for (i=(Motor->ladderNum<<1)-1,h=0;i>Motor->ladderNum;i--,h++)
			{
				Motor->ladderTarget[i]=Motor->ladderTarget[i+1]+Motor->ladderFreq[h]/100;
			}
		}
		Motor->ladderTarget[Motor->ladderNum]=Motor->Target+Motor->Current-Motor->ladderTarget[Motor->ladderNum-1];
		Motor->RunFlag=ON;
	}
}

void pluseStart(MOTORINFO_Type *Motor)
{
	if(Motor->RunFlag==ON)
	{
		Motor->ladderOrderNum=0;
		setPSC(Motor->num,Motor->ladderPSC[0]);
		change_Timer(Motor->num,1);
	}
	
	
}
void irq_callback(MOTORINFO_Type *Motor)
{
	if(Motor->Dir == CW)
	{
		Motor->Current++;
	}
	else 
	{
		Motor->Current--;
	}
	if(Motor->Current == Motor->ladderTarget[Motor->ladderOrderNum])
	{
		if(Motor->ladderOrderNum<(Motor->ladderNum<<1))
		{
			Motor->ladderOrderNum++;
			setPSC(Motor->num,Motor->ladderPSC[Motor->ladderOrderNum]);
		}else
		{
			change_Timer(Motor->num,0);
			Motor->RunFlag=OFF;
		}
	}
}

void tim2_irq_callback(void)
{
	irq_callback(&Motor_one);
}

void tim3_irq_callback(void)
{
	irq_callback(&Motor_two);
}
void tim4_irq_callback(void)
{
	irq_callback(&Motor_thr);
}

















