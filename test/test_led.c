#include "stm32f407xx.h"
#include "led.h"


void GPIOC_Config(){
	RCC->AHB1ENR |= (1UL << 2);

	LED_setPin(7);
}

int main(void){
	GPIOC_Config();
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/10000);
	
	while(1)
	{
		if(LED_readState(7)){
			LED_off(7);
		}else{
			LED_on(7);
		}
		Delay(5000);
	}
	return 0;
}