#include "setting.h"

struct settingsInitTypeDef settings;
struct powerInitTypeDef power;
static __IO uint32_t msTicks;

void SysTick_Handler(void){ msTicks++; }

uint32_t GetTick(void){ return msTicks; }

void DelayMs(uint32_t ms){ uint32_t tickstart = GetTick();
  while((GetTick() - tickstart) < ms){}
}

void DelayMc(uint32_t mc){ mc *= (SystemCoreClock / 1000000) / 9;
  while (mc--);
}

void WriteData32ToBuffer(uint8_t addr, uint32_t data, uint8_t* buff){
  buff[addr + 0x03] = (data >> 0x18);
  buff[addr + 0x02] = (data >> 0x10);
  buff[addr + 0x01] = (data >> 0x08);
  buff[addr] = data; 
}

void WriteData16ToBuffer(uint8_t addr, uint16_t data, uint8_t* buff){
  buff[addr + 0x01] = (data >> 0x08);
  buff[addr] = data;
}

uint32_t ReadData32Buffer(uint8_t addr, uint8_t* buff){
  uint32_t data = buff[addr + 0x03] << 0x18;
  data |= buff[addr + 0x02] << 0x10;
  data |= buff[addr + 0x01] << 0x08;
  data |= buff[addr]; 
  return data;
}

uint16_t ReadData16Buffer(uint8_t addr, uint8_t* buff){
  uint16_t data = buff[addr + 0x01] << 0x08;
  data |= buff[addr];
  return data;
}

