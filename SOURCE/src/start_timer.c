#include "start_timer.h"

struct timerInitTypeDef timer;

void TimerUpdate(void){
    if(timer.fridge == 0x00){
      FRIDGE_ON;
      GuiPrintIcons(0x00, GREEN);
      settings.start = 0x01;
    }else{
      timer.fridge --;
    }
    if(timer.conditioner == 0x00){
      CONDITIONER_ON;
      GuiPrintIcons(0x01, GREEN);
      settings.start = 0x01;
    }else{
     timer.conditioner --;
    }
    if(timer.power == 0x00){
      POWER_ON;
      GuiPrintIcons(0x02, GREEN);
      settings.start = 0x01;
    }else{
      timer.power --;
    }
    if(timer.boiler == 0x00){
      BOILER_ON;
//      GuiPrintIcons(0x02, GREEN);
//      settings.start = 0x01;
    }else{
      timer.boiler --;
    }
    if(timer.fridge == 0x00 & timer.conditioner == 0x00 & timer.power == 0x00 & timer.boiler == 0x00 & timer.pause != 0x00){
    timer.pause --;
    if (timer.pause == 0x00){
      settings.start = 0x02;
      settings.guiSwich = 0x02;
    }
  }
}

void TimerGpioInit(void){
  CONDITIONER_OFF;
  BOILER_OFF;
  POWER_OFF;
  FRIDGE_OFF;
  
  GPIOB->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_CNF4 | GPIO_CRL_CNF5 | GPIO_CRH_CNF8 | GPIO_CRH_CNF9);     // LED POWER FRIDGE BOILER CONDITIONER
  GPIOB->CRL |= GPIO_CRL_MODE0 | GPIO_CRL_MODE4 | GPIO_CRL_MODE5 | GPIO_CRH_MODE8 | GPIO_CRH_MODE9;   // LED POWER FRIDGE BOILER CONDITIONER
}
