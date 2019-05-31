/**
  * @file    bsp_systick.h
  * @author  WANG Kyle
  * @email   x-box361@live.com
  * @version V0.1
  * @date    13-May-2019
  * @brief   This file provides the prototype of delay function. 
  */

#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"

void SysTickDelayUs(__IO uint32_t us);
void SysTickDelayMs(__IO uint32_t ms);

#define DelayUs(x) SysTickDelayUs(x)
#define DelayMs(x) SysTickDelayMs(x)

#endif /* __SYSTICK_H */

/********************************END OF FILE**********************************/
