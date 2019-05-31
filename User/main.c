/**
  * @file    main.c
  * @author  WANG Kyle
  * @email   x-box361@live.com
  * @version V0.1
  * @date    25-May-2019
  * @brief   Just to test basic OLED feature.
  */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "stm32f10x.h"
#include "bsp_systick.h"
#include "bsp_usart.h"
#include "oled_gpio.h"

#include "car_msg.h"

int main(void)
{
  int i = 0;
  float vel_x = 0;
  CarStatus car_status;

  /* Requests the memory to store the result of sprintf. */
  char *vel_fl_buf    = (char *)malloc(sizeof(float) + 1);
  char *vel_rl_buf    = (char *)malloc(sizeof(float) + 1);
  char *vel_l_set_buf = (char *)malloc(sizeof(float) + 1);

  char *vel_fr_buf    = (char *)malloc(sizeof(float) + 1);
  char *vel_rr_buf    = (char *)malloc(sizeof(float) + 1);
  char *vel_r_set_buf = (char *)malloc(sizeof(float) + 1);

  char *vel_x_buf     = (char *)malloc(sizeof(float) + 1);
  char *vel_theta_buf = (char *)malloc(sizeof(float) + 1);

  /* Initializes OLED. */
  InitOLED();

  /* Clears OLED screen. */
  OledClearScreen();

  /* Starts initializing other peripherals. */
  OledShowString(4, 1, (uint8_t *)"Initializing...");

  /* Configures the interrupt groups */
  //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  USART_Config();

  /* Initialization of other peripherals completed. */
  OledClearScreen();

  memset(vel_fl_buf, 0, sizeof(float) + 1);
  memset(vel_rl_buf, 0, sizeof(float) + 1);
  memset(vel_l_set_buf, 0, sizeof(float) + 1);
  memset(vel_fr_buf, 0, sizeof(float) + 1);
  memset(vel_rr_buf, 0, sizeof(float) + 1);
  memset(vel_r_set_buf, 0, sizeof(float) + 1);
  memset(vel_x_buf, 0, sizeof(float) + 1);
  memset(vel_theta_buf, 0, sizeof(float) + 1);

  printf("A sample OLED show\n");

  /* Initializes the original graph of OLED. */
  OledShowString(1, 1, (uint8_t *)"       SPACE-V       ");
  OledShowString(2, 1, (uint8_t *)"---------------------");
  OledShowString(3, 1, (uint8_t *)"vel:        ang:     ");
  OledShowString(4, 1, (uint8_t *)"---------------------");
  OledShowString(5, 1, (uint8_t *)"   L      R      set ");
  OledShowString(6, 1, (uint8_t *)"F:             |     ");
  OledShowString(7, 1, (uint8_t *)"R:             |     ");
  OledShowString(8, 1, (uint8_t *)"_____________________");

  while(1)
  {
    /* Just for testing. */
    for (i = 0; i < 999; i++)
    {
      /* You need to implement the meaningful value to the variable. */
      car_status.vel_front_left  = (float)i/100.0;
      car_status.vel_rear_left   = (float)i/100.0;
      car_status.vel_left_set    = (float)i/100.0;

      car_status.vel_front_right = (float)i/100.0;
      car_status.vel_rear_right  = (float)i/100.0;
      car_status.vel_right_set   = (float)i/100.0;

      car_status.vel_theta       = (float)i/100.0;
      vel_x = (car_status.vel_rear_left 
              + car_status.vel_rear_right) / 2.0;

      /* Converts the float/int variable to string. */
      sprintf(vel_fl_buf, "%2.2f", car_status.vel_front_left);
      sprintf(vel_rl_buf, "%2.2f", car_status.vel_rear_left);
      sprintf(vel_l_set_buf, "%2.2f", car_status.vel_left_set);
      sprintf(vel_fr_buf, "%2.2f", car_status.vel_front_right);
      sprintf(vel_rr_buf, "%2.2f", car_status.vel_rear_right);
      sprintf(vel_r_set_buf, "%2.2f", car_status.vel_right_set);
      sprintf(vel_theta_buf, "%2.2f", car_status.vel_theta);
      sprintf(vel_x_buf, "%2.2f", vel_x);

      /* 
       * One character occupies 5 dots in raw,
       * plus the interval between characters,
       * using n*6 for the position of this character.
       */
      OledShowString(3, 5*6+1, (uint8_t *)vel_x_buf);
      OledShowString(3, 17*6+1, (uint8_t *)vel_theta_buf);

      OledShowString(6, 3*6+1, (uint8_t *)vel_fl_buf);
      OledShowString(6, 10*6+1, (uint8_t *)vel_fr_buf);
      OledShowString(6, 17*6+1, (uint8_t *)vel_l_set_buf);

      OledShowString(7, 3*6+1, (uint8_t *)vel_rl_buf);
      OledShowString(7, 10*6+1, (uint8_t *)vel_rr_buf);
      OledShowString(7, 17*6+1, (uint8_t *)vel_r_set_buf);

      DelayMs(100);
    }
  }
  
  free(vel_fl_buf);
  free(vel_rl_buf);
  free(vel_l_set_buf);
  free(vel_fr_buf);
  free(vel_rr_buf);
  free(vel_r_set_buf);
  free(vel_theta_buf);
  free(vel_x_buf);

  return 0;
}


