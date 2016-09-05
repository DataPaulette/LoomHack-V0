#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 24
#define BRIGHTNESS 20

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 6
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

// buttons AV/ RECUL
#define BUTT_AV 12
#define BUTT_AR 13

// Defini le nombre de rangs du motif et le nombre de cadre utilisé
//erreur à plus de 33 rangs
#define NUM_RANGS  32
#define NUM_CADRES 24

// Pattern array > 1 signifie cadre à baissé > pas de virgule au dernier rang
int PAT[NUM_RANGS][NUM_CADRES] = {
  { 1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0 }, // cadres impairs
  { 1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,1,1,1,0,0,0,0 },
  { 0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0 }, // cadres pairs
  { 0,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0 },
  { 1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0 }, // cadres impairs
  { 0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0 },
  { 0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0 }, // cadres pairs
  { 0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0 },
  { 1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0 }, // cadres impairs
  { 0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0 },
  { 0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0 }, // cadres pairs
  { 0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0 },
  { 1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0 }, // cadres impairs
  { 0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0 },
  { 0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0 }, // cadres pairs
  { 0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0 },
  { 1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0 }, // cadres impairs
  { 1,1,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0 },
  { 0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0 }, // cadres pairs
  { 1,1,1,1,1,1,1,0,0,0,0,1,0,0,1,1,1,1,0,1,0,0,0,0 },
  { 1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0 }, // cadres impairs
  { 1,1,1,1,1,1,1,0,0,0,1,1,0,0,1,1,1,1,0,1,0,0,0,0 },
  { 0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0 }, // cadres pairs
  { 1,1,0,1,1,1,1,0,0,0,1,1,0,0,0,1,1,1,0,1,0,0,0,0 },
  { 1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0 }, // cadres impairs
  { 1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,1,1,1,1,0,0,0,0 },
  { 0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0 }, // cadres pairs
  { 1,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,1,1,0,0,0,0 },
  { 1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0 }, // cadres impairs
  { 1,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,1,1,1,0,0,0,0 },
  { 0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0 }, // cadres pairs
  { 1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1 } // le dernier 1 indique la fin du motif 
};

int moves = 0;

void setup() {
  // Uncomment/edit one of the following lines for your leds arrangement.
  // FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);

  // OK pour ruban etanche 48 leds barzi
  // FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  // FastLED.addLeds<APA104, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<GW6205, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<GW6205_400, DATA_PIN, RGB>(leds, NUM_LEDS);

  // FastLED.addLeds<WS2801, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<SM16716, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<LPD8806, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<P9813, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<APA102, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<DOTSTAR, RGB>(leds, NUM_LEDS);

  // FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);

  pinMode( BUTT_AV, INPUT);
  pinMode( BUTT_AR, INPUT);

  FastLED.setBrightness(  BRIGHTNESS );

  all_ON();
  FastLED.show();
  delay(500);
  all_OFF();
  FastLED.show();
  delay(500);

  Serial.begin(9600);
}

unsigned long last_BUTT_Press_Ms = 0;
boolean bAV, bAR;
boolean last_bAV, last_bAR;

////////////////////// LOOP ////////////////////////////
void loop() {

  bAV = (digitalRead( BUTT_AV ) == HIGH );
  bAR = (digitalRead( BUTT_AR ) == HIGH );

  if ( bAV ) Serial.println("AV");
  if ( bAR ) Serial.println("AR");


  // si on appuie sur un des 2 boutons ...
  if ( (millis() - last_BUTT_Press_Ms) > 400  ) {
    last_BUTT_Press_Ms = millis();
    Serial.println("moves = " + moves);
    fadeall(400);

    if ( bAV  &&  (bAV != last_bAV) )  {
      moves++;
      if ( moves >= NUM_RANGS ) moves = 0;
    }
    if (bAR   &&  (bAR != last_bAR) )  {
      moves--;
      if ( moves < 0 ) moves = 0;
    }

    last_bAV = bAV;
    last_bAR = bAR;
  }

  // affiche les LEDs en fontion d'ou on en est dans le motif
  for (int i = 0; i < NUM_CADRES; i++) {
    if ( PAT[moves][i] == 1 )
      leds[i] = CRGB::Blue;
    else
      leds[i] = CRGB::Black;
  }

  FastLED.show();

  delay(50);

}
////////////////////// **** ////////////////////////////



void all_ON() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Red;
  }
}

void all_OFF() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
}


void fadeall(int p) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].nscale8(p);
  }
}

