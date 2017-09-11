#ifndef __STEPMOTOR_DEV_H
#define __STEPMOTOR_DEV_H 

#include "sys.h"
#define TIME2_ARR 10
#define TIME3_ARR 10
#define TIME4_ARR 10
#define APB1_CLK 72000000
void timer_init(void);
void change_Timer(u8 n,u8 f);
void ctrlGPIO_Init(void);
#endif

