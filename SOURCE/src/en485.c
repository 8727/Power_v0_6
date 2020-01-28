#include "en485.h"

struct En485InitTypeDef en485;

static const uint8_t resetEnergy[] = {0x01, 0x42, 0x80, 0x11};
static const uint8_t requestPower[] = {0x01, 0x04, 0x00, 0x00, 0x00, 0x0A, 0x70, 0x0D};

uint16_t crc16(uint8_t *buf, uint8_t len){
  uint8_t nTemp;
  uint16_t wCRCWord = 0xFFFF;
  while (len--){
    nTemp = *buf++ ^ wCRCWord;
    wCRCWord >>= 0x08;
    wCRCWord ^= crc16Tab[nTemp];
  }
  return wCRCWord;
}

void En485Sends(uint8_t *str, uint8_t len){
  uint8_t i = 0x00;
  while(len--){
    en485.txBuff[en485.txStop++] = str[i++];
  }
  EN485_TX;
  UART4->CR1 |= USART_CR1_TXEIE;
}

void Rs485ResetEnergy(void){
  En485Sends((uint8_t*)resetEnergy, 0x04);
}

void En485SetAlarm(void){
  uint8_t temp[0x08];
  temp[0x00] = 0x01;
  temp[0x01] = 0x06;
  temp[0x02] = 0x00;
  temp[0x03] = 0x01;
  temp[0x04] = (power.alarmPower >> 0x08);
  temp[0x05] =  power.alarmPower;
  uint16_t crc = crc16(temp, 0x06);
  temp[0x06] =  crc;
  temp[0x07] = (crc >> 0x08);
  En485Sends((uint8_t*)temp, 0x08);
}

void En485ReadPower(void){
  uint16_t crcCalc = 0x00;
  uint8_t temp[0x20];
  uint8_t i = 0x00;
  if(en485.rxStart != en485.rxStop){
    do{
      temp[i++] = en485.rxBuff[en485.rxStart++];
    }while(en485.rxStart != en485.rxStop);
    crcCalc = crc16(temp, (i - 0x02));
    if(crcCalc == (temp[temp[0x02] + 0x03] | (temp[temp[0x02] + 0x04] << 0x08))){
      power.voltage = (temp[0x03] << 0x08) | temp[0x04];
      power.current = (temp[0x07] << 0x18) | (temp[0x08] << 0x10) | (temp[0x05] << 0x08) | temp[0x06];
      power.activePower = (temp[0x0B] << 0x18) | (temp[0x0C] << 0x10) | (temp[0x09] << 0x08) | temp[0x0A];
      power.activeEnergy = (temp[0x0F] << 0x18) | (temp[0x10] << 0x10) | (temp[0x0D] << 0x08) | temp[0x0E];
      power.frequency = (temp[0x11] << 0x08) | temp[0x12];
      power.powerFctor = (temp[0x13] << 0x08) | temp[0x14];
      power.alarm = (temp[0x15] << 0x08) | temp[0x16];
    }
  }
  En485Sends((uint8_t*)requestPower, 0x08);
}

void UART4_IRQHandler(void){
  if(UART4->SR & USART_SR_RXNE){
    UART4->SR &= ~USART_SR_RXNE;
    en485.rxBuff[en485.rxStop++] = UART4->DR;
  }
  if(UART4->SR & USART_SR_TXE){
    if (en485.txStart != en485.txStop){
      UART4->DR = en485.txBuff[en485.txStart++];
    }else{
      UART4->CR1 &= ~USART_CR1_TXEIE;
    }
  }
  if(UART4->SR & USART_SR_TC){
    UART4->SR &= ~USART_SR_TC;
    EN485_RX;
  }
}

void En485Init(void){
  GPIOC->CRH &= ~(GPIO_CRH_CNF10 | GPIO_CRH_CNF11 | GPIO_CRH_CNF12);
  GPIOC->CRH |= (GPIO_CRH_MODE12 | GPIO_CRH_CNF10_1 | GPIO_CRH_MODE10 | GPIO_CRH_CNF11_0);
  EN485_RX;
  
  RCC->APB1ENR|= RCC_APB1RSTR_UART4RST;
  UART4->BRR = 0x208D;
  UART4->CR1 |= USART_CR1_TE | USART_CR1_RE;
  UART4->CR1 |= USART_CR1_RXNEIE;
//  UART4->CR1 |= USART_CR1_IDLEIE;
  UART4->CR1 |= USART_CR1_TCIE;
  UART4->CR1 |= USART_CR1_UE;
  
  NVIC_SetPriority(UART4_IRQn, PRIORITY_EN485);
  NVIC_EnableIRQ(UART4_IRQn);
  
  #if defined DEBUG_EN485
    printf("< OK >    Initialization EN485\r\n");
  #endif
}
