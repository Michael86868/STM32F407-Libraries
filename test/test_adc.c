#include <stdio.h>
#include "stm32f4xx.h"

uint16_t data;

void ADC_Config(){
	RCC->APB2ENR |= (1UL << 8);
	RCC->AHB1ENR |= (1UL << 0);
	ADC->CCR &= ~(3UL << 16);
	ADC1->CR1 |= (1UL << 8);
	ADC1->CR1 &= ~(3UL << 24);
	ADC1->CR2 |= (1UL << 1);
	ADC1->CR2 |= (1UL << 10);
	ADC1->CR2 &= ~(1UL << 11);
	ADC1->SMPR2 &= ~(7UL << 4*3);
	ADC1->SQR1 |= (1UL << 20);
	GPIOA->MODER |= (3UL << 2*4);
	ADC1->SQR3 |= (4UL << 0);
	ADC1->SQR3 = 0;
	ADC1->SQR3 |= (4UL << 0);
}

uint16_t ADC_Start(){
	ADC1->CR2 |= (1UL << 0);
	ADC1->SR = 0;
	ADC1->CR2 |= (1UL << 30);
	while(!(ADC1->SR & (1UL << 1)));
	ADC1->CR2 &= ~(1UL << 0);
	return ADC1->DR;
}

int main(void){
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock/10000);
	ADC_Config();
	
	while(1){
		ADC_Start();
		Delay(5000);
	}
}