void ReadConfig(void){
  #if defined DEBUG_SETTING
    printf("< OK >    Read configuration\r\n");
  #endif
  uint8_t buffEeprom[EEPROM_BUFF];
  Ee24cxxRead(buffEeprom);
  if(0xFF != buffEeprom[ADDR_STATUS]){
    RtcTypeDef dateBuild;
    dateBuild.year  = BUILD_YEAR;
    dateBuild.month = BUILD_MONTH;
    dateBuild.day   = BUILD_DAY;
    dateBuild.hour  = BUILD_TIME_H;
    dateBuild.min   = BUILD_TIME_M;
    dateBuild.sec   = BUILD_TIME_S;
    WriteData32ToBuffer(ADDR_DATE_BUILD, RtcTimeToSeconds(&dateBuild), buffEeprom);
    buffEeprom[ADDR_STATUS] = STATUS;
    buffEeprom[ADDR_DEVICE_TYPE] = DEVICE_TYPE;
    buffEeprom[ADDR_DEVICE_NUMBER] = DEVICE_NUMBER;
    buffEeprom[ADDR_RTC_CALIBRATION] = RTC_CALIBRATION;
    WriteData32ToBuffer(ADDR_CAN_SPEED, CAN_SPEED, buffEeprom);
    WriteData16ToBuffer(ADDR_RS485_SPEED, RS485_SPEED, buffEeprom);
    
    buffEeprom[ADDR_LCD_ROTATION] = LCD_ROTATION;
    buffEeprom[ADDR_TIME_ZONE] = TIME_ZONE;
    //RF24L01
    WriteData16ToBuffer(ADDR_RF24_ADDR, RF24_ADDR, buffEeprom);
    buffEeprom[ADDR_RF24_PRIM] = RF24_PRIM;
    buffEeprom[ADDR_RF24_SECON] = RF24_SECON;
    buffEeprom[ADDR_RF24_SPEED] = RF24_SPEED;
    buffEeprom[ADDR_RF24_POWER] = RF24_POWER;
    buffEeprom[ADDR_RF24_CH] = RF24_CH;
    buffEeprom[ADDR_RF24_TYPE_ON] = 0x00;
    buffEeprom[ADDR_RF24_TYPE_SEND_1] = 0x00;
    buffEeprom[ADDR_RF24_TYPE_ADDR_1] = 0x00;
    buffEeprom[ADDR_RF24_TYPE_SEND_2] = 0x00;
    buffEeprom[ADDR_RF24_TYPE_ADDR_2] = 0x00;
    buffEeprom[ADDR_RF24_TYPE_SEND_3] = 0x00;
    buffEeprom[ADDR_RF24_TYPE_ADDR_3] = 0x00;
    buffEeprom[ADDR_RF24_TYPE_SEND_4] = 0x00;
    buffEeprom[ADDR_RF24_TYPE_ADDR_4] = 0x00;
    
/*----------------------------------------------------------------------------*/
    WriteData16ToBuffer(ADDR_TIMER_START_FRIDGE, TIMER_START_FRIDGE, buffEeprom);
    WriteData16ToBuffer(ADDR_TIMER_START_CONDITIONER, TIMER_START_CONDITIONER, buffEeprom);
    WriteData16ToBuffer(ADDR_TIMER_START_POWER, TIMER_START_POWER, buffEeprom);
    WriteData16ToBuffer(ADDR_TIMER_START_RELAY_4, TIMER_START_BOILER, buffEeprom);
    WriteData32ToBuffer(ADDR_CALIBRATION_ENERGY, CALIBRATION_ENERGY, buffEeprom);
    WriteData16ToBuffer(ADDR_ALARM_POWER, ALARM_POWER, buffEeprom);
/*----------------------------------------------------------------------------*/
    Ee24cxxWrite(buffEeprom);
    
    #if defined DEBUG_SETTING
      printf("          Default configuration\r\n");
    #endif
  }
  settings.dateBuild = ReadData32Buffer(ADDR_DATE_BUILD, buffEeprom);
  settings.type = buffEeprom[ADDR_DEVICE_TYPE];
  settings.number = buffEeprom[ADDR_DEVICE_NUMBER];
  settings.rtcCalib = buffEeprom[ADDR_RTC_CALIBRATION];
  
  settings.rotation = buffEeprom[ADDR_LCD_ROTATION];
  switch(settings.rotation){
    case 0x27:                  //Dspl_Rotation_270
    case 0x09:                  //Dspl_Rotation_90
      settings.width = LCD_WIDTH; 
      settings.height = LCD_HEIGHT;
    break; 
    default:                    //Dspl_Rotation_0 Rotation_180
      settings.width = LCD_HEIGHT; 
      settings.height = LCD_WIDTH;
    break;
  }
  settings.canSpeed = ReadData32Buffer(ADDR_CAN_SPEED, buffEeprom);
  settings.rs485Speed = ReadData16Buffer(ADDR_RS485_SPEED, buffEeprom);
  settings.canDevice = (settings.type << 0x08) | (settings.number << 0x04);
  //RF24L01
  settings.rf24Addr = ReadData16Buffer(ADDR_RF24_ADDR, buffEeprom);
  settings.rf24Prim = buffEeprom[ADDR_RF24_PRIM];
  settings.rf24Secon = buffEeprom[ADDR_RF24_SECON];
  settings.rf24Speed = buffEeprom[ADDR_RF24_SPEED];
  settings.rf24Power = buffEeprom[ADDR_RF24_POWER];
  settings.rf24Ch = buffEeprom[ADDR_RF24_CH];
  settings.rf24TypeOn = buffEeprom[ADDR_RF24_TYPE_ON];
  settings.rf24TypeSend1 = buffEeprom[ADDR_RF24_TYPE_SEND_1];
  settings.rf24TypeAddr1 = buffEeprom[ADDR_RF24_TYPE_ADDR_1];
  settings.rf24TypeSend2 = buffEeprom[ADDR_RF24_TYPE_SEND_2];
  settings.rf24TypeAddr2 = buffEeprom[ADDR_RF24_TYPE_ADDR_2];
  settings.rf24TypeSend3 = buffEeprom[ADDR_RF24_TYPE_SEND_3];
  settings.rf24TypeAddr3 = buffEeprom[ADDR_RF24_TYPE_ADDR_3];
  settings.rf24TypeSend4 = buffEeprom[ADDR_RF24_TYPE_SEND_4];
  settings.rf24TypeAddr4 = buffEeprom[ADDR_RF24_TYPE_ADDR_4];
/*----------------------------------------------------------------------------*/
  timer.fridge = ReadData16Buffer(ADDR_TIMER_START_FRIDGE, buffEeprom);
  timer.conditioner = ReadData16Buffer(ADDR_TIMER_START_CONDITIONER, buffEeprom);
  timer.power = ReadData16Buffer(ADDR_TIMER_START_POWER, buffEeprom);
  timer.boiler = ReadData16Buffer(ADDR_TIMER_START_RELAY_4, buffEeprom);
  power.calibrationEnergy = ReadData32Buffer(ADDR_CALIBRATION_ENERGY, buffEeprom);
  power.alarmPower = ReadData16Buffer(ADDR_ALARM_POWER, buffEeprom);
  
  timer.pause = TIMER_PAUSE_LCD;
  settings.swich = TIMER_GUI_SWICH;
  
/*----------------------------------------------------------------------------*/
  
  dht22.humidity = 0xFFFF;
  dht22.temperature = 0xFFFF;
}

