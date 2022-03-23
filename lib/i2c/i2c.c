#include "i2c.h"

void I2C_Config(void){
	RCC->APB1ENR |= (1UL << 21);
	RCC->AHB1ENR |= (1UL << 1);
	
	GPIOB->MODER |= (2UL << 2*8) | (2UL << 2*9);
	GPIOB->OTYPER |= (1 << 8) | (1 << 9);
	GPIOB->OSPEEDR |= (3UL << 2*8) | (3UL << 2*9);
	GPIOB->PUPDR |= (1UL << 2*8) | (1UL << 2*9);
	GPIOB->AFR[1] |= (4UL << 4*0) | (4UL << 4*1);
	
	I2C1->CR1 |= (1UL << 15);
	I2C1->CR1 &= ~(1UL << 15);
	I2C1->CR2 |= (42UL << 0); // APB1 max. clock freq.
	I2C1->CCR = 210 << 0; // 1000 + 4000 / 23.8 (1/42)
	I2C1->TRISE = 43 << 0; // 1000 / 23.8
	I2C1->CR1 |= (1UL << 0);
}

void I2C_Start(void){
	I2C1->CR1 |= (1UL << 10);
	I2C1->CR1 |= (1UL << 8);
	while(!(I2C1->SR1 & (1 << 0)));
}

void I2C_Write(uint8_t data){
	while(!(I2C1->SR1 & (1 << 7)));
	I2C1->DR = data;
	while(!(I2C1->SR1 & (1 << 2)));
}

void I2C_Address(uint8_t address){
	uint8_t temp;
	I2C1->DR = address;
	while(!(I2C1->SR1 & (1 << 1)));
	temp = I2C1->SR1 | I2C1->SR2;
}

void I2C_Stop(void){
	I2C1->SR1 |= (1UL << 9);
}