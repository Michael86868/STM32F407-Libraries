#include "stm32f4xx.h"

void GPIOD_Config(){
    RCC->AHB1ENR |= (1UL << 2); // Povolení clocku na port C
	GPIOC->MODER |= (2UL << 2*8) | (2UL << 2*9); // Nastavení alternativní funkce pro piny 8 a 9
    GPIOC->OSPEEDR |= (3UL << 2*8) | (3UL << 2*9); // Nastavení frekvence 100MHz na 8 a 9 pin
	GPIOC->PUPDR &= ~(3UL << 2*8) & ~(3UL << 2*9); // Vynulování registru (pro nastavení PULL UP)
	GPIOC->PUPDR |= (1UL << 2*8) | (1UL << 2*9); // Nastavení PULL UP na 8 a 9 pin
	GPIOC->AFR[1] |= (2UL << 4*0) | (2UL << 4*1); // Zapnutí alternativní funkce na piny 8 a 9
}

void TIM3_Config(){
    RCC->APB1ENR |= (1UL << 1); //Zapnutí clocku na TIM3
    TIM3->PSC = 15; // SysClock = 16/(15+1)=1MHz
    TIM3->ARR = 10000; //Perioda = 10ms 
    TIM3->EGR |= (1UL << 0); //Generate an update event  
    TIM3->CCMR2 |= (6UL << 4) | (6UL << 12); //Zapnutí PWM  
    TIM3->CCR3 = 5000;// Nastavení "duty cycle" na 40%
    TIM3->CCR4 = 5000;// Nastavení "duty cycle" na 10%
    TIM3->CCER |= (1UL << 0) | (1UL << 4) | (1UL << 8) | (1UL << 12);
    TIM3->CR1 |= (1UL << 0); // Zapnutí citani citace	
	TIM3->DIER |= (1UL << 1); //Zapnutí interního preruseni
	NVIC_SetPriority(TIM3_IRQn, 3);
	NVIC_EnableIRQ(TIM3_IRQn);
}

void TIM3_IRQHandler(){
	if(TIM3->SR & 1){
		if(TIM3->CCR4 == 10000){
			TIM3->CCR4 = 5000;
		}else{
			TIM3->CCR4 += 50;
		}
		TIM3->SR &= ~(1UL << 0);
	}
}


int main(void)
{ 
    GPIOD_Config();
    TIM3_Config();
	for(;;);
}