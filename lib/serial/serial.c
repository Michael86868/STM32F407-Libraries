#include "serial.h"


void Uart2Config(void)
{
	RCC->APB1ENR |= (1<<17);  // Povolení hodinovího signílu pro UART2
	RCC->AHB1ENR |= (1<<0); // Povolení hodinovího signílu pro port A
	
	GPIOA->MODER |= (2<<4);  // Nastavení alternativní funkce pro pin PA2
	GPIOA->MODER |= (2<<6);  // Nastavení alternativní funkce pro pin PA3
	
	GPIOA->OSPEEDR |= (3<<4) | (3<<6);  //Nastavení rychlosti na nejvyssi (High Speed)
	
	GPIOA->AFR[0] |= (7<<8);  // Nastavení alternativní funkce pro USART2 na Pin PA2 [AF7]
	GPIOA->AFR[0] |= (7<<12); // Nastavení alternativní funkce pro USART2 na Pin PA3 [AF7]
	
	USART2->CR1 |= (1<<13);  // Povolení USART2
	
	USART2->CR1 |= (0<<12);  // Nastavení delky slova na 8bitu [M=0]
	
	//USART2->BRR = (7<<0) | (24<<4);   // Nastavení Baud Rate na 115200 baudu (Nutno vypocitat!)
	USART2->BRR = 0x8B; // Nastavení Baud Rate na 115200 baudu (Nutno vypocitat!)
	
	USART2->CR1 |= (1<<2); //Povolení prijimace
	USART2->CR1 |= (1<<3);  //Povoleni vysilace
}


void UART2_SendChar(unsigned char c)
{
	USART2->DR = c; // Ulozeni dat do DR registru
	while (!(USART2->SR & (1<<6)));  // Pockani na poslani vsech dat z DR registru pomocí hodinoveho signalu
}
	
void UART2_SendString(char *string)
{
	while (*string) UART2_SendChar (*string++);
}

uint8_t UART2_GetChar (void)
{
	do{
		while (!(USART2->SR & (1<<5))); // Pockani na precteni vsech dat z DR registru pomoci hodinoveho signalu
	}while(USART2->DR == '\n' || USART2->DR == '\r' || USART2->DR == '\b'); //Platformio vraci i ENTER, kterym potvrdime odeslani ('\b' - backspace)

	return USART2->DR; // Vraceni dat z DR registru
}
