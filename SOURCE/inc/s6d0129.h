#ifndef _S6D0129_H
#define _S6D0129_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "setting.h"
#include "gui.h"

/* Define --------------------------------------------------------------------*/
#define S6D0129_RESET_LOW         GPIOD->BSRR = GPIO_BSRR_BR2
#define S6D0129_RESET_HIGHT       GPIOD->BSRR = GPIO_BSRR_BS2

#define S6D0129_WR_LOW            GPIOA->BSRR = GPIO_BSRR_BR1
#define S6D0129_WR_HIGHT          GPIOA->BSRR = GPIO_BSRR_BS1

#define S6D0129_RS_COM            GPIOA->BSRR = GPIO_BSRR_BR2
#define S6D0129_RS_DATA           GPIOA->BSRR = GPIO_BSRR_BS2

#define S6D0129_CS_LOW            GPIOA->BSRR = GPIO_BSRR_BR3
#define S6D0129_CS_HIGHT          GPIOA->BSRR = GPIO_BSRR_BS3

void LcdWriteCom(uint8_t cmd);
void LcdWriteData(uint8_t data);
void LcdWriteComData(uint8_t cmd, uint16_t data);
void LcdInit(void);

#endif /* _S6D0129_H */
