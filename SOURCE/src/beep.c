#include "beep.h"


void BeepInit(void){
  GPIOB->CRH |= GPIO_CRL_MODE1;
  GPIOB->CRH &= ~(GPIO_CRL_CNF1);
  
  #if defined DEBUG_BEEP
    printf("< OK >    Initialization BEEP\r\n");
  #endif
}
