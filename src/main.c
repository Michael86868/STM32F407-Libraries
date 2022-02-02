#include "stm32f407xx.h"

void GPIOD_Config(){
	RCC->AHB1ENR |= (1UL << 3);
	
	GPIOD->MODER |= (1UL << 2*12) | (1UL << 2*13) | (1UL << 2*14) | (1UL << 2*15);

	GPIOD->ODR &= ~(1UL << 12) & ~(1UL << 13) & ~(1UL << 14) & ~(1UL << 15);
}


int main(void){
	GPIOD_Config();
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/10000);
	
	while(1)
	{
		
	}
	
	return 0;
}