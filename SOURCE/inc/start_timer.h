#ifndef _START_TIMER_H
#define _START_TIMER_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "setting.h"
#include "gui.h"

/* Define --------------------------------------------------------------------*/
#define LED_ON                    GPIOB->BSRR = GPIO_BSRR_BR0
#define LED_OFF                   GPIOB->BSRR = GPIO_BSRR_BS0

#define POWER_ON                  GPIOB->BSRR = GPIO_BSRR_BR4
#define POWER_OFF                 GPIOB->BSRR = GPIO_BSRR_BS4

#define FRIDGE_ON                 GPIOB->BSRR = GPIO_BSRR_BR5
#define FRIDGE_OFF                GPIOB->BSRR = GPIO_BSRR_BS5

#define BOILER_ON                 GPIOB->BSRR = GPIO_BSRR_BR8
#define BOILER_OFF                GPIOB->BSRR = GPIO_BSRR_BS8

#define CONDITIONER_ON            GPIOB->BSRR = GPIO_BSRR_BR9
#define CONDITIONER_OFF           GPIOB->BSRR = GPIO_BSRR_BS9


struct timerInitTypeDef{
  uint16_t fridge;
  uint16_t conditioner;
  uint16_t power;
  uint16_t boiler;
  uint8_t  pause;
};
extern struct timerInitTypeDef timer;

void TimerUpdate(void);
void TimerGpioInit(void);

#endif /* _START_TIMER_H */
