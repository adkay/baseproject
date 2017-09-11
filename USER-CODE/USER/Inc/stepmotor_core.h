#ifndef __STEPMOTOR_CORE_H
#define __STEPMOTOR_CORE_H

#include "sys.h"


typedef enum{
	CW=1,
	CCW=0
}DIR_Type;

typedef enum{
	ON=1,
	OFF=0
}STATUS_Type;
      //

typedef struct{
	u8 num;
	u16 MINFrequency;
	u32 MAXFrequency;
	u16 ADTIMELADDERNUM;
	u32 CLK_DATA;
	long Current;	//绝对定位 当前位置
	long Target;   //绝对定位 目标位置
	unsigned int Excitation;   //细分
	DIR_Type Dir;            //方向
	STATUS_Type RunFlag;     //运行控制
	unsigned int accelerateTime;   //加减速时间
	unsigned int ladderNum;
	unsigned int ladderOrderNum;
	u32 ladderFreq[102];
	u16 ladderPSC[202];
	long ladderTarget[202];
	
}MOTORINFO_Type;


void tim2_irq_callback(void);
void tim3_irq_callback(void);
void tim4_irq_callback(void);
void stepMotorInit(void);
void stepMotorRun(void);
void setSlope(u8 n,u16 atime);
void setPSC(u8 n,u16 psc);
void setDir(u8 n,DIR_Type m);
void DRVA(MOTORINFO_Type *Motor,long target,unsigned int hz);
void pluseStart(MOTORINFO_Type *Motor);
void PAUSE(MOTORINFO_Type *Motor);
void DRVI(MOTORINFO_Type *Motor,long target,unsigned int hz);
#endif

