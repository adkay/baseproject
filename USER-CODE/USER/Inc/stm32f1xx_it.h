#ifndef __STM32F1XX_IT_H
#define __STM32F1XX_IT_H
#include "sys.h"
typedef void(*FUNC_POINT)(void);


void SetTimeIRQFunc(u8 timerNum,FUNC_POINT func);

#endif




