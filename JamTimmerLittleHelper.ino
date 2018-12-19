/*HI MUGGLE WORLD. Please spread this Jam Timmer's Little Helper
arround the globe. Share Alike. Thanks. @merececarri */
 
// ADAFRUIT LIBRARY IMPORT

#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <gfxfont.h>
#include <Adafruit_ST7735.h> 
#include <SPI.h>
#include <Fonts/FreeSerif12pt7b.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Adafruit_GFX.h>  

//  PIN DEFINITION  

#define TFT_CS 10   //constante a pin 10 de arduino
#define TFT_RST 9  // you can also connect this to the Arduino reset
#define TFT_DC  8 //constante a pin 8 de arduino
#define TFT_SCLK 13   
#define TFT_MOSI 11 

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

//  COLOR DEFINITION

#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0
#define WHITE    0xFFFF

void setup() {
  
  tft.setFont (&FreeMonoBold9pt7b);
  tft.initR(INITR_BLACKTAB);

  pinMode (2, INPUT); //BUT_START
  pinMode (3, INPUT); //BUT_RESET
  pinMode (4, INPUT); //BUT_PAUSE

  uint16_t w = tft.width();
  uint16_t h = tft.height();

  tft.fillScreen(ST7735_BLACK);
  
  drawtext("JAM", ST7735_BLUE, 47, 25, 15, 15);
  drawtext("TIMMER'S", ST7735_YELLOW, 22, 50, 15, 15);
  drawtext("LITTLE", ST7735_CYAN, 28, 75, 15, 15);
  drawtext("HELPER", ST7735_BLUE, 28, 100, 15, 15);
  delay(5000);
 
  
  tft.fillScreen(ST7735_BLACK);
  
  //tft.drawRect(0, 0, 128, 128, BLACK);
  //tft.fillRect(0, 0, 128, 128,BLACK);
  
  drawtext("00", ST7735_WHITE, 14, 30, 10, 10);
  drawtext("0:00", ST7735_WHITE, 65, 30, 10, 10);

  drawtext("00:00", ST7735_CYAN, 15, 110, 15, 15);
  drawtext("P1", ST7735_RED, 95, 110, 15, 15);

  drawtext("JT's LH", ST7735_BLUE, 25, 70, 15, 15);

  

  Serial.begin(9600);
}

unsigned long time_jam = 0;
unsigned long time_general = 0;


enum {OFF, STOPPED, COUNTING, PAUSED};
enum {BUT_START, BUT_PAUSE, BUT_RESET, NO_BUTTON};
int jamNumber = 0;
int state = OFF;

void loop() {

  

  int button = checkButtons();

  switch (state) {
    case OFF:
      if (button == BUT_START) {
        state = COUNTING;
        jamNumber = 1; //agregue esta tambien
      }
      break;
    
    case STOPPED:
      if (oneSecondLater()) time_general++;
      time_jam = 0; // agregue esta linea
      
      if (button == BUT_START) {
        state = COUNTING;
        jamNumber = jamNumber+1;
      }
      else if (button == BUT_RESET) {
        time_jam = 0;
        time_general = 0;
        jamNumber = 0; //agregue esta. no estoy segura si es 0 o 1
      }
      break;
      
    case COUNTING:
      if (oneSecondLater()) {
        time_general++;
        time_jam++;
        if (time_jam == 120000) {
          time_jam = 0;
          state = STOPPED;
        }
      }
      
      if (button == BUT_START) {
        state = STOPPED;
      }
      else if (button == BUT_PAUSE) {
        state = PAUSED;
      }      
      break;
    
    case PAUSED:
      if (button == BUT_START) {
        state = COUNTING;
      }
      break;
  }


//  HRS, MINS AND SECS CALCULATION + PRINT
    
    unsigned long over;
    unsigned long tgHours, tgMinutes, tgSeconds, tjHours, tjMinutes,tjSeconds; 
    
    tgHours = ((time_general)/3600000);
    
    tgMinutes = (((tgHours) % 3600000) / 60000);
    
    tgSeconds =  (time_general%60);
    
    
    
    tjHours =  int((time_jam)/3600000);
    over = (tjHours) % 3600000;
    tjMinutes =  int(over/60000);
    over = over % 60000;
    tjSeconds =  int(over/1000);
    over = over % 60000;
    

//  PRINT JAM PERIODS 

  if (tgMinutes > 31) {
        drawtext("P2", ST7735_RED, 95, 110, 15, 15);
      }
      else {
        drawtext("P1", ST7735_RED, 95, 110, 15, 15);
      }


/*  PROVISORIO TIEMPOS
  drawint (time_general%60, ST7735_BLUE, 4, 50, 120, 20);
  drawint (time_general%60, ST7735_BLUE, 10, 80, 120, 20);
  */
  
 
  
//  PRINT GENERAL TIME (ACUMULADO)

      tgMinutes = int(time_general / 60);
      tgSeconds = time_general - (tgMinutes * 60);

      if (tgMinutes <10){
        drawint (tgMinutes, ST7735_CYAN, 26, 110, 15, 15);
      }

      else {
        drawint (tgMinutes, ST7735_CYAN, 16, 110, 15, 15);
      }

      if (tgSeconds < 10) {
        drawint (tgSeconds, ST7735_CYAN, 58, 110, 15, 15);
        drawtext ("0", ST7735_WHITE, 47, 110, 12, 12);
      }
      else {
        drawint (tgSeconds, ST7735_CYAN, 47, 110, 30, 25);      
        }
  
  
 // PRINT JAM TIME

      tjMinutes = int(time_jam / 60);
      tjSeconds = time_jam - (tjMinutes * 60);

      drawint (tjMinutes, ST7735_WHITE, 65, 30, 15, 15);

      if (tjSeconds < 10) {
        drawint (tjSeconds, ST7735_WHITE, 100, 30, 12, 12);
        drawtext ("0", ST7735_WHITE, 89, 30, 12, 12);
      }
      else {
        drawint (tjSeconds, ST7735_WHITE, 89, 30, 22, 17);
      }
      
 // PRINT JAM NUMBER 

  tft.drawCircle( 24, 24, 14, CYAN);

  drawtext("00", ST7735_WHITE, 14, 30, 10, 10);

  if (jamNumber < 10) {
        drawint (jamNumber, ST7735_WHITE, 23, 30, 12, 12);
        drawtext ("0", ST7735_WHITE, 14, 30, 11, 11);
      }
      else {
        drawint (jamNumber, ST7735_WHITE, 14, 30, 12, 12);
      }    
}
