#ifndef i2c
#define i2c

#include "stm32f4xx.h"  

void I2C_Config(void);
void I2C_Start(void);
void I2C_Write(uint8_t data);
void I2C_Address(uint8_t address);
void I2C_Stop(void);

#endif