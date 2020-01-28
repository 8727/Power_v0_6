#ifndef _EN485_H
#define _EN485_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "setting.h"
#include "crc16.h"

/* Define --------------------------------------------------------------------*/
#define SIZE_BUFF_EN485                     0x0100

#define EN485_TX                            GPIOC->BSRR = GPIO_BSRR_BS12
#define EN485_RX                            GPIOC->BSRR = GPIO_BSRR_BR12

struct En485InitTypeDef{
  uint8_t rxBuff[SIZE_BUFF_EN485];
  uint8_t txBuff[SIZE_BUFF_EN485];
  uint8_t rxStart;
  uint8_t rxStop;
  uint8_t txStart;
  uint8_t txStop;
};

extern struct En485InitTypeDef en485;

void En485Sends(uint8_t *str, uint8_t len);
void En485ResetEnergy(void);
void En485SetAlarm(void);
void En485ReadPower(void);
void En485Init(void);

#endif /* _EN485_H */
