/**
  * @file    car_msg.h
  * @author  WANG Kyle
  * @email   x-box361@live.com
  * @version V0.1
  * @date    25-May-2019
  * @brief   This file provides the message definition. 
  */

#ifndef __CAR_MSG_H
#define __CAR_MSG_H

typedef struct
{
  float vel_front_left;
  float vel_rear_left;
  float vel_left_set;

  float vel_front_right;
  float vel_rear_right;
  float vel_right_set;

  float vel_theta;
} CarStatus;

#endif /* __CAR_MSG_H */

/********************************END OF FILE**********************************/
