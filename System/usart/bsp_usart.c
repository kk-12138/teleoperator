/**
  * @file    bsp_usart.c
  * @author  WANG Kyle
  * @email   x-box361@live.com
  * @version V0.1
  * @date    13-May-2019
  * @brief   This file provides the functions of USART. 
  */

#include "bsp_usart.h"

 /**
  * @brief  Configs the NVIC.
  * @param  None
  * @retval None
  */
//static void NVIC_Configuration(void)
//{
//  NVIC_InitTypeDef NVIC_InitStructure;

//  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

//  NVIC_Init(&NVIC_InitStructure);
//}

 /**
  * @brief  Configs the USART1 parameter.
  * @param  None
  * @retval None
  */
void USART_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;

  /* Enables GPIOA and USART1 clock. */
  DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
  DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);

  /* Configs GPIO parameter. */
  GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);

  /* Configs USART parameter. */
  USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(DEBUG_USARTx, &USART_InitStructure);

//  /* Configs NVIC. */
//  NVIC_Configuration();

//  /* Enables USART1 interrupt. */
//  USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);

  /* Enables USART1. */
  USART_Cmd(DEBUG_USARTx, ENABLE);
}

/**
  * @brief  Transmits single data through the USARTx peripheral.
  * @param  pUSARTx: Select the USART or the UART peripheral.
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @param  data: the data to transmit.
  * @retval None
  */
void USART_SendByte(USART_TypeDef *pUSARTx, uint8_t data)
{
  USART_SendData(pUSARTx, data);

  /* wait until the transmition complete. */
  while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

/**
  * @brief  Transmits array through the USARTx peripheral.
  * @param  pUSARTx: Select the USART or the UART peripheral.
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @param  array: the data to transmit.
  * @param  num: the number of members in the array.
  * @retval None
  */
void USART_SendArray(USART_TypeDef *pUSARTx, uint8_t *array, uint16_t num)
{
  uint8_t i;

  for (i = 0; i < num; i++)
  {
    USART_SendByte(pUSARTx, array[i]);
  }

  /* wait until the transmition complete. */
  while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);
}

/**
  * @brief  Transmits string through the USARTx peripheral.
  * @param  pUSARTx: Select the USART or the UART peripheral. 
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @param  str: Point to the data for transmit.
  * @retval None
  */
void USART_SendString(USART_TypeDef *pUSARTx, char *str)
{
  unsigned int k = 0;

  do 
  {
    USART_SendByte(pUSARTx, *(str + k));
    k++;
  } while (*(str + k) != '\0');
  
  /* wait until the transmition complete. */
  while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);
}

/**
  * @brief  Transmits single data through the USARTx peripheral.
  * @param  pUSARTx: Select the USART or the UART peripheral. 
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @param  data: the data to transmit.
  * @retval None
  */
void USART_SendHalfWord(USART_TypeDef *pUSARTx, uint16_t data)
{
  uint8_t temp_h, temp_l;

  temp_h = (data & 0XFF00) >> 8;
  temp_l = data & 0XFF;

  /* Sends high eight bits of data. */
  USART_SendData(pUSARTx, temp_h);	
  while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);

  /* Sends low eight bits of data. */
  USART_SendData(pUSARTx, temp_l);
  while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

/* Redirecs C library fputc to USART1, and then you can use printf. */
int fputc(int ch, FILE *f)
{
  USART_SendData(DEBUG_USARTx, (uint8_t) ch);
  while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);

  return (ch);
}

/* Redirecs C library fgetc to USART1. */
int fgetc(FILE *f)
{
  /* Waits for USART1 input data. */
  while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);

  return (int)USART_ReceiveData(DEBUG_USARTx);
}

/********************************END OF FILE**********************************/
