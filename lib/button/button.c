#include "button.h"

void BTN_setPin(unsigned char pin)
{
	GPIOA->MODER &= ~(3UL << 2*pin);
	GPIOA->PUPDR &= ~(3UL << 2*pin);
	GPIOA->PUPDR |= (1UL << 2*pin);
}

unsigned char BTN_readState(unsigned char pin)
{
	return (~(GPIOA->IDR >> pin) & 0x1);
}
