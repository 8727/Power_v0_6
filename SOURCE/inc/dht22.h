#ifndef _DHT22_H
#define _DHT22_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "setting.h"

/* Define --------------------------------------------------------------------*/
#define  BITBAND_RAMADR(xAdr, xBit)      ((uint32_t *)(SRAM_BB_BASE + ((xAdr - SRAM_BASE) * 32) + (xBit * 4)))

struct Dht22InitTypeDef{
  uint16_t dataBuff[42];
  uint16_t humidity;
  uint16_t temperature;
};

extern struct Dht22InitTypeDef dht22;

void Dht22Init(void);

#endif /* _DHT22_H */
