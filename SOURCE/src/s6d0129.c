#include "s6d0129.h"

void LcdWriteCom(uint8_t cmd){
  S6D0129_RS_COM;
  GPIOC->ODR = cmd;
  S6D0129_WR_LOW;
  S6D0129_WR_HIGHT;
  S6D0129_RS_DATA;
}

void LcdWriteData(uint8_t data){
  GPIOC->ODR = data;
  S6D0129_WR_LOW;
  S6D0129_WR_HIGHT;
}

void LcdWriteComData(uint8_t cmd, uint16_t data){
  S6D0129_RS_COM;
  GPIOC->ODR = cmd;
  S6D0129_WR_LOW;
  S6D0129_WR_HIGHT;
  S6D0129_RS_DATA;
  GPIOC->ODR = (data >> 0x08);
  S6D0129_WR_LOW;
  S6D0129_WR_HIGHT;
  GPIOC->ODR = data;
  S6D0129_WR_LOW;
  S6D0129_WR_HIGHT;
}

void LcdInit(void){
  GPIOC->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_CNF1 | GPIO_CRL_CNF2 | GPIO_CRL_CNF3 |
                  GPIO_CRL_CNF4 | GPIO_CRL_CNF5 | GPIO_CRL_CNF6 | GPIO_CRL_CNF7);
  GPIOC->CRL |= GPIO_CRL_MODE0 | GPIO_CRL_MODE1 | GPIO_CRL_MODE2 | GPIO_CRL_MODE3 |
                GPIO_CRL_MODE4 | GPIO_CRL_MODE5 | GPIO_CRL_MODE6 | GPIO_CRL_MODE7;
  
  GPIOA->CRL &= ~(GPIO_CRL_CNF1 | GPIO_CRL_CNF2 | GPIO_CRL_CNF3);
  GPIOA->CRL |= GPIO_CRL_MODE1 | GPIO_CRL_MODE2 | GPIO_CRL_MODE3;
  
  GPIOD->CRL &= ~(GPIO_CRL_CNF2);
  GPIOD->CRL |= GPIO_CRL_MODE2;
  
  S6D0129_CS_HIGHT;
  S6D0129_WR_HIGHT;
  S6D0129_RS_DATA;
  S6D0129_RESET_HIGHT;
  DelayMs(0x05); // 5ms
  S6D0129_RESET_LOW;
  DelayMs(0x05); // 5ms
  S6D0129_RESET_HIGHT;
  DelayMs(0x05); // 5ms
  
  S6D0129_CS_LOW;
  
  LcdWriteComData(0x00,0x0001);
  DelayMs(0x64);
  
  LcdWriteComData(0x11,0x2E00);
  LcdWriteComData(0x14,0x040B);
  LcdWriteComData(0x10,0x1040);
  DelayMs(0x0A); 
  LcdWriteComData(0x13,0x0040);
  DelayMs(0x0A); 
  LcdWriteComData(0x13,0x0060);
  DelayMs(0x0A); 
  LcdWriteComData(0x13,0x0070);
  DelayMs(0x06); 
  LcdWriteComData(0x11,0x3704);
  LcdWriteComData(0x10,0x1600);
  DelayMs(0x02);
  LcdWriteComData(0x01,0x0B27);
  LcdWriteComData(0x02,0x0700);
  
  switch(settings.rotation){
    case 0x27: LcdWriteComData(0x03,0x1010);  //LCD_Rotation_270
    break;
    case 0x18: LcdWriteComData(0x03,0x1030);  //LCD_Rotation_180
    break;
    case 0x09: LcdWriteComData(0x03,0x1038);  //LCD_Rotation_90
    break;
    default: LcdWriteComData(0x03,0x1030);    //LCD_Rotation_0
    break;
  }
  
  LcdWriteComData(0x07,0x0004);
  LcdWriteComData(0x08,0x0505);
  LcdWriteComData(0x09,0x0000);
  LcdWriteComData(0x0B,0x0000);
  LcdWriteComData(0x0C,0x0000);
  
  LcdWriteComData(0x40,0x0000);
  LcdWriteComData(0x46,0xEF00);
  LcdWriteComData(0x47,0x013F);
  LcdWriteComData(0x48,0x0000);
  DelayMs(0x05);
  
  LcdWriteComData(0x30,0x0000);
  LcdWriteComData(0x31,0x0006);
  LcdWriteComData(0x32,0x0000);
  LcdWriteComData(0x33,0x0000);
  LcdWriteComData(0x34,0x0707);
  LcdWriteComData(0x35,0x0700);
  LcdWriteComData(0x36,0x0303);
  LcdWriteComData(0x37,0x0007);
  LcdWriteComData(0x38,0x1100);
  LcdWriteComData(0x39,0x1100);
  
  LcdWriteComData(0x07,0x0015);
  DelayMs(0x04);
  LcdWriteComData(0x07,0x0017);
  DelayMs(0x04);
  
  LcdWriteComData(0x20,0x0000);
  LcdWriteComData(0x21,0x0000);
  LcdWriteCom(0x22);
  
  S6D0129_CS_HIGHT;
}
