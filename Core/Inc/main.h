  
  
  

  
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

  
#include "stm32f4xx_hal.h"

  
  

  

  
  

  

  
  

  

  
  

  

  
void Error_Handler(void);

  

  

  
#define LCD_D4_Pin GPIO_PIN_0
#define LCD_D4_GPIO_Port GPIOB
#define LCD_D5_Pin GPIO_PIN_1
#define LCD_D5_GPIO_Port GPIOB
#define LCD_D6_Pin GPIO_PIN_2
#define LCD_D6_GPIO_Port GPIOB
#define LCD_D7_Pin GPIO_PIN_3
#define LCD_D7_GPIO_Port GPIOB
#define LCD_RS_Pin GPIO_PIN_4
#define LCD_RS_GPIO_Port GPIOB
#define LCD_RW_Pin GPIO_PIN_5
#define LCD_RW_GPIO_Port GPIOB
#define LCD_EN_Pin GPIO_PIN_8
#define LCD_EN_GPIO_Port GPIOB

  

  

#ifdef __cplusplus
}
#endif

#endif   
