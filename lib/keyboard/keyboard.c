#include "keyboard.h"

const int row_pins[4] = {6,7,8,9};
const int col_pins[4] = {0,1,2,3};

void KEYPAD_Config(){
	RCC->AHB1ENR |= (1UL << 3);
	GPIOD->MODER |= (1UL << 2*row_pins[0]) | (1UL << 2*row_pins[1]) | (1UL << 2*row_pins[2]) | (1UL << 2*row_pins[3]);
	GPIOD->OTYPER &= ~(1UL << row_pins[0]) & ~(1UL << row_pins[1]) & ~(1UL << row_pins[2]) & ~(1UL << row_pins[3]);
	GPIOD->OSPEEDR &= ~(3UL << 2*row_pins[0]) & ~(3UL <<2*row_pins[1]) & ~(3UL << 2*row_pins[2]) & ~(3UL << 2*row_pins[3]);
	GPIOD->OSPEEDR |= (2UL << 2*row_pins[0]) | (2UL << 2*row_pins[1]) | (2UL << 2*row_pins[2]) | (2UL << 2*row_pins[3]);
	GPIOD->PUPDR &= ~(3UL << 2*row_pins[0]) & ~(3UL << 2*row_pins[1]) & ~(3UL << 2*row_pins[2]) & ~(3UL << 2*row_pins[3]);
	GPIOD->MODER &= ~(3UL << 2*col_pins[0]) & ~(3UL << 2*col_pins[1]) & ~(3UL << 2*col_pins[2]) & ~(3UL << 2*col_pins[3]);
	GPIOD->PUPDR &= ~(3UL << 2*col_pins[0]) & ~(3UL << 2*col_pins[1]) & ~(3UL << 2*col_pins[2]) & ~(3UL << 2*col_pins[3]);
	GPIOD->PUPDR |= (1UL << 2*col_pins[0]) | (1UL << 2*col_pins[1]) | (1UL << 2*col_pins[2]) | (1UL << 2*col_pins[3]);
}

unsigned char KEYPAD_Key(void){
	while(1){
		Delay(2000);

		GPIOD->ODR &= ~(1UL << row_pins[1]) & ~(1UL << row_pins[1]) & ~(1UL << row_pins[2]) & ~(1UL << row_pins[3]);
		GPIOD->ODR |= (1UL << row_pins[0]) | (1UL << row_pins[1]) | (1UL << row_pins[2]);
		
		switch (GPIOD->IDR & 0xF){
			case 14: return '.'; 
			case 13: return '0';
			case 11: return '=';
			case 7: return '/';
		}

		GPIOD->ODR &= ~(1UL << row_pins[0]) & ~(1UL << row_pins[1]) & ~(1UL << row_pins[2]) & ~(1UL << row_pins[3]);
		GPIOD->ODR |= (1UL << row_pins[0]) | (1UL << row_pins[1]) | (1UL << row_pins[3]);

		switch (GPIOD->IDR & 0xF){
			case 14: return '7';
			case 13: return '8';
			case 11: return '9';
			case 7: return '*';
		}

		GPIOD->ODR &= ~(1UL << row_pins[0]) & ~(1UL << row_pins[1]) & ~(1UL << row_pins[2]) & ~(1UL << row_pins[3]);
		GPIOD->ODR |= (1UL << row_pins[0]) | (1UL << row_pins[2]) | (1UL << row_pins[3]);
		
		switch (GPIOD->IDR & 0xF){
			case 14: return '4';
			case 13: return '5';
			case 11: return '6';
			case 7: return '-';
		}
		GPIOD->ODR &= ~(1UL << row_pins[0]) & ~(1UL << row_pins[1]) & ~(1UL << row_pins[2]) & ~(1UL << row_pins[3]);
		GPIOD->ODR |= (1UL << row_pins[1]) | (1UL << row_pins[2]) | (1UL << row_pins[3]);

		switch (GPIOD->IDR & 0xF){
			case 14: return '1';
			case 13: return '2';
			case 11: return '3';
			case 7: return '+';
		}
	}
}
