#include <FastLED.h>
#include <SoftwareSerial.h>

#define DATA_PIN      13
#define LED_TYPE      WS2812
#define COLOR_ORDER   GRB
#define NUM_LEDS      30
#define FRAMES_PER_SECOND 120

CRGB leds[NUM_LEDS];

#define BRIGHTNESS         255

#define SOFT_RX_PIN 2         // BTCHIP-TX -> NANO-SOFT-RX (2)
#define SOFT_TX_PIN 3         // BTCHIP-RX -> NANO-SOFT-TX (3)
#define SERIAL_BAUDRATE    57600
#define SERIAL_TIMEOUT     5

SoftwareSerial btSerial(SOFT_RX_PIN, SOFT_TX_PIN);

int btBOOL = 0;                     //-ACTIVATE BLUETOOTH OR NOT
byte inbyte;                        //-SERIAL INPUT BYTE
int thisarg;                        //-SERIAL INPUT ARG

#include "efekty.h"

void setup() {
  Serial.begin(SERIAL_BAUDRATE);        // SETUP HARDWARE SERIAL (USB)
  Serial.setTimeout(SERIAL_TIMEOUT);
 
  btSerial.begin(SERIAL_BAUDRATE);      // SETUP SOFTWARE SERIAL (USB)
  btSerial.setTimeout(SERIAL_TIMEOUT);

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  LEDS.setBrightness(max_bright);
 
  one_color_all(0,0,0);
  FastLED.show();  
}

void change_mode(int newmode){
  thissat = 255;
  switch (newmode) {
    case  0: one_color_all(0,0,0);  FastLED.show(); break;        // ALL OFF
    case  1: one_color_all(255,255,255);  FastLED.show(); break;  // ALL ON
    case  2: thisdelay = 20; break;                               // CONFETTI
    case  3: thisdelay = 20; thissat = 0; break;                  // GLITTER FADE
    case  4: thisdelay = 20; thissat = 0; break;                  // GLITTER
    case  5: thisdelay = 100; thishue = 100; break;               // COLOR LEFT RIGHT
    case  6: thisdelay = 50; thishue = 95; break;                 // MATRIX COLOR
    case  7: thisdelay = 50; thishue = 95; break;                 // MATRIX RAIN
    case  8: thishue = 160; thissat = 50; break;                  // STRIP FLICKER
    case  9: thisdelay = 10; thishue = 220; break;                // BOUNCE FADE
    case 10: thishue = 150; max_bright=255; break;                // PURPLE RAIN
    case 11: thisdelay = 20; break;                               // NOISE 16
    case 12: thisdelay = 20; break;                               // FIRE 2012
    case 13: thisdelay = 90; thisstep = 5; break;                 // MOVING PIXELS
    case 14: thisdelay = 40; thisBLU = 255; break;                // CYLON BOUNCE
    case 15: thisdelay = 30; break;                               // RUNNING LIGHYS
    case 16: thisdelay = 30; thisstep = 30; break;                // ONE SINE
    case 17: thisdelay = 100; break;                              // BLENDME
    case 18: thisdelay = 50; thisstep = 0; break;                 // RIPPLE
    case 19: thisdelay = 40; thisstep = 30; break;                // MOVER
    case 20: thisdelay = 10; break;                               // LIGHTNINGS
    case 21: thisdelay = 5; thisstep = 30; break;                 // EASE ME
    case 22: thisdelay = 50; thissat = 255; break;                // RAINBOW 'UP' THE LOOP
    case 23: thisdelay = 40; break;                               // THRRE SIN
    case 24: thisdelay = 80; thishue = 0; break;                  // KITT
    case 25: thisdelay = 30; thisstep = 3; break;                 // NEW KITT
    case 26: thisdelay = 20; thishue = 0; break;                  // FADE ALL LEDS THROUGH HSV RAINBOW
    case 27: thisdelay = 20; thishue = 0; break;                  // RANDOM INDEX/COLOR
    case 28: thisdelay = 50; break;                               // TWINKLE
    case 29: thisdelay = 5; break;                                // NEW RAINBOW LOOP
    case 30: thisdelay = 5; thissat = 0; break;                   // NEW RAINBOW LOOP + GLITTER
    case 31: thisdelay = 20; thisstep = 10; break;                // RAINBOW LOOP
    case 32: thisdelay = 40; thishue = 0; break;                  // POLICE LIGHTS SINGLE
    case 33: thisdelay = 40; thishue = 0; break;                  // POLICE LIGHTS SOLID
    //case 34:                                                    // RANDOM RED
    case 35: thisdelay = 100; break;                              // CELL AUTO - RULE 30 (RED)
    case 36: thisdelay = 40; break;                               // JUGGLE
    case 37: thisdelay = 5; thishue = 0; break;                   // PULSE COLOR SATURATION
    case 38: thisdelay = 5; thishue = 0; break;                   // PULSE COLOR BRIGHTNESS
    //case 39:                                                    // FLAME ISH 
    case 40: thisdelay = 35; break;                               // RANDOM COLOR POP
    case 41: thisdelay = 25; thishue = 0; break;                  // RGB PROPELLER
    case 42: thisdelay = 20; thishue = 0; break;                  // CYLON v1
    case 43: thisdelay = 40; thishue = 0; break;                  // CYLON v2
    case 44: thisdelay = 60; thishue = 180; break;                // VERTICAL SOMETHING
    case 45: thisdelay = 40; break;                               // MARCH RANDOM COLORS
    case 46: thisdelay = 80; break;                               // MARCH RWB COLORS
    case 47: thisdelay = 60; thishue = 95; break;                 // RADIATION SYMBOL
    //case 48:                                                    // PLACEHOLDER FOR COLOR LOOP VAR DELAY VARS
    case 49: thisdelay = 35; thishue = 180; break;                // SIN WAVE BRIGHTNESS
    case 50: thisdelay = 100; thishue = 0; break;                 // POP LEFT/RIGHT 
  
  }
  bouncedirection = 0;
  one_color_all(0,0,0);
  ledMode = newmode;
}

