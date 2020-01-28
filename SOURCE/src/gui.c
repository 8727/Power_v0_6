#include "gui.h"

struct TableInitTypeDef img[0x0100];
//struct GuiInitTypeDef gui;

void GuiSetWindow(uint16_t x, uint16_t y, uint16_t width, uint16_t height){
  if(settings.width < width) width = settings.width;
  if(settings.height < height) height = settings.height;
  if(settings.width < (x + width)) x = settings.width - width;
  if(settings.height <(y + height)) y = settings.height - height;
  
  LcdWriteCom(0x46);
  LcdWriteData(y + height - 0x01);
  LcdWriteData(y);
  LcdWriteComData(0x47,(x + width - 0x01));
  LcdWriteComData(0x48,x);
  LcdWriteComData(0x20,y);
  LcdWriteComData(0x21,x);
  LcdWriteCom(0x22);
}

void GuiFullWindow(uint16_t color){
  uint32_t i = settings.width * settings.height;
  GuiSetWindow(0x00, 0x00, settings.width, settings.height);
  while(i--){
    GPIOC->ODR = (color >> 0x08);
    S6D0129_WR_LOW;
    S6D0129_WR_HIGHT;
    GPIOC->ODR = color;
    S6D0129_WR_LOW;
    S6D0129_WR_HIGHT;
  }
}

void GuiDrawPixel(uint16_t color){
  GPIOC->ODR = (color >> 0x08);
  S6D0129_WR_LOW;
  S6D0129_WR_HIGHT;
  GPIOC->ODR = color;
  S6D0129_WR_LOW;
  S6D0129_WR_HIGHT;
}

//void GuiCalibDraw(uint16_t x, uint16_t y){
//  uint32_t c;
//  GuiSetWindow(x - 0x0F, y - 0x0F, 0x20, 0x20);
//  for(uint8_t i = 0x00; i < 0x20; i++){
////    c = calibDraw[i];
//    for(uint8_t z = 0x00; z < 0x20; z++){
//      if(c & 0x80000000){
//        GuiDrawPixel(BLACK);
//      }else{
//        GuiDrawPixel(WHITE);
//      }
//      c <<= 0x01;
//    }
//  }
//}

//void GuiCalibErase(uint16_t x, uint16_t y){
//  GuiSetWindow(x - 0x0F, y - 0x0F, 0x20, 0x20);
//  uint16_t i = 0x0400;
//  while(i--){
//    GuiDrawPixel(WHITE);
//  }
//}

//void GuiFullWindow(uint16_t color){
//  uint32_t i = settings.width * settings.height;
//  GuiSetWindow(0x00, 0x00, settings.width, settings.height);
//  while(i--){
//    GuiDrawPixel(color);
//  }
//}

//void GuiEraseW25qxx(void){
//  uint16_t i = (w25qxx.blocks + 0x08) * 0x28;
//  GuiFullWindow(BLACK);
//  GuiSetWindow(((settings.width - w25qxx.blocks ) / 0x02) - 0x04, (settings.height / 0x02) - 0x14, w25qxx.blocks + 0x08, 0x28);
//    while(i--){
//    GuiDrawPixel(WHITE);
//  }
//}

//void GuiEraseBlocks(uint8_t block){
//  uint8_t i = 0x32;
//  GuiSetWindow(((settings.width - w25qxx.blocks) / 0x02) + block, (settings.height / 0x02) - 0x10, 0x01, 0x20);
//  while(i--){
//    GuiDrawPixel(RED);
//  }
//}

//void GuiBr(void){
//  uint8_t c;
//  uint8_t br = 249;
//  for(uint8_t x = 0x00; x < 0x32; x++){
//    GuiSetWindow(0x0F + x * 0x09, 0x04, 0x08, 0x10);
//    for(uint8_t i = 0x00; i < 0x10; i++){
//      if((x * 5.1) < br){
//        c = brOn[i];
//      }else{
//        c = brOff[i];
//      }
//      for(uint8_t z = 0x00; z < 0x08; z++){
//        if(c & 0x80){
//          LCD_DATA = BLACK;
//        }else{
//          LCD_DATA = WHITE;
//        }
//        c <<= 0x01;
//      }
//    }
//  }
//}

//void DMA1_Channel2_IRQHandler(void){
//  DMA1->IFCR |= DMA_IFCR_CGIF2;
//  DMA1_Channel2->CCR &= ~DMA_CCR2_EN;
//  DMA1_Channel3->CCR &= ~DMA_CCR3_EN;
//  if(0x00 < gui.step){
//    gui.step--;
//    DMA1_Channel2->CNDTR = 0xFFFF;
//    DMA1_Channel3->CNDTR = 0xFFFF;
//    DMA1_Channel2->CCR |= DMA_CCR2_EN;
//    DMA1_Channel3->CCR |= DMA_CCR3_EN;
//  }else{
//    SPI1->CR1 &= ~SPI_CR1_DFF;
//    SPI1->CR2 &= ~(SPI_CR2_RXDMAEN | SPI_CR2_TXDMAEN);
//    W25Qxx_CS_HIGHT;
//  }
//}

