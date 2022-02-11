#ifndef serial
#define serial

#include "stm32f4xx.h"
#include <string.h>
#include "functions.h"
#include <math.h>

void UART2_Config(void);
void UART2_SendChar(unsigned char c);
void UART2_SendString(char *string);
uint8_t UART2_GetChar(void);

#endif
