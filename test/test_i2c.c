#include "stm32f4xx.h" 
#include "i2c.h"   

int main (void)
{
	I2C_Config();
	
	I2C_Start();
	I2C_Address(0x4E);
	I2C_Write(0x20);
	I2C_Stop();
	for(;;);
}