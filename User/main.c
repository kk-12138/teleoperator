/**
  * @file    main.c
  * @author  WANG Kyle
  * @email   x-box361@live.com
  * @version V0.1
  * @date    13-May-2019
  * @brief   Basic development environment.
  */

#include "stm32f10x.h"
#include "bsp_systick.h"
#include "bsp_usart.h"

int main(void)
{
  /* Configures the nested vectored interrupt controller. */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

  USART_Config();

  printf("just a UART test...\n");
  DelayMs(1000);

  while(1)
  {
  }
}
