#ifndef _SETTING_H
#define _SETTING_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "main.h"
#include "start_timer.h"
#include "Ee24cxx.h"
#include "rtc.h"
#include "ds18b20.h"
#include "dht22.h"
#include "nrf24.h"
#include "rs485.h"
#include "en485.h"
#include "can.h"
#include "w25qxx.h"
#include "s6d0129.h"
#include "beep.h"

/* Define --------------------------------------------------------------------*/
#define HW_BUILD                         "0.06"      // "0.06" 0x302E3036
#define SW_BUILD                         "1.00"      // "1.00" 0x312E3033
#define STATUS                           'D'         // 0x44 -default "D",
#define DEVICE_TYPE                      0x02        // Device type  0x00 = Core, 0x01 = Water, 0x02 = Power/Timer start, 0x03 = SW
#define DEVICE_NUMBER                    0x00        // Device number
#define RTC_CALIBRATION                  0x00        // RTC CalibrationPpm
#define LCD_ROTATION                     0x09        // 0x27 Rotation_270, 0x18 Rotation_180, 0x09 Rotation_90, 0x00 Rotation_0
#define LCD_WIDTH                        0x0140
#define LCD_HEIGHT                       0x00F0
#define TIME_ZONE                        0x00        //

#define RF24_ADDR                        0x8727      //
#define RF24_PRIM                        0x70
#define RF24_SECON                       0x71
#define RF24_SPEED                       0x01        // 0x00  1Mbps, 0x01  2Mbps, 0x10 250kbps
#define RF24_POWER                       0x03        // 0x00 -18dBm, 0x01 -12dBm, 0x02 -6dBm, 0x03 0dBm
#define RF24_CH                          0x70        // 0-125 0x00-0x7D

#define TIMER_START_POWER                0x0130      //    5 min  4 sec
#define TIMER_START_FRIDGE               0x0260      //   10 min  8 sec
#define TIMER_START_CONDITIONER          0x0390      //   15 min 12 sec
#define TIMER_START_BOILER               0x0000      // 1092 min 15 sec
#define CALIBRATION_ENERGY               0x0000
#define ALARM_POWER                      0x0898      // 2200 W

#define TIMER_PAUSE_LCD                  0x05
#define TIMER_GUI_SWICH                  0x0F


//#define HEATING_MAX_DEVICES              0x05
//#define DS18B20_MAX_DEVICES              0x08

#define EEPROM_BUFF                      0x80

/* Define --------------------------------------------------------------------*/
#define CanModeNormal                    0x00
#define CanModeLoopBack                  CAN1->BTR |= CAN_BTR_LBKM
#define CanModeSilent                    CAN1->BTR |= CAN_BTR_SILM
#define CanModeSilentLoopBack            CAN1->BTR |= (CAN_BTR_SILM | CAN_BTR_LBKM)

#define CAN_SPEED                        0x001C0004  //0x00050004 // 1000 Kb
                                                     //0x001C0004 // 500 Kb
                                                     //0x001C0009 // 250 Kb
                                                     //0x001C0013 // 125 Kb
                                                     //0x001C0018 // 100 Kb

#define RS485_SPEED                      0x208D      //0x0057       //921600
                                                     //0x00A0       //500000
                                                     //0x00AE       //460800
                                                     //0x0140       //250000
                                                     //0x015B       //230400
                                                     //0x0000       //125000
                                                     //0x02B6       //115200
                                                     //0x056D       //57600
                                                     //0x0823       //38400
                                                     //0x208D       //9600

#define USART_2_3_SPEED_1152             0x015B      //0x002B       //921600
#define USART_2_3_SPEED_96               0x1047      //0x0050       //500000
                                                     //0x0057       //460800
                                                     //0x00A0       //250000
                                                     //0x00AE       //230400
                                                     //0x0000       //125000
                                                     //0x015B       //115200
                                                     //0x02B6       //57600
                                                     //0x0412       //38400
                                                     //0x0823       //19200
                                                     //0x1047       //9600