void loop()
{
  switch (ledMode) 
   {
      case  0: one_color_all(0,0,0); break;
      case  1: one_color_all(255,255,255); break;
      case  2: confetti(); break;
      case  3: Glitter_fade(); break;
      case  4: Glitter(); break;
      case  5: colorleftright(); break;
      case  6: matrix(); break;
      case  7: matrix1(); break;
      case  8: flicker(); break;
      case  9: bounceFadeRain(); break;
      case 10: unicornPurpleRain(); break;
      case 11: noise16(); break;
      case 12: Fire2012(); break;
      case 13: moving_pixels(); break;
      case 14: CylonBounce(); break;
      case 15: RunningLights(); break;
      case 16: one_sine(); break;
      case 17: blendme(); break;
      case 18: ripple(); break;
      case 19: mover(); break;
      case 20: lightnings(); break;
      case 21: easeMe(); break;
      case 22: rainbow_vertical(); break;
      case 23: three_sin(); break;
      case 24: kitt(); break;
      case 25: NewKITT(0xff, 0, 0, 50); break;
      case 26: rainbow_fade(); break;
      case 27: random_burst(); break;
      case 28: twinkle(); break;
      case 29: new_rainbow_loop(); break;
      case 30: new_rainbow_loop_addGlitter(); break;
      case 31: rainbow_loop(); break;
      case 32: ems_lightsONE(); break;
      case 33: ems_lightsALL(); break;
      case 34: random_red(); break;
      case 35: rule30(); break;
      case 36: juggle(); break;
      case 37: pulse_one_color_all_rev(); break;
      case 38: pulse_one_color_all(); break;
      case 39: flame(); break;
      case 40: random_color_pop(); break;
      case 41: rgb_propeller(); break;
      case 42: color_bounce(); break;
      case 43: color_bounceFADE(); break;
      case 44: fade_vertical(); break;
      case 45: random_march(); break;
      case 46: rwb_march(); break;
      case 47: radiation(); break;
      case 48: color_loop_vardelay(); break;
      case 49: sin_bright_wave(); break;
      case 50: pop_horizontal(); break;

      case 150: one_color_all(thisRED, thisGRN, thisBLU);  FastLED.show(); break;
      case 151: wake_light_fade_on(); break;
      case 300: demo_modeA(); break;

   }

     //---PROCESS SOFTWARE SERIAL COMMANDS AND ARGS
  while (btSerial.available() > 0) {
    inbyte = btSerial.read();
    if (btSerial.overflow()){Serial.println("SoftwareSerial overflow!");}
    switch(inbyte) {
    case 59: break; //---BREAK IF INBYTE = ';'
    case 108:      //---"l" - SET SINGLE LED VALUE
      thisindex = btSerial.parseInt();
      thisRED = btSerial.parseInt();
      thisGRN = btSerial.parseInt();
      thisBLU = btSerial.parseInt();      
      if (ledMode != 999) {
        ledMode = 999;
        one_color_all(0,0,0);}        
      leds[thisindex].setRGB( thisRED, thisGRN, thisBLU);
      break;
    case 100:      //---"d" - SET DELAY VAR
      thisarg = btSerial.parseInt();
      thisdelay = thisarg;
      break;
    case 115:      //---"s" - SET STEP VAR
      thisarg = btSerial.parseInt();
      thisstep = thisarg;
      break;
    case 104:      //---"h" - SET HUE VAR
      thisarg = btSerial.parseInt();
      thishue = thisarg;
      break;
    case 116:      //---"t" - SET SATURATION VAR
      thisarg = btSerial.parseInt();
      thissat = thisarg;
      break;
    case 98:      //---"b" - SET MAX BRIGHTNESS
      max_bright = btSerial.parseInt();
      LEDS.setBrightness(max_bright);
      break;      
    case 109:      //---"m" - SET MODE
      thisarg = btSerial.parseInt();    
      Serial.println(thisarg);       
      change_mode(thisarg);
      break;
    case 99:      //---"c" - CLEAR STRIP
      one_color_all(0,0,0);
      break;
    case 97:      //---"a" - SET ALL TO ONE COLOR BY HSV 0-255
      thisarg = btSerial.parseInt();
      one_color_allHSV(thisarg);
      break;
    case 122:      //---"z" - COMMAND TO 'SHOW' LEDS
      LEDS.show();
      break;        
    case 82:      //---"R" - RED
      thisarg = btSerial.parseInt();
      thisRED = thisarg;
      Serial.print(thisarg);
      break;   
    case 71:      //---"G" - GREEN
      thisarg = btSerial.parseInt();
      Serial.print(thisarg);
      thisGRN = thisarg;
      break;   
    case 66:      //---"B" - BLUE
      thisarg = btSerial.parseInt();
      Serial.print(thisarg);
      thisBLU = thisarg;
      break;
    case 70:      //---"F" - BLUE
      thisarg = btSerial.parseInt();
      Serial.print(thisarg);
      thisfade = thisarg;
      break;


    
//    case 106:      //---"j" - pobiera liste efektow
//      btSerial.println("");
//      btSerial.print("ALL OFF,");
//      btSerial.print("ALL ON,"); 
//      btSerial.print("MATRIX COLOR,");
//      btSerial.print("MATRIX RAIN,");
//      btSerial.print("CONFETTI,");
//      btSerial.print("GLITTER,");
//      btSerial.print("GLITTER FADE,");
//      btSerial.print("NEW RAINBOW LOOP,");
//      btSerial.print("NEW RAINBOW LOOP + GLITTER,");
//      btSerial.print("Twinkle,");
//      btSerial.print("RAINBOW LOOP,");
//      btSerial.print("POLICE LIGHTS SINGLE,");
//      btSerial.print("POLICE LIGHTS SOLID,");
//      btSerial.print("COMET COLOR,");
//      btSerial.print("THRRE SIN,");
//      btSerial.print("STRIP FLICKER,");
//      btSerial.print("JUGGLE,");
//      btSerial.print("PULSE COLOR SATURATION,");
//      btSerial.print("PULSE COLOR BRIGHTNESS,");
//      btSerial.print("FLAME,");
//      btSerial.print("RANDOM COLOR POP,");
//      btSerial.print("RGB PROPELLER,");
//      btSerial.print("KNIGHT INDUSTIES 2000,");
//      btSerial.print("FADE ALL LEDS THROUGH HSV RAINBOW,");
//      btSerial.print("RANDOM INDEX/COLOR,");
//      btSerial.print("BOUNCE COLOR (SINGLE LED),");
//      btSerial.print("BOUNCE COLOR (SIMPLE MULTI-LED FADE),");
//      btSerial.print("FADE 'UP' THE LOOP,");
//      btSerial.print("QUICK 'N DIRTY RANDOMIZE,");
//      btSerial.print("RULE 30 (RED FOR NOW),");
//      btSerial.print("RANDOM MARCH CCW,");
//      btSerial.print("R W B MARCH CCW,");
//      btSerial.print("SORT OF RADIATION SYMBOLISH,");
//      btSerial.print("COLOR LOOP (SINGLE LED),");
//      btSerial.print("BRIGHTNESS SINE WAVE,");
//      btSerial.print("POP LEFT/RIGHT,");
//      btSerial.print("QUADRATIC BRIGHTNESS CURVE,");
//      btSerial.print("VERITCAL RAINBOW,");
//      btSerial.print("DOT BEAT,");
//      btSerial.print("EASE ME,");
//      btSerial.print("LIGHTNINGS,");
//      btSerial.print("MOVER,");
//      btSerial.print("RIPPLE,");
//      btSerial.print("BLENDME,");
//      break;        
    }
  }
//  //---PROCESS HARDWARE SERIAL COMMANDS AND ARGS
//  while (Serial.available() > 0) {inbyte = Serial.read();
//    switch(inbyte) {
//    case 59: break; //---BREAK IF INBYTE = ';'
//    case 108:      //---"l" - SET SINGLE LED VALUE RGB
//      thisindex = Serial.parseInt();
//      thisRED = Serial.parseInt();
//      thisGRN = Serial.parseInt();
//      thisBLU = Serial.parseInt();      
//      if (ledMode != 999) {
//        ledMode = 999;
//        one_color_all(0,0,0);}        
//      leds[thisindex].setRGB( thisRED, thisGRN, thisBLU);
//      break;
//    case 118:      //---"v" - SET SINGLE LED VALUE HSV
//      thisindex = Serial.parseInt();
//      thishue = Serial.parseInt();
//      thissat = Serial.parseInt();
//      //thisVAL = Serial.parseInt();      
//      if (ledMode != 999) {
//        ledMode = 999;
//        one_color_all(0,0,0);}
//      leds[thisindex] = CHSV(thishue, thissat, 255);
//      break;      
//    case 100:      //---"d" - SET DELAY VAR
//      thisarg = Serial.parseInt();
//      thisdelay = thisarg;
//      break;
//    case 115:      //---"s" - SET STEP VAR
//      thisarg = Serial.parseInt();
//      thisstep = thisarg;
//      break;
//    case 104:      //---"h" - SET HUE VAR
//      thisarg = Serial.parseInt();
//      thishue = thisarg;
//      break;
//    case 116:      //---"t" - SET SATURATION VAR
//      thisarg = Serial.parseInt();
//      thissat = thisarg;
//      break;
//    case 98:      //---"b" - SET MAX BRIGHTNESS
//      max_bright = Serial.parseInt();
//      LEDS.setBrightness(max_bright);
//      break;      
//    case 109:      //---"m" - SET MODE
//      thisarg = Serial.parseInt();      
//      change_mode(thisarg);
//      break;
//    case 99:      //---"c" - CLEAR STRIP
//      one_color_all(0,0,0);
//      break;
//    case 97:      //---"a" - SET ALL TO ONE COLOR BY HSV 0-255
//      thisarg = Serial.parseInt();
//      one_color_allHSV(thisarg);
//      break;
//    case 122:      //---"z" - COMMAND TO 'SHOW' LEDS
//      FastLED.show();  
//      break;
//    case 82:      //---"R" - RED
//      thisarg = Serial.parseInt();
//      thisRED = thisarg;
//      break;   
//    case 71:      //---"G" - GREEN
//      thisarg = Serial.parseInt();
//      thisGRN = thisarg;
//      break;   
//    case 66:      //---"B" - BLUE
//      thisarg = Serial.parseInt();
//      thisBLU = thisarg;
//      break;
//    }
//  }
}

 
