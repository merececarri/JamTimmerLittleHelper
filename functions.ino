/*HI MUGGLE WORLD. Please spread this Jam Timmer's Little Helper
arround the globe. Share Alike. Thanks. @merececarri */
 
// CHECK BUTTON LOOP

int checkButtons() {
    
  int buttonIs = NO_BUTTON;

  static int lastButtonState2 = 0;
  static int lastButtonState3 = 0;
  static int lastButtonState4 = 0;
  
  int buttonState2 = digitalRead(2); //BUT_START 
  int buttonState3 = digitalRead(3); //BUT_RESET
  int buttonState4 = digitalRead(4); //BUT_PAUSE
  
  if (buttonState2 && !lastButtonState2) {
    buttonIs = BUT_START;
  }


  else if (buttonState3 && !lastButtonState3) {
    buttonIs = BUT_RESET;
  }

   else if (buttonState4 && !lastButtonState4) {
    buttonIs = BUT_PAUSE; 
  }
  
  lastButtonState2 = buttonState2;
  lastButtonState3 = buttonState3;
  lastButtonState4 = buttonState4;

  
  return buttonIs;    // return button state BUT_START, BUT_PAUSE, BUT_RESET o NO_BUTTON
 
}


unsigned long lastTime = 0;

bool oneSecondLater() {
  bool r = false;
  if (millis() - lastTime > 1000) {
    r = true;
    lastTime = millis();
  }
  return r;
}

  // PRINTING LAYOUT

void drawtext(char *text, uint16_t color, uint16_t x, uint16_t y, uint16_t wtxt, uint16_t htxt) {
  tft.drawRect(x, y - htxt + 1, wtxt, htxt, ST7735_BLACK);
  tft.fillRect(x, y - htxt + 1, wtxt, htxt, ST7735_BLACK);
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void drawint(unsigned long value, uint16_t color, uint16_t x, uint16_t y, uint16_t wtxt, uint16_t htxt) {
  tft.drawRect(x, y - htxt + 1, wtxt, htxt, ST7735_BLACK);
  tft.fillRect(x, y - htxt + 1, wtxt, htxt, ST7735_BLACK);
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(value);
}


void drawCircle(uint16_t x, uint16_t y, uint16_t radius, uint16_t color){
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.drawCircle (x, y, radius, color);
}
  
void fillCircle(uint16_t x, uint16_t y, uint16_t radius, uint16_t color){
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.fillCircle (x, y, radius, color);
}


