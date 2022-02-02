#ifndef button
#define button

#include "stm32f4xx.h"

void BTN_setPin(unsigned char pin);
unsigned char BTN_readState(unsigned char pin);

#endif
