#include "led.h"

void LED_on(unsigned char pin)
{
	GPIOC->ODR &= ~(1 << pin);
}

void LED_off(unsigned char pin)
{
	GPIOC->ODR |= (1 << pin);
}

void LED_setPin(unsigned char pin)
{
	GPIOC->MODER |= (1UL << 2*pin);
	LED_off(pin);
}

int LED_readState(unsigned char pin)
{
	return !(GPIOC->ODR << pin);
}


