 

#include "lcd.h"

void LCD_HighNibble(uint8_t data)
{
    HAL_GPIO_WritePin(GPIOB, LCD_D4_Pin, (data >> 4) & 0x01);
    HAL_GPIO_WritePin(GPIOB, LCD_D5_Pin, (data >> 5) & 0x01);
    HAL_GPIO_WritePin(GPIOB, LCD_D6_Pin, (data >> 6) & 0x01);
    HAL_GPIO_WritePin(GPIOB, LCD_D7_Pin, (data >> 7) & 0x01);

    HAL_GPIO_WritePin(GPIOB, LCD_EN_Pin, 1);
    HAL_Delay(10);
    HAL_GPIO_WritePin(GPIOB, LCD_EN_Pin, 0);
}

void LCD_LowNibble(uint8_t data)
{
    HAL_GPIO_WritePin(GPIOB, LCD_D4_Pin, (data >> 0) & 0x01);
    HAL_GPIO_WritePin(GPIOB, LCD_D5_Pin, (data >> 1) & 0x01);
    HAL_GPIO_WritePin(GPIOB, LCD_D6_Pin, (data >> 2) & 0x01);
    HAL_GPIO_WritePin(GPIOB, LCD_D7_Pin, (data >> 3) & 0x01);

    HAL_GPIO_WritePin(GPIOB, LCD_EN_Pin, 1);
    HAL_Delay(10);
    HAL_GPIO_WritePin(GPIOB, LCD_EN_Pin, 0);
}

void scmd(uint8_t data)
{
    HAL_GPIO_WritePin(GPIOB, LCD_RS_Pin, 0);
    LCD_HighNibble(data);
    LCD_LowNibble(data);

}

void sdata(uint8_t data)
{
    HAL_GPIO_WritePin(GPIOB, LCD_RS_Pin, 1);
    LCD_HighNibble(data);
    LCD_LowNibble(data);

}

void lcd_init(void)
{
    HAL_Delay(20);

    scmd(0x33);

    HAL_Delay(1);

    scmd(0x32);
    scmd(0x0C);
    scmd(0x01);
}

void string(char *data)
{
    while(*data != '\0')
    {
        sdata(*data);
        data++;
    }
}
void lcd_goto(uint8_t row, uint8_t col)
{
    if(row == 0)
        scmd(0x80 + col);
    else
        scmd(0xC0 + col);
}
