#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "main.h"
#include <stdint.h>

void LCD_HighNibble(uint8_t data);
void LCD_LowNibble(uint8_t data);

void scmd(uint8_t data);
void sdata(uint8_t data);

void lcd_init(void);
void string(char *data);
void lcd_goto(uint8_t row, uint8_t col);
#endif
