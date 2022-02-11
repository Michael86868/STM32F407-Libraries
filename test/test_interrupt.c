#include "stm32f407xx.h"

int flag = 0;

void GPIOA_Config(){
    RCC->AHB1ENR |= (1UL << 0);
	GPIOA->MODER &= ~(3UL << 2*4); 
	GPIOA->PUPDR |= (2UL << 2*4);
}

void GPIOC_Config(){
    RCC->AHB1ENR |= (1UL << 2);
    GPIOC->MODER |= (1UL << 2*7);
    GPIOC->PUPDR &= ~(3UL << 2*7);
    GPIOC->PUPDR |= (1UL << 2*7);
}

void Interrupt_Config(){
    RCC->APB2ENR |= (1UL << 14); // Povolení hodinového signálu pro systémové přerušení (external interrupt)

    SYSCFG->EXTICR[2] &= ~(15UL << 0);  // Povolení hodinového signálu pro pin PA4

    EXTI->IMR |= (1UL << 4); // Zrušení maskování 0 pinu

    EXTI->RTSR &= ~(1UL << 4); // Reagování při náběžné hraně 0 pinu

    EXTI->FTSR |= (1UL << 4); // Reagování při sestupné hraně 0 pinu

    NVIC_SetPriority(EXTI4_IRQn, 4); // Nastavení nejvyšší priority pro External Interrupt pinu 0

    NVIC_EnableIRQ(EXTI4_IRQn); // Povolení External Interrupt-u na pinu 0
}

void EXTI4_IRQHandler(void){
    if(EXTI->PR & (1UL << 4)) // Zjištění zda bylo aktivováno přerušení na nultém pinu
    {
        EXTI->PR |= (1UL << 4); // Nastavení přerušení do 0
        flag = 1;
    }
}

int main(void){
    GPIOA_Config();
    GPIOC_Config();
    Interrupt_Config();
    
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock/10000);

    while(1)
    {
        LED_on(7);
        if(flag){
            LED_off(7);
            flag = 0;
            Delay(50000);
        } 
        Delay(500);

    }
    
    return 0;
}