/* Define --------------------------------------------------------------------*/
#define ADDR_DATE_BUILD                  0x00 // 0x00-0x03
#define ADDR_STATUS                      0x04
#define ADDR_DEVICE_NUMBER               0x05
#define ADDR_DEVICE_TYPE                 0x06
#define ADDR_RTC_CALIBRATION             0x07
#define ADDR_TIME_ZONE                   0x08
#define ADDR_LCD_ROTATION                0x09
#define ADDR_CAN_SPEED                   0x0A // 0x0A-0x0D
#define ADDR_RS485_SPEED                 0x0E // 0x0E-0x0F
#define ADDR_RF24_ADDR                   0x10 // 0x10-0x11
#define ADDR_RF24_PRIM                   0x12
#define ADDR_RF24_SECON                  0x13
#define ADDR_RF24_SPEED                  0x14
#define ADDR_RF24_POWER                  0x15
#define ADDR_RF24_CH                     0x16
#define ADDR_RF24_TYPE_ON                0x17
#define ADDR_RF24_TYPE_SEND_1            0x18
#define ADDR_RF24_TYPE_ADDR_1            0x19
#define ADDR_RF24_TYPE_SEND_2            0x1A
#define ADDR_RF24_TYPE_ADDR_2            0x1B
#define ADDR_RF24_TYPE_SEND_3            0x1C
#define ADDR_RF24_TYPE_ADDR_3            0x1D
#define ADDR_RF24_TYPE_SEND_4            0x1E
#define ADDR_RF24_TYPE_ADDR_4            0x1F
#define ADDR_________X                   0x20 // 0x20-0x2F

/* Define --------------------------------------------------------------------*/
#define ADDR_TIMER_START_FRIDGE          0x30 // 0x30-0x31
#define ADDR_TIMER_START_CONDITIONER     0x32 // 0x32-0x33
#define ADDR_TIMER_START_POWER           0x34 // 0x34-0x35
#define ADDR_TIMER_START_RELAY_4         0x36 // 0x36-0x37
#define ADDR_CALIBRATION_ENERGY          0x3A // 0x3A-0x3D
#define ADDR_ALARM_POWER                 0x3E // 0x3E-0x3F

/* Define --------------------------------------------------------------------*/
#define PRIORITY_DHT22_DMA               0x0F
#define PRIORITY_RTC                     0x0E
#define PRIORITY_RS485                   0x01
#define PRIORITY_EN485                   0x00
#define PRIORITY_TIMER_UPDATE            0x00

#define PRIORITY_DS18B20                 0x00
#define PRIORITY_DHT22_TIM               0x00

#define PRIORITY_CAN_TX                  0x00
#define PRIORITY_CAN_RX0                 0x00
#define PRIORITY_CAN_RX1                 0x00
#define PRIORITY_CAN_ERROR               0x00
#define PRIORITY_RF24                    0x00

/* Define --------------------------------------------------------------------*/
struct settingsInitTypeDef{
  uint32_t dateBuild;
  uint8_t  number;
  uint8_t  type;
  uint8_t  rtcCalib;
  uint32_t canSpeed;
  uint16_t rs485Speed;
  uint8_t  rotation;
  int8_t   timeZone;
  uint16_t canDevice;
  uint32_t uptime;
  // LCD
  uint16_t width;
  uint16_t height;
  //RF24L01
  uint16_t rf24Addr;
  uint8_t  rf24Prim;
  uint8_t  rf24Secon;
  uint8_t  rf24Speed;
  uint8_t  rf24Power;
  uint8_t  rf24Ch;
  uint8_t  rf24TypeOn;
  uint8_t  rf24TypeSend1;
  uint8_t  rf24TypeAddr1;
  uint8_t  rf24TypeSend2;
  uint8_t  rf24TypeAddr2;
  uint8_t  rf24TypeSend3;
  uint8_t  rf24TypeAddr3;
  uint8_t  rf24TypeSend4;
  uint8_t  rf24TypeAddr4;
  //Timer
  uint8_t  start;
  uint8_t  swich;
  uint8_t  guiSwich;
};

struct powerInitTypeDef{
  uint32_t activeEnergy;
  uint32_t activePower;
  uint16_t voltage;
  uint32_t current;
  uint8_t  powerFctor;
  uint16_t frequency;
  uint16_t alarm;
  uint32_t calibrationEnergy;
  uint16_t alarmPower;
};

extern struct settingsInitTypeDef settings;
extern struct powerInitTypeDef power;

uint32_t GetTick(void);
void DelayMs(uint32_t ms);
void DelayMc(uint32_t mc);

void WriteData32ToBuffer(uint8_t addr, uint32_t data, uint8_t* buff);
void WriteData16ToBuffer(uint8_t addr, uint16_t data, uint8_t* buff);
uint32_t ReadData32Buffer(uint8_t addr, uint8_t* buff);
uint16_t ReadData16Buffer(uint8_t addr, uint8_t* buff);

void ReadConfig(void);
void Setting(void);

#endif /* _SETTING_H */
