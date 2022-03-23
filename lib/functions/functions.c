#include "functions.h"

volatile uint32_t Ticks;

void SysTick_Handler(void) {
  	Ticks++;
}

void Delay(uint32_t ms) {
  	uint32_t start;
  	start = Ticks;
  	while ((Ticks - start) < ms);
}

char* charToString(unsigned char number){
	static char string[50];
	sprintf(string, "%c", number);
	return string;
}

char* intToString(unsigned char number){
	static char string[50];
	sprintf(string, "%d", number);
	return string;
}

char* floatToString(float number){
	static char string[50];
	sprintf(string, "%.2f", number);
	return string;
}

char* usintToString(unsigned long int number){
	static char string[50];
	sprintf(string, "%ld", number);
	return string;
}