//void GuiLoadImg(uint16_t x, uint16_t y, uint8_t numb){
//  uint32_t pixel = img[numb].width * img[numb].height;
//  GuiSetWindow(x, y, img[numb].width, img[numb].height);
//  if(0x025800 < pixel) pixel =  0x025800;
//  if(0xFFFF < pixel){
//    gui.step = pixel / 0xFFFF;
//    DMA1_Channel2->CNDTR = pixel - gui.step * 0xFFFF;
//    DMA1_Channel3->CNDTR = pixel - gui.step * 0xFFFF;
//  }else{
//    DMA1_Channel2->CNDTR = pixel;
//    DMA1_Channel3->CNDTR = pixel;
//  }
//  W25Qxx_CS_LOW;
//  W25QxxWriteRead(CMD_FAST_READ);
//  W25QxxWriteRead(img[numb].address >> 0x08);
//  W25QxxWriteRead(img[numb].address & 0x00FF);
//  W25QxxWriteRead(0x00);
//  W25QxxWriteRead(0x00);
//  SPI1->CR1 |= SPI_CR1_DFF;
//  SPI1->CR2 |= SPI_CR2_RXDMAEN | SPI_CR2_TXDMAEN;
//  DMA1_Channel2->CCR |= DMA_CCR2_EN;
//  DMA1_Channel3->CCR |= DMA_CCR3_EN;
//}

void GuiPrintSign(uint8_t height, uint8_t width, uint32_t *buffLine, uint16_t addr, uint16_t ink){
  uint32_t line;
  uint8_t lineX;
  while(height--){
    line = buffLine[addr];
    lineX = width;
    while(lineX--){
      if(line & 0x80000000){
        GuiDrawPixel(ink);
      }else{
        GuiDrawPixel(BLACK);
      }
      line <<= 0x01;
    }
    addr++;
  }
}

void GuiPrintDigits(uint16_t x, uint16_t y, uint16_t ink, uint8_t digits, uint8_t fraction, uint32_t number){
  uint8_t digitLine[digits];
  uint8_t i;
  uint16_t width, height, addr;
  for(i = 0x00; i < digits; i++){
    if(number > 0x00){
      digitLine[i] = number % 0x0A;
      number /= 0x0A;
    }else{
      if(i < (fraction + 0x01)){
        digitLine[i] = 0x00;
      }else{
        digitLine[i] = 0x0A;
      }
    }
  }
  for(i = 0x00; i < digits; i++){
    if(i < fraction){
      width = 0x17;
      height = 0x2C;
      addr = (digitLine[i] * height);
      GuiSetWindow(x, (y + 0x0C), width, height);
      GuiPrintSign(height, width, (uint32_t*)fonts_23x44, addr, ink);
    }else{
      x -= 0x03;
      width = 0x1A;
      height = 0x38;
      if(0x09 < digitLine[i]){
        digitLine[i] = 0x08;
        ink = DARKGREY;
      }
      addr = (digitLine[i] * height);
      GuiSetWindow(x, y, width, height);
      GuiPrintSign(height, width, (uint32_t*)fonts_26x56, addr, ink);
    }
    x -= 0x19;
  }
}

void GuiPrintFonts(uint16_t x, uint16_t y, uint16_t ink, uint8_t addr, uint8_t width){
  uint16_t c;
  uint8_t s;
  uint8_t i = 0x14;
  GuiSetWindow(x, y, width, i);
  while(i--){
    c = fonts[addr];
    s = width;
    while(s--){
      if(c & 0x8000){
        GuiDrawPixel(ink);
      }else{
        GuiDrawPixel(BLACK);
      }
      c <<= 0x01;
    }
    addr++;
  }
}

void GuiPrintFont(void){
  GuiPrintFonts(0x0106, 0x24, WHITE, 0xA0, 0x0D);  // кВт*ч  kW*h
  GuiPrintFonts(0x0113, 0x24, WHITE, 0x64, 0x10);  // кВт*ч  kW*h
  GuiPrintFonts(0x0123, 0x24, WHITE, 0x78, 0x07);  // кВт*ч  kW*h
  GuiPrintFonts(0x012A, 0x24, WHITE, 0x14, 0x0B);  // кВт*ч  kW*h
  GuiPrintFonts(0x0135, 0x24, WHITE, 0x8C, 0x0B);  // кВт*ч  kW*h
  GuiPrintFonts(0xFB, 0x60, WHITE, 0x64, 0x10);  // Вт W
  GuiPrintFonts(0x010B, 0x60, WHITE, 0x78, 0x07);  // Вт W
  GuiPrintFonts(0x55, 0x9C, WHITE, 0x3C, 0x10);  // Hz
  GuiPrintFonts(0x65, 0x9C, WHITE, 0xB4, 0x0C);  // Hz
  GuiPrintFonts(0x0130, 0x9C, WHITE, 0x50, 0x10); // V
  GuiPrintFonts(0x60, 0xD8, WHITE, 0x00, 0x10); // %
  GuiPrintFonts(0x0130, 0xD8, WHITE, 0x28, 0x10);  // A
}

