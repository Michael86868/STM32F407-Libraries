#ifndef lcd

#define lcd

#include "stm32f4xx.h"  
#include <string.h>
#include "functions.h"
#include <stdarg.h>
#include <stdio.h>

//3 RS, 4 R/W, 5 E, 6..9 DB4..DB7

//void LCD_config(unsigned char _rs,unsigned char _rw,unsigned char _en,unsigned char _db4,unsigned char _db5,unsigned char _db6,unsigned char _db7);

void LCD_config(void);
void write_nibble(unsigned short int nibble);
void LCD_command(unsigned short int cmd);
void LCD_data(unsigned short int cmd);
void LCD_setCursor(int col, int row);
void LCD_print(char *text);
void LCD_home(void);
void LCD_clear(void);
void LCD_blink(void);
void LCD_noBlink(void);
void LCD_cursor(void);
void LCD_noCursor(void);
void LCD_display(void);
void LCD_noDisplay(void);
void LCD_scrollLeft(void);
void LCD_scrollRight(void);
void LCD_autoscroll(void);
void LCD_noAutoscroll(void);
void LCD_leftToRight(void);
void LCD_rightToLeft(void);
void LCD_createChar(char b[8], unsigned char adress);
void LCD_printChar(unsigned char adress);
void LCD_init(void);
void LCD_printf(const char * format, ...) __attribute__((format(printf, 1, 2)));


#endif

