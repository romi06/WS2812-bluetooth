#include <FastLED.h>
#include <SoftwareSerial.h>

#define DATA_PIN          13
#define LED_TYPE          WS2812
#define COLOR_ORDER       GRB
#define NUM_LEDS          5
#define FRAMES_PER_SECOND 120

CRGB leds[NUM_LEDS];

#define BRIGHTNESS         255

int max_bright =      255;   //-SET MAX BRIGHTNESS 
int thissat =         255;   //-SATURATION (0-255)
int thishue =         0;     //-HUE (0-360)

int thisRED = 10;
int thisGRN = 10;
int thisBLU = 10;

#define SOFT_RX_PIN 2      // BTCHIP-TX -> NANO-SOFT-RX (2)
#define SOFT_TX_PIN 3      // BTCHIP-RX -> NANO-SOFT-TX (3)
#define SERIAL_BAUDRATE    57600
#define SERIAL_TIMEOUT     5

SoftwareSerial btSerial(SOFT_RX_PIN, SOFT_TX_PIN);

int btBOOL = 0;                     //-ACTIVATE BLUETOOTH OR NOT
byte inbyte;                        //-SERIAL INPUT BYTE
int thisarg;                        //-SERIAL INPUT ARG

void setup() {
  Serial.begin(SERIAL_BAUDRATE);        // SETUP HARDWARE SERIAL (USB)
  Serial.setTimeout(SERIAL_TIMEOUT);
 
  btSerial.begin(SERIAL_BAUDRATE);      // SETUP SOFTWARE SERIAL (USB)
  btSerial.setTimeout(SERIAL_TIMEOUT);

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  LEDS.setBrightness(max_bright);
 
}

  
//-SET ALL LEDS TO ONE COLOR
void one_color_all(int thisRED, int thisGRN, int thisBLU) {
      for(int i = 0 ; i < NUM_LEDS; i++ ) 
    {
      leds[i].setRGB( thisRED, thisGRN, thisBLU);
    }
}

//-SET ALL LEDS TO ONE COLOR (HSV)
void one_color_allHSV(int thishue, int thissat, int max_bright) { 
    for(int i = 0 ; i < NUM_LEDS; i++ ) {
      leds[i] = CHSV(thishue, thissat, 255);
    }
}

void loop()
{
  one_color_all(thisRED, thisGRN, thisBLU);

       //---PROCESS SOFTWARE SERIAL COMMANDS AND ARGS
  while (btSerial.available() > 0) {
    inbyte = btSerial.read();
    if (btSerial.overflow()){Serial.println("SoftwareSerial overflow!");}
    switch(inbyte) {
    case 59: break; //---BREAK IF INBYTE = ';'
    case 116:      //---"t" - SET SATURATION VAR
      thisarg = btSerial.parseInt();
      thissat = thisarg;
      break;
    case 104:      //---"h" - SET HUE VAR
      thisarg = btSerial.parseInt();
      thishue = thisarg;
      break;      
    case 98:      //---"b" - SET MAX BRIGHTNESS
      max_bright = btSerial.parseInt();
      LEDS.setBrightness(max_bright);
      break;      
    case 109:      //---"m" - SET MODE
      one_color_allHSV(thishue, thissat, 255);
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
     }
   }
 }