void TIM3_IRQHandler(void){
  TIM3->SR &= ~TIM_SR_UIF;
  S6D0129_CS_LOW;
  switch(settings.guiSwich){
    case 0x01: GuiUpdateTimer();
    break;
    case 0x00: GuiFullWindow(BLACK); GuiPrintIcon(); GuiUpdateTimer(); settings.guiSwich++;
    break;
    case 0x03: GuiUpdatePower();
    break;
    case 0x02: GuiFullWindow(BLACK); GuiPrintFont(); GuiUpdatePower();settings.guiSwich++;
    break;
    default:   GuiFullWindow(BLACK);
    break;
  }
  S6D0129_CS_HIGHT;
  LED_ON;
  En485ReadPower();
  if(settings.start == 0x01){
    if(settings.swich == 0x00){
      if(settings.guiSwich == 0x01){ settings.guiSwich = 0x02; }else{ settings.guiSwich = 0x00; }
      settings.swich = TIMER_GUI_SWICH;
    }else{
      settings.swich--;
    }
  }
  LED_OFF;
}

void TimerInit(void){
  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
  TIM3->PSC = 0x1F3F; // 7999 80000000:8000=10000Hz
//  TIM3->ARR = 0x03E7; // 10Hz
  TIM3->ARR = 0x07CF; // 5Hz
  TIM3->SR = 0x00;
  TIM3->DIER |= TIM_DIER_UIE;
  TIM3->CR1 = TIM_CR1_CEN | TIM_CR1_ARPE;
  
  NVIC_SetPriority(TIM3_IRQn, PRIORITY_TIMER_UPDATE);
  NVIC_EnableIRQ(TIM3_IRQn);
}

void Setting(void){
  #if defined DEBUG_SETTING
    printf("\t\tStart setting\n\r\n");
  #endif
  SysTick_Config(SystemCoreClock / 1000);   //1ms
  
  RCC->APB1ENR |= RCC_APB1ENR_PWREN;
  RCC->APB1ENR |= RCC_APB1ENR_BKPEN;
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
  
  AFIO->MAPR = AFIO_MAPR_SWJ_CFG_JTAGDISABLE + AFIO_MAPR_TIM2_REMAP_FULLREMAP;
  
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
  RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
  RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
  
  TimerGpioInit();
  Ee24cxxInit();
  ReadConfig();
  W25QxxInit();
  LcdInit();
  GuiInit();
  En485Init();
  Ds18b20Init();
  Dht22Init();
  CanInit();
  Rs485Init();
  Nrf24Init();
  BeepInit();
  RtcInit();
  TimerInit();
  #if defined DEBUG_SETTING
    printf("\t\tStop setting\n\r\n");
  #endif
}
