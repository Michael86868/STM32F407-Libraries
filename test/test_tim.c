#include "stm32f407xx.h"
#include "functions.h"

void GPIOC_Config(){
    RCC->AHB1ENR |= (1UL << 2);
    GPIOC->MODER |= (1UL << 2*7);
}
void TIM6_Config(void)
{
    RCC->APB1RSTR |= RCC_APB1RSTR_TIM6RST;
    RCC->APB1RSTR &= ~RCC_APB1RSTR_TIM6RST;
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
    TIM6->CR1 |= TIM_CR1_ARPE;  
    TIM6->ARR = 65523;  
    TIM6->PSC = 500;  
    TIM6->CR1 |= TIM_CR1_CEN;   
    TIM6->EGR = TIM_EGR_UG;
    TIM6->SR = 0x0000;  
}

int main(void){
    GPIOC_Config();
    TIM6_Config();
    
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock/10000);

    while(1)
    {
        GPIOC->ODR &= ~(1UL << 7);
        if(TIM6->SR & TIM_SR_UIF){
            GPIOC->ODR |= (1UL << 7);
            TIM6->SR = 0;
            Delay(5000);
        }
        Delay(1);
    }
    
    return 0;
}



