#include "button.h"

void BTN_setPin(unsigned char pin)
{
	GPIOA->MODER &= ~(3UL << 2*pin);
	GPIOB->PUPDR &= ~(3UL << 2*pin);
	GPIOB->PUPDR |= (1UL << 2*pin);
}

unsigned char BTN_readState(unsigned char pin)
{
	return ((GPIOB->IDR >> pin) & 0x1);
}