void GuiUpdatePower(void){
  GuiPrintDigits(0xE7, 0x02, WHITE, 0x09, 0x03, power.activeEnergy);  // кВт*ч  kW*h
  GuiPrintDigits(0xDC, 0x3E, YELLOW, 0x06, 0x01, power.activePower);  // Вт W
  GuiPrintDigits(0x3B, 0x7A, GREEN, 0x03, 0x01, power.frequency);     // Гц Hz
  GuiPrintDigits(0x0115, 0x7A, ORANGE, 0x04, 0x01, power.voltage);    // В V
  GuiPrintDigits(0x44, 0xB6, CYAN, 0x03, 0x00, power.powerFctor);     // %
  GuiPrintDigits(0x0115, 0xB6, RED, 0x05, 0x03, power.current);       // А
}

void GuiPrintIcons(uint8_t icons, uint16_t ink){
  uint8_t i, width, height;
  uint16_t x, y, addr;
  switch(icons){
    case 0x00: x = 0x2D, y = 0x00; width = 0x32; height = 0x50; addr = 0x0154; i = 0x7D; // fridge
    break;
    case 0x01: x = 0x1E, y = 0x5C; width = 0x50; height = 0x38; addr = 0x00C8; i = 0x8C; // conditioner
    break;
    case 0x02: x = 0x1E, y = 0xA0; width = 0x50; height = 0x50; addr = 0x0000; i = 0xC8; // power
    break;
    default:   x = 0x00, y = 0x00; width = 0x00; height = 0x00; addr = 0x0000; i = 0x00;
    break;
  }
  GuiSetWindow(x, y, width, height);
  GuiPrintSign(i, 0x20, (uint32_t*)icon, addr, ink);
}

void GuiPrintIcon(void){
  for(uint8_t i = 0x00; i < 0x03; i++){ GuiPrintIcons(i, WHITE); }
}

void GuiPrintDigitsTimer(uint8_t timers){
  uint16_t x[0x04]={0x0102, 0xDE, 0xA6, 0x82};
  uint16_t digits[0x04], addr, data, ink;
  uint8_t y, b, height, width, j, min, sec;
  switch(timers){
    case 0x00: y = 0x0C; data = timer.fridge;
    break;
    case 0x01: y = 0x5C; data = timer.conditioner;
    break;
    case 0x02: y = 0xAC; data = timer.power;
    break;
    default:   y = 0x00; data = 0x00;
    break;
  }
  if(data > 0x1E){
    ink = WHITE;
  }else{
    if(data > 0x0A){
      ink = YELLOW;
    }else{
      ink = RED;
      if(data == 0x00){
        ink = GREEN;
      }
    }
  }
  min = data / 0x3C;
  sec = data % 0x3C;
  if(min > 0x09){ 
    digits[0x03] = min / 0x0A;
    b = 0x00;
  }else{ 
    digits[0x03] = 0x08;
    b = 0x01;
  }
  digits[0x02] = min % 0x0A;
  digits[0x01] = sec / 0x0A;
  digits[0x00] = sec % 0x0A;
  GuiSetWindow(0xCB, (y + 0x10), 0x08, 0x08); // :
  uint8_t z = 0x40;
  while(z--){
    GuiDrawPixel(ink);
  }
  GuiSetWindow(0xCB, (y + 0x2C), 0x08, 0x08); // :
  z = 0x40;
  while(z--){
    GuiDrawPixel(ink);
  }
  for(j = 0x00; j < 0x04; j++){
    height = 0x38;
    width = 0x1A;
    addr = (digits[j] * height);
    GuiSetWindow(x[j], y, width, height);
    if(b > 0x00 & j == 0x03) ink = DARKGREY;
    GuiPrintSign(height, width, (uint32_t*)fonts_26x56, addr, ink);
  }
}

void GuiUpdateTimer(void){
  for(uint8_t i = 0x00; i < 0x03; i++){ GuiPrintDigitsTimer(i); }
}

void GuiInit(void){
  
  #if defined DEBUG_GUI
    printf("< OK >    Initialization GUI\r\n");
  #endif
}
