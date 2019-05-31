/**
  * @file    oled_gpio.h
  * @author  WANG Kyle
  * @email   x-box361@live.com
  * @version V0.1
  * @date    25-May-2019
  * @brief   This file provides the interface of OLED.
  *
  * @attention
  *   SCL -> PB9
  *   SDA -> PB10
  *   RES -> PB11
  *   DC  -> PB12
  *   CS  -> PB13
  *   FSO -> PB14
  *   CS2 -> PB15
  */

#ifndef __OLED_GPIO_H
#define __OLED_GPIO_H

#include "stm32f10x.h"

#define Max_Column  128
#define SIZE  16

#define CLEAR  0
#define SET  1

#define OLED_SCL_GPIO_PORT    GPIOB
#define OLED_SCL_GPIO_CLK     RCC_APB2Periph_GPIOB
#define OLED_SCL_GPIO_PIN     GPIO_Pin_9

#define OLED_SDA_GPIO_PORT    GPIOB
#define OLED_SDA_GPIO_CLK     RCC_APB2Periph_GPIOB
#define OLED_SDA_GPIO_PIN     GPIO_Pin_10

#define OLED_RES_GPIO_PORT    GPIOB
#define OLED_RES_GPIO_CLK     RCC_APB2Periph_GPIOB
#define OLED_RES_GPIO_PIN     GPIO_Pin_11

#define OLED_DC_GPIO_PORT     GPIOB
#define OLED_DC_GPIO_CLK      RCC_APB2Periph_GPIOB
#define OLED_DC_GPIO_PIN      GPIO_Pin_12

#define OLED_CS_GPIO_PORT     GPIOB
#define OLED_CS_GPIO_CLK      RCC_APB2Periph_GPIOB
#define OLED_CS_GPIO_PIN      GPIO_Pin_13

#define OLED_FSO_GPIO_PORT    GPIOB
#define OLED_FSO_GPIO_CLK     RCC_APB2Periph_GPIOB
#define OLED_FSO_GPIO_PIN     GPIO_Pin_14

#define OLED_CS2_GPIO_PORT    GPIOB
#define OLED_CS2_GPIO_CLK     RCC_APB2Periph_GPIOB
#define OLED_CS2_GPIO_PIN     GPIO_Pin_15

#define OLED_SCL(a) if (a)  \
          GPIO_SetBits(OLED_SCL_GPIO_PORT, OLED_SCL_GPIO_PIN);\
          else  \
          GPIO_ResetBits(OLED_SCL_GPIO_PORT, OLED_SCL_GPIO_PIN)

#define OLED_SDA(a) if (a)  \
          GPIO_SetBits(OLED_SDA_GPIO_PORT, OLED_SDA_GPIO_PIN);\
          else  \
          GPIO_ResetBits(OLED_SDA_GPIO_PORT, OLED_SDA_GPIO_PIN)

#define OLED_RES(a) if (a)  \
          GPIO_SetBits(OLED_RES_GPIO_PORT, OLED_RES_GPIO_PIN);\
          else  \
          GPIO_ResetBits(OLED_RES_GPIO_PORT, OLED_RES_GPIO_PIN)

#define OLED_DC(a) if (a)  \
          GPIO_SetBits(OLED_DC_GPIO_PORT, OLED_DC_GPIO_PIN);\
          else  \
          GPIO_ResetBits(OLED_DC_GPIO_PORT, OLED_DC_GPIO_PIN)

#define OLED_CS(a) if (a)  \
          GPIO_SetBits(OLED_CS_GPIO_PORT, OLED_CS_GPIO_PIN);\
          else  \
          GPIO_ResetBits(OLED_CS_GPIO_PORT, OLED_CS_GPIO_PIN)

#define OLED_FSO(a) if (a)  \
          GPIO_SetBits(OLED_FSO_GPIO_PORT, OLED_FSO_GPIO_PIN);\
          else  \
          GPIO_ResetBits(OLED_FSO_GPIO_PORT, OLED_FSO_GPIO_PIN)

#define OLED_CS2(a) if (a)  \
          GPIO_SetBits(OLED_CS2_GPIO_PORT, OLED_CS2_GPIO_PIN);\
          else  \
          GPIO_ResetBits(OLED_CS2_GPIO_PORT, OLED_CS2_GPIO_PIN)

#define FOND_CHIP_OUT GPIO_ReadInputDataBit(OLED_FSO_GPIO_PORT, OLED_FSO_GPIO_PIN)

void InitOLED(void);
void OledClearScreen(void);
void DisplayGraphic5x7(uint32_t page, uint32_t column, const uint8_t *ptr);

/**
  * @brief  Display string in the size of 5x7.
  *         5 means it occupies 5 dots in column.
  *         7 means it occupies 7 dots in raw.
  * @param  y: Where y can be 1-8 to select the page adress.
  *            Because the resolution of this OLED is 128x64,
  *            one page occupies 8 raws.
  *            Therefore it has 8 pages totally.
  * @param  x: The column address of the dot.
  *            Actually, what you need is the adress of the character.
  *            So you need to caculate the address of the character 
  *            by the address of the dot and the size of the character.
  * @param  str: The pointer to the string you want to display.
  * @retval None
  */
void OledShowString(uint8_t y, uint8_t x, uint8_t *str);

#endif /* __OLED_GPIO_H */

/********************************END OF FILE**********************************/
