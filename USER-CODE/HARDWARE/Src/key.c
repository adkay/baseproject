#include "key.h"
#include "gpio.h"


u8 Trg=0;
u8 Cont=0;
void key_Init(void)
{
	RCC->APB2ENR|=1<<6;    	//PORTE
	GPIOE->CRL&=0XFFF0000F;
	GPIOE->CRL|=0X00088880;
	GPIOE->ODR|=1<<1;
	GPIOE->ODR|=1<<2;
	GPIOE->ODR|=1<<3;
	GPIOE->ODR|=1<<4;  
	
}

void keyRead(void)
{
	u8 ReadData=((KEY_UP<<UP_Press)+(!KEY_DOWN<<DOWN_Press)+(!KEY_LEFT<<LEFT_Press)+(!KEY_RIGHT<<RIGHT_Press))^0xFF;
	Trg=ReadData&(ReadData^Cont);
	Cont=ReadData;
}
















