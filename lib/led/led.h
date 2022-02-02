#ifndef led
#define led

#include "stm32f4xx.h"


void LED_setPin(unsigned char pin);
void LED_on(unsigned char pin);
void LED_off(unsigned char pin);
int LED_readState(unsigned char pin);

#endif
