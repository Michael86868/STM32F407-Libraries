#include "stm32f407xx.h"
#include "lcd.h"

int main(void){
	char s5[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00};

	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/10000);
	LCD_config();
	LCD_init();

	LCD_createChar(s5,1);
	LCD_setCursor(0,0);
	LCD_printChar(1);

	LCD_setCursor(0,1);
	LCD_print("Mas se dobre ?");
	
	return 0;
}