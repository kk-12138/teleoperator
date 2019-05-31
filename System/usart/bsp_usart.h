/**
  * @file    bsp_usart.h
  * @author  WANG Kyle
  * @email   x-box361@live.com
  * @version V0.1
  * @date    13-May-2019
  * @brief   This file provides the interface of USART. 
  */

#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"
#include <stdio.h>

/** 
  * @brief USART configurtion.
  *
  * You should flow below setups to config USART:
  * 1. Config bus clock macro: USART1 append on AHB2 bus,
  * and others append on APB1 bus;
  * 2. Config GPIO macro.
  */
#define  DEBUG_USARTx                   USART1
#define  DEBUG_USART_CLK                RCC_APB2Periph_USART1
#define  DEBUG_USART_APBxClkCmd         RCC_APB2PeriphClockCmd
#define  DEBUG_USART_BAUDRATE           115200

#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd

#define  DEBUG_USART_TX_GPIO_PORT       GPIOA
#define  DEBUG_USART_TX_GPIO_PIN        GPIO_Pin_9
#define  DEBUG_USART_RX_GPIO_PORT       GPIOA
#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_10

#define  DEBUG_USART_IRQ                USART1_IRQn
#define  DEBUG_USART_IRQHandler         USART1_IRQHandler

void USART_Config(void);
void USART_SendByte(USART_TypeDef *pUSARTx, uint8_t data);
void USART_SendArray(USART_TypeDef *pUSARTx, uint8_t *array, uint16_t num);
void USART_SendString(USART_TypeDef *pUSARTx, char *str);
void USART_SendHalfWord(USART_TypeDef *pUSARTx, uint16_t data);

#endif /* __USART_H */

/********************************END OF FILE**********************************/
