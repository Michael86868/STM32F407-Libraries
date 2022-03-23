#include "lcd.h"

unsigned char lcdcontrol = 0x04 | 0x00 | 0x00;
unsigned char lcdmode = 0x02 | 0x00;
const int data_pins[4] = {6,7,8,9};
const int rs = 3;
const int rw = 4;
const int en = 5;

void LCD_config(void){
	RCC->AHB1ENR |= (1UL << 4);
	GPIOE->MODER |=  (1UL << 2*rs) | (1UL << 2*rw) | (1UL << 2*en) | (1UL << 2*data_pins[0]) | (1UL << 2*data_pins[1]) | (1UL << 2*data_pins[2]) | (1UL << 2*data_pins[3]);
	GPIOE->OTYPER &= ~(1UL << rs) & ~(1UL << rw) &	~(1UL << en) & ~(1UL <<   data_pins[0]) & ~(1UL <<   data_pins[1]) & ~(1UL <<   data_pins[2]) & ~(1UL << data_pins[3]);
	GPIOE->OSPEEDR &= ~(3UL << 2*rs) & ~(3UL << 2*rw) & ~(3UL << 2*en ) & ~(3UL << 2*data_pins[0]) & ~(3UL << 2*data_pins[1]) & ~(3UL << 2*data_pins[2]) & ~(3UL << 2*data_pins[3]);  
	GPIOE->OSPEEDR |=  (2UL << 2*rs) | (2UL << 2*rw) | (2UL << 2*en) | (2UL << 2*data_pins[0]) | (2UL << 2*data_pins[1]) | (2UL << 2*data_pins[2]) | (2UL << 2*data_pins[3]);
	GPIOE->PUPDR &= ~(3UL << 2*rs) & ~(3UL << 2*rw) & ~(3UL << 2*en) & ~(3UL << 2*data_pins[0]) & ~(3UL << 2*data_pins[1]) & ~(3UL << 2*data_pins[2]) & ~(3UL << 2*data_pins[3]);
}

void write_nibble(unsigned short int nibble){
	unsigned char i;
	GPIOE->BSRR = (1UL << (rw+16) ) | (1UL << (en+16));
	GPIOE->BSRR = (1UL << en);
	for(i=0;i<4;i++)
		if((nibble>>i)&0x01)
			GPIOE->ODR |= (1UL << (data_pins[i]));
	Delay(1);
	GPIOE->BSRR = (1UL << (en+16));
	Delay(1);
	GPIOE->ODR &= ~(1UL << data_pins[0]) & ~(1UL << data_pins[1]) & ~(1UL << data_pins[2]) & ~(1UL << data_pins[3]);
}

void LCD_command(unsigned short int cmd){
	GPIOE->BSRR = (1UL << (rs+16));
	write_nibble(cmd >> 4);
	write_nibble(cmd);
	Delay(1);	
}

void LCD_data(unsigned short int cmd){
	GPIOE->BSRR = (1UL << rs);
	write_nibble(cmd >> 4);
	write_nibble(cmd);
	Delay(1);
}

void LCD_setCursor(int col, int row){
	switch(row)
	{
		case 0: LCD_command(0x80 + col); break;
		case 1: LCD_command(0xC0 + col); break;
		case 2: LCD_command(0x94 + col); break;
		case 3: LCD_command(0xD4 + col); break;
	}
}

void LCD_print(char *text){
	unsigned short int i, length = strlen(text);
	for (i=0 ; i < length ; ++i ){
		LCD_data(*text);
		text++;
	}
}

void LCD_home(void){
	LCD_command(0x02);
	Delay(20);
}

void LCD_clear(void){
	LCD_command(0x01);
	Delay(20);
}

void LCD_blink(void){
	lcdcontrol |= 0x01;
	LCD_command(0x08 | lcdcontrol);
}

void LCD_noBlink(void){
	lcdcontrol &= ~0x01;
	LCD_command(0x08 | lcdcontrol);
}

void LCD_cursor(void){
	lcdcontrol |= 0x02;
	LCD_command(0x08 | lcdcontrol);
}

void LCD_noCursor(void){
	lcdcontrol &= ~0x02;
	LCD_command(0x08 | lcdcontrol);
}

void LCD_display(void){
	lcdcontrol |= 0x04;
	LCD_command(0x08 | lcdcontrol);
}

void LCD_noDisplay(void){
	lcdcontrol &= ~0x04;
	LCD_command(0x08 | lcdcontrol);
}

void LCD_scrollLeft(void){
	LCD_command(0x10 | 0x08 | 0x00);
}

void LCD_scrollRight(void){
	LCD_command(0x10 | 0x08 | 0x04);
}

void LCD_autoscroll(void){
	lcdmode |= 0x01;
	LCD_command(0x04 | lcdmode);
}

void LCD_noAutoscroll(void){
	lcdmode &= ~0x01;
	LCD_command(0x04 | lcdmode);
}

void LCD_leftToRight(void){
	lcdmode |= 0x02;
	LCD_command(0x04 | lcdmode);
}

void LCD_rightToLeft(void){
	lcdmode &= ~0x02;
	LCD_command(0x04 | lcdmode);
	LCD_scrollLeft();
}

void LCD_createChar(char b[8], unsigned char adress){
	unsigned char i = 0;
	LCD_command(((adress-1)<<3)+0x48); 
	for(i=0;i<8;i++)
		LCD_data(b[i]);
	Delay(50);
}

void LCD_printChar(unsigned char adress){
	LCD_data(((adress-1))+0x01);
}

void LCD_init(void){			 
	LCD_command(0x03);
	Delay(50);
	LCD_command(0x03);
	Delay(10);		
	LCD_command(0x03);	
	Delay(10);	
	LCD_command(0x02);
	LCD_command(0x28);			
	LCD_display();
	LCD_noCursor();
	LCD_clear();
}

void LCD_printf(const char * format, ...){
	char string[128];
	
	va_list arglist;
	va_start(arglist, format);

	vsnprintf(string, sizeof(string), format, arglist);

	LCD_print(string);
}