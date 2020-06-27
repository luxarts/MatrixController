#include <FastLED.h>

#define PIN 4
#define NUM_LEDS 64
#define COLOR_ORDER GRB
#define CHIPSET WS2812

CRGB leds[NUM_LEDS];

uint8_t inputMatrix[192];
uint8_t inputComplete = false;

void setup(){
  memset(inputMatrix, 0, sizeof(inputMatrix));
  Serial.begin(115200);
  FastLED.addLeds<CHIPSET, PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.setBrightness(255);
  FastLED.show();
}

void loop(){
  if(inputComplete){
    inputComplete = false;

    uint8_t colorIndex = 0;

    for(uint8_t i=0; i<NUM_LEDS; i++){
      leds[i] = CRGB(inputMatrix[colorIndex], inputMatrix[colorIndex+1], inputMatrix[colorIndex+2]);
      colorIndex += 3;
    }

    FastLED.show();
  }
}

void serialEvent(){
  while(Serial.available()){
    Serial.readBytes(inputMatrix, 192);
    inputComplete = true;
  }
}
