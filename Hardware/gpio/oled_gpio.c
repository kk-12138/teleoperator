/**
  * @file    oled_gpio.c
  * @author  WANG Kyle
  * @email   x-box361@live.com
  * @version V0.1
  * @date    25-May-2019
  * @brief   This file provides the functions of OLED.
  */

#include "oled_gpio.h"
#include "bsp_systick.h"

unsigned long fontaddr = 0;

static void OledGpioConfig(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enables GPIOB clock. */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

  /* Configs GPIO parameter. */
  GPIO_InitStructure.GPIO_Pin = OLED_SCL_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(OLED_SCL_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = OLED_SDA_GPIO_PIN;
  GPIO_Init(OLED_SDA_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = OLED_RES_GPIO_PIN;
  GPIO_Init(OLED_RES_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = OLED_DC_GPIO_PIN;
  GPIO_Init(OLED_DC_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = OLED_CS_GPIO_PIN;
  GPIO_Init(OLED_CS_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = OLED_CS2_GPIO_PIN;
  GPIO_Init(OLED_CS2_GPIO_PORT, &GPIO_InitStructure);

  /* /Resets GPIO. */
  GPIO_ResetBits(OLED_SCL_GPIO_PORT, OLED_SCL_GPIO_PIN);
  GPIO_ResetBits(OLED_SDA_GPIO_PORT, OLED_SDA_GPIO_PIN);
  GPIO_ResetBits(OLED_RES_GPIO_PORT, OLED_RES_GPIO_PIN);
  GPIO_ResetBits(OLED_DC_GPIO_PORT, OLED_DC_GPIO_PIN);
  GPIO_ResetBits(OLED_CS_GPIO_PORT, OLED_CS_GPIO_PIN);
  GPIO_ResetBits(OLED_CS2_GPIO_PORT, OLED_CS2_GPIO_PIN);
}

static void OledTransferCmd(int cmd)
{
  char i;

  OLED_DC(0);
  OLED_CS(0);

  for(i = 0; i< 8; i++)
  {
    OLED_SCL(0);

    if (cmd & 0x80)
      OLED_SDA(1);
    else
      OLED_SDA(0);

    OLED_SCL(1);
    __nop();

    cmd <<= 1;
  }

  OLED_DC(1);
  OLED_CS(1);
}

static void OledTransferData(int data)
{
  char i;

  OLED_DC(1);
  OLED_CS(0);

  for(i = 0; i< 8; i++)
  {
    OLED_SCL(0);

    if (data & 0x80)
      OLED_SDA(1);
    else
      OLED_SDA(0);

    OLED_SCL(1);
    __nop();

    data <<= 1;
  }

  OLED_DC(1);
  OLED_CS(1);
}

void InitOLED(void)
{
  DelayMs(400);
  OledGpioConfig();
  OLED_RES(0);
  DelayMs(400);
  OLED_RES(1);
  OLED_CS(0);
  OLED_CS2(1);

  OledTransferCmd(0xAE);  //display off
  OledTransferCmd(0x20);  //Set Memory Addressing Mode	
  OledTransferCmd(0x10);  //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
  OledTransferCmd(0xb0);  //Set Page Start Address for Page Addressing Mode,0-7
  OledTransferCmd(0xc8);  //Set COM Output Scan Direction
  OledTransferCmd(0x00);  //set low column address
  OledTransferCmd(0x10);  //set high column address
  OledTransferCmd(0x40);  //set start line address
  OledTransferCmd(0x81);  //set contrast control register
  OledTransferCmd(0xFF);
  OledTransferCmd(0xa1);  //set segment re-map 0 to 127
  OledTransferCmd(0xa6);  //set normal display
  OledTransferCmd(0xa8);  //set multiplex ratio(1 to 64)
  OledTransferCmd(0x3F);
  OledTransferCmd(0xa4);  //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
  OledTransferCmd(0xd3);  //set display offset
  OledTransferCmd(0x00);  //not offset
  OledTransferCmd(0xd5);  //set display clock divide ratio/oscillator frequency
  OledTransferCmd(0xf0);  //set divide ratio
  OledTransferCmd(0xd9);  //set pre-charge period
  OledTransferCmd(0x22);
  OledTransferCmd(0xda);  //set com pins hardware configuration
  OledTransferCmd(0x12);
  OledTransferCmd(0xdb);  //set vcomh
  OledTransferCmd(0x20);  //0x20,0.77xVcc
  OledTransferCmd(0x8d);  //set DC-DC enable
  OledTransferCmd(0x14);
  OledTransferCmd(0xaf);  //turn on oled panel 

  OLED_CS(1);
}

void OledClearScreen(void)
{
  uint8_t i, j;

  OLED_CS(0);
  OLED_CS2(1);

  for(i = 0; i < 8; i++)
  {
    OledTransferCmd(0xb0+i);
    OledTransferCmd(0x00);
    OledTransferCmd(0x10);

    for(j = 0; j < 128; j++)
    {
      OledTransferData(0x00);
    }
  }
  OLED_CS(1);
}

static void SendCmdToFondChip(uint8_t cmd)
{
  uint8_t i;

  for(i = 0; i < 8; i++)
  {
    if(cmd & 0x80)
    {
      OLED_SDA(1);
      __nop();
    }
    else
    {
      OLED_SDA(0);
      __nop();
    }

    cmd = cmd<<1;

    OLED_SCL(0);
    __nop();
    OLED_SCL(1);
    __nop();
  }
}

static void FondChipGpioSet(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = OLED_FSO_GPIO_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;

  GPIO_Init(OLED_FSO_GPIO_PORT, &GPIO_InitStructure);
}

static void FondChipGpioReset(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = OLED_FSO_GPIO_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;

  GPIO_Init(OLED_FSO_GPIO_PORT, &GPIO_InitStructure);
}

static uint8_t GetDataFromFondChip(void)
{
  uint8_t i;
  uint8_t ret_data = 0;

  OLED_SCL(1);
  __nop();

  FondChipGpioSet();

  for(i=0;i<8;i++)
  {
    OLED_FSO(1);
    __nop();
    OLED_SCL(0);
    __nop();

    ret_data = ret_data << 1;

    if( FOND_CHIP_OUT )
    {
      ret_data = ret_data + 1;
      __nop();
    }
    else
    {
      ret_data = ret_data + 0;
      __nop();
    }
    OLED_SCL(1);
  }
  FondChipGpioReset();

  return(ret_data);
}

static void GetBytesDataFromFondChip(uint8_t addrHigh, uint8_t addrMid, \
                                 uint8_t addrLow, uint8_t *pBuff, uint8_t len)
{
  uint8_t i;

  OLED_CS2(0);
  OLED_CS(1);
  OLED_SCL(0);

  SendCmdToFondChip(0x03);
  SendCmdToFondChip(addrHigh);
  SendCmdToFondChip(addrMid);
  SendCmdToFondChip(addrLow);

  for(i = 0; i < len; i++ )
    *(pBuff + i) = GetDataFromFondChip();
  OLED_CS2(1);
}

void DisplayGraphic5x7(uint32_t page, uint32_t column, const uint8_t *ptr)
{
  uint32_t col_cnt;
  uint8_t page_address;
  uint8_t column_address_L, column_address_H;

  page_address = 0xb0 + page - 1;

  OLED_CS(0);

  column_address_L = (column & 0x0f) - 1;
  column_address_H = ((column >> 4) & 0x0f) + 0x10;

  OledTransferCmd(page_address);
  OledTransferCmd(column_address_H);  /*Set MSB of column Address*/
  OledTransferCmd(column_address_L);  /*Set LSB of column Address*/

  for(col_cnt = 0; col_cnt < 6; col_cnt++)
  {
    OledTransferData(*ptr);
    ptr++;
  }
  OLED_CS(1);
}

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
void OledShowString(uint8_t y, uint8_t x, uint8_t *str)
{
  uint8_t i= 0;
  uint8_t addrHigh, addrMid, addrLow;

  while ((str[i] > 0x00))
  {
    if((str[i] >= 0x20) && (str[i] <= 0x7e))
    {
      uint8_t fontbuf[8];

      fontaddr = (str[i] - 0x20);
      fontaddr = (unsigned long)(fontaddr * 8);
      fontaddr = (unsigned long)(fontaddr + 0x3bfc0);
      addrHigh = (fontaddr & 0xff0000) >> 16;
      addrMid = (fontaddr & 0xff00) >> 8;
      addrLow = fontaddr & 0xff;

      GetBytesDataFromFondChip(addrHigh, addrMid, addrLow, fontbuf, 8);
      
      DisplayGraphic5x7(y, x, fontbuf);
      i += 1;
      x += 6;
    }
    else
    i++;
  }
}

/********************************END OF FILE**********************************/
