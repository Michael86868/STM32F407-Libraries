#include "stm32f407xx.h"
#include "button.h"
#include "functions.h"

void GPIOB_Config(){
    RCC->AHB1ENR |= (1UL << 1);

    BTN_setPin(14);
}

void GPIOD_Config(){
    RCC->AHB1ENR |= (1UL << 3);
    
    GPIOD->MODER |= (1UL << 2*12) | (1UL << 2*13) | (1UL << 2*14) | (1UL << 2*15);

    GPIOD->ODR &= ~(1UL << 12) & ~(1UL << 13) & ~(1UL << 14) & ~(1UL << 15);
}


int main(void){
    GPIOB_Config();
	GPIOD_Config();
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock/10000);
    
    while(1)
    {
        if(BTN_readState(14)){
            GPIOD->ODR |= (1UL << 12) | (1UL << 13) | (1UL << 14) | (1UL << 15);
        }else{
            GPIOD->ODR &= ~(1UL << 12) & ~(1UL << 13) & ~(1UL << 14) & ~(1UL << 15);
        }
        
        Delay(5000);
        
    }
    
    return 0;
}