#ifndef serial
#define serial

#include "stm32f4xx.h"
#include <string.h>
#include "functions.h"
#include <math.h>

void Uart2Config(void);
void UART2_SendChar(unsigned char c);
void UART2_SendString(char *string);

#endif
