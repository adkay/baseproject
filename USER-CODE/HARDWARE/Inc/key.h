#ifndef __KEY_H
#define __KEY_H

#include "sys.h"

#define KEY_UP !PEin(1)
#define KEY_DOWN !PEin(3)
#define KEY_LEFT !PEin(2)
#define KEY_RIGHT !PEin(4)


#define UP_Press 0
#define DOWN_Press 1
#define LEFT_Press 2
#define RIGHT_Press 3

extern u8 Trg;
extern u8 Cont;

void key_Init(void);
void keyRead(void);

#endif

