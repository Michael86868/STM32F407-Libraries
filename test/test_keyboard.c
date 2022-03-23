#include "stm32f407xx.h"
#include "keyboard.h"

int main(){
    uint16_t key;
    SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/10000);
    KEYPAD_Config();
    for(;;)
        key = KEYPAD_Key();
}