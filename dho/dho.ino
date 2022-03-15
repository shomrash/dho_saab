#include <FastLED.h>
#include "GyverTimer.h"   // подключаем библиотеку

GTimer myTimer(MS);  // создать миллисекундный таймер (ms) (по умолч. в режиме интервала)

#define LED_dho_r_PIN     2
#define LED_dho_l_PIN     3
#define COLOR_ORDER GRB
#define CHIPSET     WS2811
#define NUM_LEDS    15


#define BRIGHTNESS  255

CRGB ledDhoRight[NUM_LEDS];

void setup() {
  FastLED.addLeds<CHIPSET, LED_dho_r_PIN, COLOR_ORDER>(ledDhoRight, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<CHIPSET, LED_dho_l_PIN, COLOR_ORDER>(ledDhoRight, NUM_LEDS).setCorrection( TypicalLEDStrip );
  
  FastLED.setBrightness( BRIGHTNESS );

  myTimer.setInterval(25);   
  myTimer.start();
}

int dr = 0;
int stateDHO = 0;
int brt[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,255 };

void loop() {
 if (myTimer.isReady()){
    if (stateDHO == 0){
      ledDhoRight[dr] =  CHSV(50, 0, 255);
      ledDhoRight[dr -1] = CRGB::Black;
      dr++;

      if (dr == 15) {
        dr=0;
        stateDHO = 1;
      }
    }
    if (stateDHO == 1){
         for(int i = 0; i < NUM_LEDS; i = i + 1) {
            brt[i] = brt[i]+15;
          ledDhoRight[dr] = CHSV(50, 0, brt[dr]);
         dr++;
          if (dr == 15) {
        dr=0;
        }
         }
         
          ledDhoRight[dr] = CHSV(50, 0, brt[dr]);
         dr++;
          if (dr == 15) {
        dr=0;
        stateDHO = 2;
      }
         
         }
    
    
    }
  FastLED.show();
}
