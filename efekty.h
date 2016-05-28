#ifndef EFEKTY_H
#define EFEKTY_H

#define COOLING 55      // Default 50, suggested range 20-100 
#define SPARKING 120    // Default 120, suggested range 50-200.
bool gReverseDirection = false;

int max_bright =      255;   //-SET MAX BRIGHTNESS 
int thissat =         255;   //-SATURATION (0-255)
int thisdelay =       20;    //-FX LOOPS DELAY VAR
int thisstep =        10;    //-FX LOOPS DELAY VAR
int thishue =         0;     //-HUE (0-360)
int bouncedirection = 0;     //-SWITCH FOR COLOR BOUNCE (0-1)
int ledMode =         51;    //-MODE TESTING
int thisindex =       0;     //-SET SINGLE LED VAR
int thisRED =         0;
int thisGRN =         0;
int thisBLU =         0;
int pixel =           0;
int dir =             0;  
int thisfade =        0;
int ihue =            0;
int isat =            0;     //-SATURATION (0-255)
int ibright =         0;     //-BRIGHTNESS (0-255)

// One line matrix
bool thisdir =  0;     // Standard direction
bool huerot =   0;
uint8_t bgclr = 0;
uint8_t bgbri = 0;
int ledsX[NUM_LEDS][3];    //-ARRAY FOR COPYING WHATS IN THE LED STRIP CURRENTLY (FOR CELL-AUTOMATA, MARCH, ETC)

//bounceFadeRain
int hit;

//Noise
uint32_t  x,hue_time;                       // x & hue_time values
uint8_t octaves =       2;       //2        // how many octaves to use for the brightness
uint8_t hue_octaves =   3;       //3        // how many octaves to use for the hue
int xscale =            57771;   //57771    // the 'distance' between points on the x axis
uint32_t hxy =          43213;   //43213    // not sure about this
int hue_scale =         20;      //1        // the 'distance' between points for the hue noise
int hue_speed =         1;       //31       // how fast we move through hue noise
uint8_t x_speed =       0;       //331      // adjust this value to move along the x axis between frames
int8_t hxyinc =         3;       //3

//moving pixels
int16_t positionRed =   0;    // Set initial start position of Red pixel
int16_t positionWhite = 2;    // Set initial start position of White pixel
int16_t positionBlue =  6;    // Set initial start position of Blue pixel

//One sine
#define qsubd(x, b) ((x>b)?wavebright:0)   // Digital unsigned subtraction macro. if result <0, then => 0. Otherwise, take on fixed value.
#define qsuba(x, b) ((x>b)?x-b:0)          // Analog Unsigned subtraction macro. if result <0, then => 0
int thisphase =         0;                 // Phase change value gets calculated.
int8_t thisspeed =      8;                 // You can change the speed of the wave, and use negative values.
uint8_t thisrot =       1;                 // You can change how quickly the hue rotates for this wave. Currently 0.
uint8_t thiscutoff =  192;                 // You can change the cutoff value to display this wave. Lower value = longer wave.
uint8_t wavebright =  128;                 // You can change the brightness of the waves/bars rolling across the screen.

//Ripple
#define maxsteps 16                        // Case statement wouldn't allow a variable.
uint8_t myfade =    255;                   // Starting brightness.
uint8_t colour;                            // Ripple colour is randomized.
uint8_t bgcol =       0;      
int step =           -1;                   // -1 is the initializing step.
int center =          0;                   // Center of the current ripple.

// LIGHTNINGS
uint8_t ledstart;           // Starting location of a flash
uint8_t ledlen;             // Length of a flash
uint8_t flashes =     8;    // the upper limit of flashes per strike
unsigned int dimmer = 1;
uint8_t frequency =  50;    // controls the interval between strikes
uint8_t bpm =        30;

//---FIND INDEX OF HORIZONAL OPPOSITE LED
int BOTTOM_INDEX = 0;
int TOP_INDEX = int(NUM_LEDS/2);
int EVENODD = NUM_LEDS%2;

// three_sin variables
int wave1 =     0;
int wave2 =     0;
int wave3 =     0;
uint8_t inc1 =  2;
uint8_t inc2 =  1;
uint8_t inc3 = -3;
uint8_t lvl1 = 80;
uint8_t lvl2 = 80;
uint8_t lvl3 = 80;
uint8_t mul1 = 20;
uint8_t mul2 = 25;
uint8_t mul3 = 22;

// Twinkle
int ranamount = 50;       // The higher the number, lowers the chance for a pixel to light up.
int n =          0;       // number that helps to switch between Blue and White

// SORT OF RADIATION SYMBOLISH
float tcount = 0.0;          //-INC VAR FOR SIN LOOPS

//-SET ALL LEDS TO ONE COLOR
void one_color_all(int cred, int cgrn, int cblu) {       
    for(int i = 0 ; i < NUM_LEDS; i++ ) 
    {
      leds[i].setRGB( cred, cgrn, cblu);
    }
}

//-SET ALL LEDS TO ONE COLOR (HSV)
void one_color_allHSV(int ahue) { 
    for(int i = 0 ; i < NUM_LEDS; i++ ) {
      leds[i] = CHSV(ahue, thissat, 255);
    }
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] = CHSV(thishue, thissat, 255);
  }
}

void copy_led_array(){
  for(int i = 0; i < NUM_LEDS; i++ ) {
    ledsX[i][0] = leds[i].r;
    ledsX[i][1] = leds[i].g;
    ledsX[i][2] = leds[i].b;
  }  
}

//---FIND INDEX OF HORIZONAL OPPOSITE LED
int horizontal_index(int i) {
  //-ONLY WORKS WITH INDEX < TOPINDEX
  if (i == BOTTOM_INDEX) {return BOTTOM_INDEX;}
  if (i == TOP_INDEX && EVENODD == 1) {return TOP_INDEX + 1;}
  if (i == TOP_INDEX && EVENODD == 0) {return TOP_INDEX;}
  return NUM_LEDS - i;  
}

//---FIND INDEX OF ANTIPODAL OPPOSITE LED
  int antipodal_index(int i) {
  int iN = i + TOP_INDEX;
  if (i >= TOP_INDEX) {iN = ( i + TOP_INDEX ) % NUM_LEDS; }
  return iN;
}

//---FIND ADJACENT INDEX CLOCKWISE
int adjacent_cw(int i) {
  int r;
  if (i < NUM_LEDS - 1) {r = i + 1;}
  else {r = 0;}
  return r;
}

//---FIND ADJACENT INDEX COUNTER-CLOCKWISE
int adjacent_ccw(int i) {
  int r;
  if (i > 0) {r = i - 1;}
  else {r = NUM_LEDS - 1;}
  return r;
}
//------------------------LED EFFECT FUNCTIONS------------------------
    
// random colored speckles that blink in and fade smoothly
void confetti() 
{
  fadeToBlackBy(leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV(thishue + random8(64), 200, 255);
  thishue++;
  LEDS.show();  
  delay(thisdelay);
}

// Glitter
void Glitter() 
{
  LEDS.clear();  
  addGlitter(80 + thisstep); 
  LEDS.show();  
  delay(thisdelay);
}

// Glitter fade
void Glitter_fade() 
{
  fadeToBlackBy( leds, NUM_LEDS, thisstep);
  addGlitter(30 + thisstep); 
  LEDS.show();  
  delay(thisdelay);
}

//color left right
void colorleftright(){  //***** Color Wheel from the left.
   leds[pixel] = 0x000000;          
    if (dir == 1){
      if(--pixel == 0) {
        dir = 0;
        one_color_allHSV(thishue + random8(64));
      }
    FastLED.show();                   
    delay(thisdelay+100); 
    }
    else{
      if(++pixel >= NUM_LEDS) {         // Increment head index.  Off end of strip?
        dir = 1;
        one_color_allHSV(thishue + random8(64));
      }
    FastLED.show();                   
    delay(thisdelay+100); 
    }
}

// One line matrix
void matrix1() {                                               
  if (huerot) thishue=thishue+5;
  if (random16(90) > 80) {
    if (thisdir == 0) leds[0] = CHSV(thishue, thissat, 255);
    else leds[NUM_LEDS-1] = CHSV(thishue, thissat, 255);
  }
  else {
    if (thisdir ==0) leds[0] = CHSV(bgclr, thissat, bgbri);
    else leds[NUM_LEDS-1] = CHSV(bgclr, thissat, bgbri);
  }
  if (thisdir == 0) {
    for (int i = NUM_LEDS-1; i >0 ; i-- ) leds[i] = leds[i-1];
  } else {
    for (int i = 0; i < NUM_LEDS ; i++ ) leds[i] = leds[i+1];
  }
  LEDS.show();  
  delay(thisdelay);
}

// LINE MATRIX
void matrix() {                                   
  int rand = random(0, 100);
  if (rand > 90) {
    leds[0] = CHSV(thishue, thissat, 255);
    thishue++;
  }
  else {leds[0] = CHSV(thishue, thissat, 0);
  thishue++;
  }
  copy_led_array();
    for(int i = 1; i < NUM_LEDS; i++ ) {
    leds[i].r = ledsX[i-1][0];
    leds[i].g = ledsX[i-1][1];
    leds[i].b = ledsX[i-1][2];    
  }
  LEDS.show();  
  delay(thisdelay);
}

void wake_light_fade_on() { // increases the red and blue channels, most beneficial for waking up
  for(int scale = 0; scale < 255; scale++) { 
    FastLED.showColor(CRGB(thisRED, thisGRN, thisBLU), scale);
    delay(thisfade);
  }
    LEDS.show();  
}

void fade_off() {
  for(int scale = 255; scale > 0; scale--) { 
    FastLED.showColor(CRGB(thisRED, thisGRN, thisBLU), scale);
    delay(10);
  }
  for (int i = 0; i < NUM_LEDS; i++) { leds[i] = CRGB::Black; }
  FastLED.show(); 
  delay(thisfade); 
}

//-FLICKER EFFECT
void flicker() {            
  int random_bright = random(0,255);
  int random_delay = random(10,100);
  int random_bool = random(0,random_bright);
  if (random_bool < 10) {
    delay(random_delay);
    for(byte i = 0 ; i < NUM_LEDS; i++ ) {
      leds[i] = CHSV(thishue, thissat, random_bright); 
    }
    LEDS.show();
    delay(random_delay);    
  }
}

//bounceFadeRain
void bounceFadeRain()
{
  fadeToBlackBy(leds, NUM_LEDS, 20);
  int pos = beatsin8(10, 0, NUM_LEDS);
  leds[pos] = CHSV(thishue, thissat, 255);
  //leds[pos] += CRGB::Magenta;
  if (pos == 1 || pos == 15) {
    hit++;
  }
  FastLED.show();
  delay(thisdelay);
}

void tropicThunder() {
  
  unsigned int randSpark = random(0, (NUM_LEDS) - 1);
  unsigned int thunderDelay = random(3, 50);

  leds[randSpark] = CRGB::Green;
  FastLED.show();
  delay(thunderDelay);
  leds[randSpark] = CRGB::Orange;
  FastLED.show();
  delay(thunderDelay);
  leds[randSpark] = CRGB::Black;
  delay(thunderDelay);

}

void unicornPurpleRain(){
  // unicorn rainDrop falls dim
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(thishue, 255, 50);

    if (i == NUM_LEDS-1) {
      leds[i] = CHSV(thishue, 255, 255);
    }
    // show led
    FastLED.show();
    // go Back to Black
    leds[i] = CRGB::Black;

    // gravity effect
    delay(80 - constrain(i * 7, 7, 70));
  }

  // bounce/splash drop back for 3 leds
  int dropBounces = 0;
  uint8_t brigthtness = 255;
  while(brigthtness > 20) {

    // bouncing routine
    while(dropBounces < 3) {
    // bounce down
      for(int i = (NUM_LEDS)-1; i >= (NUM_LEDS)-3+dropBounces; i--) {
        leds[i] = CHSV(thishue, 255, brigthtness);
        FastLED.show();
        leds[i] = CRGB::Black;
        delay(80 - (NUM_LEDS - i) * 20);
        brigthtness -= 10;
      }

      // bounce up
      for(int i =(NUM_LEDS)-3+dropBounces; i < NUM_LEDS; i++) {
        leds[i] = CHSV(thishue, 255, brigthtness);
        FastLED.show();
        leds[i] = CRGB::Black;
        delay(80 + (dropBounces * 50));
        brigthtness -= 10;
      }
      dropBounces ++;
    }

    // flow and glow then fade out
    // like water on a cold fullmoon night...

    // glow UP
    for (int i = 0; i < 40; i ++) {
      leds[NUM_LEDS-1] = CHSV(thishue, 255, brigthtness + i);
      FastLED.show();
      delay(7);

      // for every 4 loops
      if (i % 4 == 0 ) {
        // decrease brightness
        brigthtness--;
      }
    }

    // glow down
    for (int i = 40; i > 0; i --) {
      leds[NUM_LEDS-1] = CHSV(thishue, 255, brigthtness + i);
      FastLED.show();
      delay(7);

      // for every 4 loops
      if (i % 4 == 0 ) {
        // decrease brightness
        brigthtness--;
      }
    }

    leds[NUM_LEDS-1] = CRGB::Black;
    delay(20);
  }
}

//noise16
void noise16() {
  fill_noise16(leds, NUM_LEDS, octaves, x, xscale, hue_octaves, hxy, hue_scale, hue_time);
  if (thisdir == 0) {hxy+=hxyinc; x += x_speed; hue_time+= hue_speed;} else { hxy-=hxyinc; x -= x_speed; hue_time -= hue_speed;}
  FastLED.show();
  delay(thisdelay);
}

//Fire2012
void Fire2012()
{
// Array of temperature readings at each simulation cell
  static byte heat[NUM_LEDS];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUM_LEDS; j++) {
      CRGB color = HeatColor( heat[j]);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (NUM_LEDS-1) - j;
      } else {
        pixelnumber = j;
      }
      leds[pixelnumber] = color;
    }
  FastLED.show();
  delay(thisdelay);
}

//moving pixels
void moving_pixels() {  
  EVERY_N_MILLISECONDS(thisdelay*5) {

    // Set pixel color
    leds[positionRed] = CRGB::Red;
    leds[positionWhite] = CRGB::White;
    leds[positionBlue] = CRGB::Blue;
  
    // Show the pixels
    FastLED.show();
    //delay(holdTime);  // Delay for a bit.
    delay(thisdelay*5);
    // Set pixels back to Black for the next loop around.
    leds[positionRed] = CRGB::Black;
    leds[positionWhite] = CRGB::Black;
    leds[positionBlue] = CRGB::Black;
  
    // Set new position, moving (forward or backward) by delta.
    // NUM_LEDS is added to the position before doing the modulo
    // to cover cases where delta is a negative value.
    positionRed = (positionRed + thisstep + NUM_LEDS) % NUM_LEDS;
    positionWhite = (positionWhite + thisstep + NUM_LEDS) % NUM_LEDS;
    positionBlue = (positionBlue + thisstep + NUM_LEDS) % NUM_LEDS;
  }
} 

//CylonBounce
void CylonBounce(){
  int ReturnDelay = 50;
  for(int i = 0; i < NUM_LEDS-thisstep/2-2; i++) {
    leds[i] = CRGB(thisRED/10, thisGRN/10, thisBLU/10);
    for(int j = 1; j <= thisstep/2; j++) {
      leds[i+j] = CRGB(thisRED, thisGRN, thisBLU);
    }
    leds[i+thisstep/2+1] = CRGB(thisRED/10, thisGRN/10, thisBLU/10);
    LEDS.show();
    delay(thisdelay);
  }
  delay(ReturnDelay);
  for(int i = NUM_LEDS-thisstep/2-2; i > 0; i--) {
    leds[i] = CRGB(thisRED/10, thisGRN/10, thisBLU/10);
    for(int j = 1; j <= thisstep/2; j++) {
      leds[i+j] = CRGB(thisRED, thisGRN, thisBLU); 
    }
    leds[i+thisstep/2+1] = CRGB(thisRED/10, thisGRN/10, thisBLU/10);
    LEDS.show();
    delay(thisdelay);
  }
  delay(ReturnDelay);
}

//Running Lights
void RunningLights() {  
  for(int i=0; i<NUM_LEDS*2; i++)
  {
      thisstep++; // = 0; //Position + Rate;
      for(int i=0; i<NUM_LEDS; i++) {
        // sine wave, 3 offset waves make a rainbow!
        //float level = sin(i+Position) * 127 + 128;
        //setPixel(i,level,0,0);
        //float level = sin(i+Position) * 127 + 128;
       leds[i].r = ((sin(i+thisstep) * 127 + 128)/255)*255;
       leds[i].g = ((sin(i+thisstep) * 127 + 128)/255)*0;
       leds[i].b = ((sin(i+thisstep) * 127 + 128)/255)*255;
      }
      LEDS.show();
      delay(thisdelay);
  }
}

//One sine
void one_sine() {                                                             // This is the heart of this program. Sure is short.
  thisphase += thisspeed;                                                     // You can change direction and speed individually.
  thishue = thishue + thisrot;                                                // Hue rotation is fun for thiswave.
  for (int k=0; k<NUM_LEDS-1; k++) {                                          // For each of the LED's in the strand, set a brightness based on a wave as follows:
    int thisbright = qsubd(cubicwave8((k*thisstep)+thisphase), thiscutoff);    // qsub sets a minimum value called thiscutoff. If < thiscutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
    leds[k] = CHSV(bgclr, 255, bgbri);                                        // First set a background colour, but fully saturated.
    leds[k] += CHSV(thishue, thissat, thisbright);                             // Then assign a hue to any that are bright enough.
  }
  bgclr++;                                                                    // You can change the background colour or remove this and leave it fixed.
  LEDS.show();  
  delay(thisdelay);
}

//Blendme
void blendme() {
  uint8_t starthue = beatsin8(20, 0, 255);
  uint8_t endhue = beatsin8(35, 0, 255);
  if (starthue < endhue) {
    fill_gradient(leds, NUM_LEDS, CHSV(starthue,255,255), CHSV(endhue,255,255), FORWARD_HUES);    // If we don't have this, the colour fill will flip around
  } else {
    fill_gradient(leds, NUM_LEDS, CHSV(starthue,255,255), CHSV(endhue,255,255), BACKWARD_HUES);
  }
  LEDS.show();  
  delay(thisdelay);
}

//Ripple
void ripple() {
 for (int i = 0; i < NUM_LEDS; i++) leds[i] = CHSV(bgcol++, 255, thisstep);  // Rotate background colour.
  LEDS.show(); 
  switch (step) {
    case -1:                                                          // Initialize ripple variables.
      center = random(NUM_LEDS);
      colour = random8();
      step = 0;
      LEDS.show();  
      delay(thisdelay);
      break;
    case 0:
      leds[center] = CHSV(colour, 255, 255);                          // Display the first pixel of the ripple.
      step ++;
      LEDS.show(); 
      delay(thisdelay); 
      break;
    case maxsteps:                                                    // At the end of the ripples.
      step = -1;
      LEDS.show();
      delay(thisdelay);
      break;
    default:                                                                             // Middle of the ripples.
      leds[(center + step + NUM_LEDS) % NUM_LEDS] += CHSV(colour, 255, myfade/step*2);   // Simple wrap from Marc Miller
      leds[(center - step + NUM_LEDS) % NUM_LEDS] += CHSV(colour, 255, myfade/step*2);
      step ++;                                                                            // Next step.
      LEDS.show();
      delay(thisdelay);
      break;   
      LEDS.show();
  } 
}

// MOVER
void mover() { 
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] += CHSV(thishue, 255, 255);
    leds[(i+5) % NUM_LEDS] += CHSV(thishue+85, 255, 255);         // We use modulus so that the location is between 0 and NUM_LEDS
    leds[(i+10) % NUM_LEDS] += CHSV(thishue+170, 255, 255);       // Same here.
    LEDS.show();
    fadeToBlackBy(leds, NUM_LEDS, thisstep*5);                    // Low values = slower fade.
    delay(thisdelay);                                             // UGH!!!! A blocking delay. If you want to add controls, they may not work reliably.
  }
}

// LIGHTNINGS
void lightnings() {
  ledstart = random8(NUM_LEDS);           // Determine starting location of flash
  ledlen = random8(NUM_LEDS-ledstart);    // Determine length of flash (not to go beyond NUM_LEDS-1)
  for (int flashCounter = 0; flashCounter < random8(3,flashes); flashCounter++) {
    if(flashCounter == 0) dimmer = 5;     // the brightness of the leader is scaled down by a factor of 5
    else dimmer = random8(1,3);           // return strokes are brighter than the leader
    fill_solid(leds+ledstart,ledlen,CHSV(255, 0, 255/dimmer));
    FastLED.show();                       // Show a section of LED's
    delay(random8(4,10));                 // each flash only lasts 4-10 milliseconds
    fill_solid(leds+ledstart,ledlen,CHSV(255,0,0));   // Clear the section of LED's
    FastLED.show();     
    if (flashCounter == 0) delay (150);   // longer delay until next flash after the leader
    delay(50+random8(100));               // shorter delay between strokes  
  } // for()
  delay(random8(frequency)*100);          // delay between strikes
  delay(thisdelay);
}

// easeMe
void easeMe() {
  static uint8_t easeOutVal = 0;
  static uint8_t easeInVal  = 0;
  static uint8_t lerpVal    = 0;
  easeOutVal = ease8InOutQuad(easeInVal);
  easeInVal++;
  lerpVal = lerp8by8(0, NUM_LEDS, easeOutVal);
  leds[lerpVal] = CRGB::Orange;
  fadeToBlackBy(leds, NUM_LEDS, thisstep);                     // 8 bit, 1 = slow, 255 = fast
  LEDS.show();  
  delay(thisdelay);
}

// RAINBOW 'UP' THE LOOP
void rainbow_vertical() {                        
  thisindex++;
  if (thisindex > TOP_INDEX) {thisindex = 0;}  
  thishue = thishue + thisstep;
  if (thishue > 255) {thishue = 0;}
  int idexA = thisindex;
  int idexB = horizontal_index(idexA);
  leds[idexA] = CHSV(thishue, thissat, 255);
  leds[idexB] = CHSV(thishue, thissat, 255);
  LEDS.show();  
  delay(thisdelay);
}

//Three Sin
void three_sin() {
  wave1 += inc1;
  wave2 += inc2;
  wave3 += inc3;
  for (int k=0; k<NUM_LEDS; k++) {
    leds[k].r = qsub8(sin8(mul1*k + wave1), lvl1);         // Another fixed frequency, variable phase sine wave with lowered level
    leds[k].g = qsub8(sin8(mul2*k + wave2), lvl2);         // A fixed frequency, variable phase sine wave with lowered level
    leds[k].b = qsub8(sin8(mul3*k + wave3), lvl3);         // A fixed frequency, variable phase sine wave with lowered level
  }
  LEDS.show();  
  delay(thisdelay);
}

// KNIGHT INDUSTIES 2000
void kitt() {                                     
  int rand = random(0, TOP_INDEX);
  for(int i = 0; i < rand; i++ ) {
    leds[TOP_INDEX+i] = CHSV(thishue, thissat, 255);
    leds[TOP_INDEX-i] = CHSV(thishue, thissat, 255);
    LEDS.show();
    delay((thisdelay*2)/rand);
  }
  for(int i = rand; i > 0; i-- ) {
    leds[TOP_INDEX+i] = CHSV(thishue, thissat, 0);
    leds[TOP_INDEX-i] = CHSV(thishue, thissat, 0);
    LEDS.show();
    delay((thisdelay*2)/rand);
  }  
}

void RightToLeft(byte red, byte green, byte blue, int ReturnDelay) {
  for(int i = NUM_LEDS-thisstep-2; i > 0; i--) {
    one_color_all(0,0,0);
    leds[i] = CRGB(red/10, green/10, blue/10);
    for(int j = 1; j <= thisstep; j++) {
      leds[i+j] = CRGB(red, green, blue); 
    }
    leds[i+thisstep+1] = CRGB(red/10, green/10, blue/10);
    LEDS.show();
    delay(thisdelay);
  }
  delay(ReturnDelay);
}

void LeftToRight(byte red, byte green, byte blue, int ReturnDelay) {
  for(int i = 0; i < NUM_LEDS-thisstep-2; i++) {
    one_color_all(0,0,0);
    leds[i] = CRGB(red/10, green/10, blue/10);
    for(int j = 1; j <= thisstep; j++) {
      leds[i+j] = CRGB(red, green, blue); 
    }
    leds[i+thisstep+1] = CRGB(red/10, green/10, blue/10);
    LEDS.show();
    delay(thisdelay);
  }
  delay(ReturnDelay);
}

void OutsideToCenter(byte red, byte green, byte blue, int ReturnDelay) {
  for(int i = 0; i<=((NUM_LEDS-thisstep)/2); i++) {
    one_color_all(0,0,0);
    leds[i] = CRGB(red/10, green/10, blue/10);
    for(int j = 1; j <= thisstep; j++) {
      leds[i+j] = CRGB(red, green, blue); 
    }
    leds[i+thisstep+1] = CRGB(red/10, green/10, blue/10);    
    leds[NUM_LEDS-i] = CRGB(red/10, green/10, blue/10);
    for(int j = 1; j <= thisstep; j++) {
      leds[NUM_LEDS-i-j] = CRGB(red, green, blue); 
    }
    leds[NUM_LEDS-i-thisstep-1] = CRGB(red/10, green/10, blue/10);
    LEDS.show();
    delay(thisdelay);
  }
  delay(ReturnDelay);
}

void CenterToOutside(byte red, byte green, byte blue, int ReturnDelay) {
  for(int i =((NUM_LEDS-thisstep)/2); i>=0; i--) {
    one_color_all(0,0,0);    
    leds[i] = CRGB(red/10, green/10, blue/10);
    for(int j = 1; j <= thisstep; j++) {
      leds[i+j] = CRGB(red, green, blue); 
    }
    leds[i+thisstep+1] = CRGB(red/10, green/10, blue/10);        
    leds[NUM_LEDS-i] = CRGB(red/10, green/10, blue/10);
    for(int j = 1; j <= thisstep; j++) {
      leds[NUM_LEDS-i-j] = CRGB(red, green, blue); 
    }
    leds[NUM_LEDS-i-thisstep-1] = CRGB(red/10, green/10, blue/10);
    LEDS.show();
    delay(thisdelay);
  }
  delay(ReturnDelay);
}

//NewKITT
void NewKITT(byte red, byte green, byte blue, int ReturnDelay){
  RightToLeft(red, green, blue, ReturnDelay);
  LeftToRight(red, green, blue, ReturnDelay);
  OutsideToCenter(red, green, blue, ReturnDelay);
  CenterToOutside(red, green, blue, ReturnDelay);
  LeftToRight(red, green, blue, ReturnDelay);
  RightToLeft(red, green, blue, ReturnDelay);
  OutsideToCenter(red, green, blue, ReturnDelay);
  CenterToOutside(red, green, blue, ReturnDelay);
}

// FADE ALL LEDS THROUGH HSV RAINBOW
void rainbow_fade() {                         
    thishue++;
    if (thishue > 255) {thishue = 0;}
    for(int idex = 0 ; idex < NUM_LEDS; idex++ ) {
      leds[idex] = CHSV(thishue, thissat, 255);
    }
    LEDS.show();    
    delay(thisdelay);
}

// RANDOM INDEX/COLOR
void random_burst() {                         
  thisindex = random(0, NUM_LEDS);
  thishue = random(0, 255);  
  leds[thisindex] = CHSV(thishue, thissat, 255);
  LEDS.show();
  delay(thisdelay);
}

// Twinkle
void twinkle() {
  // Make sure we're at least utilizing ALL the LED's.
  if (ranamount >NUM_LEDS) ranamount = NUM_LEDS;
  // Set random value  
  int idex = random16(0, ranamount);
  // Light up a random Led in Blue or White (Blue if Pair, White if not)
  if (idex < NUM_LEDS && n % 2 == 0) {                                    
      leds[idex] = CRGB::Blue;
      n++;
  } else {
      leds[idex] = CRGB::White;
      n++;
  } 
  // Go through the array and reduce each RGB value by a percentage.
  for (int i = 0; i <NUM_LEDS; i++) leds[i].nscale8(myfade); 
  LEDS.show();  
  delay(thisdelay);
}

//RAINBOW FADE FROM FAST_SPI2
void new_rainbow_loop(){                       
  ihue -= 1;
  fill_rainbow( leds, NUM_LEDS, ihue );
  LEDS.show();
  delay(thisdelay);
}

//RAINBOW FADE FROM FAST_SPI2
void new_rainbow_loop_addGlitter(){                       
  ihue -= 1;
  fill_rainbow( leds, NUM_LEDS, ihue );
  addGlitter(80); 
  LEDS.show();
  delay(thisdelay);
}

//LOOP HSV RAINBOW
void rainbow_loop() {                        
  thisindex++;
  ihue = ihue + thisstep;
  if (thisindex >= NUM_LEDS) {thisindex = 0;}
  if (ihue > 255) {ihue = 0;}
  leds[thisindex] = CHSV(ihue, thissat, 255);
  LEDS.show();
  delay(thisdelay);
}

//EMERGENCY LIGHTS (TWO COLOR SINGLE LED)
void ems_lightsONE() {                    
  thisindex++;
  if (thisindex >= NUM_LEDS) {thisindex = 0;}
  int idexR = thisindex;
  int idexB = antipodal_index(idexR);
  int thathue = (thishue + 160) % 255;  
  for(int i = 0; i < NUM_LEDS; i++ ) {
    if (i == idexR) {leds[i] = CHSV(thishue, thissat, 255);}
    else if (i == idexB) {leds[i] = CHSV(thathue, thissat, 255);}    
    else {leds[i] = CHSV(0, 0, 0);}
  }
  LEDS.show();  
  delay(thisdelay);
}

//EMERGENCY LIGHTS (TWO COLOR SOLID)
void ems_lightsALL() {                  
  thisindex++;
  if (thisindex >= NUM_LEDS) {thisindex = 0;}
  int idexR = thisindex;
  int idexB = antipodal_index(idexR);
  int thathue = (thishue + 160) % 255;
  leds[idexR] = CHSV(thishue, thissat, 255);
  leds[idexB] = CHSV(thathue, thissat, 255);  
  LEDS.show();  
  delay(thisdelay);
}

// QUICK 'N DIRTY RANDOMIZE TO GET CELL AUTOMATA STARTED  
void random_red() {                       
  int temprand;
  for(int i = 0; i < NUM_LEDS; i++ ) {
    temprand = random(0,100);
    if (temprand > 50) {leds[i].r = 255;}
    if (temprand <= 50) {leds[i].r = 0;}
    leds[i].b = 0; leds[i].g = 0;
  }
  LEDS.show();  
}

// 1D CELLULAR AUTOMATA - RULE 30 (RED FOR NOW)
void rule30() {                          
  if (bouncedirection == 0) {
    random_red();
    bouncedirection = 1;
  }
  copy_led_array();
  int iCW;
  int iCCW;
  int y = 100;  
  for(int i = 0; i < NUM_LEDS; i++ ) {
    iCW = adjacent_cw(i);
    iCCW = adjacent_ccw(i);
    if (ledsX[iCCW][0] > y && ledsX[i][0] > y && ledsX[iCW][0] > y) {leds[i].r = 0;}
    if (ledsX[iCCW][0] > y && ledsX[i][0] > y && ledsX[iCW][0] <= y) {leds[i].r = 0;}
    if (ledsX[iCCW][0] > y && ledsX[i][0] <= y && ledsX[iCW][0] > y) {leds[i].r = 0;}
    if (ledsX[iCCW][0] > y && ledsX[i][0] <= y && ledsX[iCW][0] <= y) {leds[i].r = 255;}
    if (ledsX[iCCW][0] <= y && ledsX[i][0] > y && ledsX[iCW][0] > y) {leds[i].r = 255;}
    if (ledsX[iCCW][0] <= y && ledsX[i][0] > y && ledsX[iCW][0] <= y) {leds[i].r = 255;}
    if (ledsX[iCCW][0] <= y && ledsX[i][0] <= y && ledsX[iCW][0] > y) {leds[i].r = 255;}
    if (ledsX[iCCW][0] <= y && ledsX[i][0] <= y && ledsX[iCW][0] <= y) {leds[i].r = 0;}
  }
  LEDS.show();  
  delay(thisdelay*2);
}

// JUGGLE
void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy(leds, NUM_LEDS, 20);
  byte thishue = 0;
  for (int i = 0; i < 8; i++) {
    leds[beatsin16(i+7,0,NUM_LEDS)] |= CHSV(thishue, 200, 255);
    thishue += 32;
  }
    LEDS.show();
   delay(thisdelay);
}

// PULSE SATURATION ON ALL LEDS TO ONE COLOR 
void pulse_one_color_all_rev() {           
  if (bouncedirection == 0) {
    isat++;
    if (isat >= 255) {bouncedirection = 1;}
  }
  if (bouncedirection == 1) {
    isat = isat - 1;
    if (isat <= 1) {bouncedirection = 0;}         
  }  
    for(int idex = 0 ; idex < NUM_LEDS; idex++ ) {
      leds[idex] = CHSV(thishue, isat, 255);
    }
    LEDS.show();
    delay(thisdelay);
}

// PULSE BRIGHTNESS ON ALL LEDS TO ONE COLOR 
void pulse_one_color_all() {              
  if (bouncedirection == 0) {
    ibright++;
    if (ibright >= 255) {bouncedirection = 1;}
  }
  if (bouncedirection == 1) {
    ibright = ibright - 1;
    if (ibright <= 1) {bouncedirection = 0;}         
  }  
    for(int idex = 0 ; idex < NUM_LEDS; idex++ ) {
      leds[idex] = CHSV(thishue, thissat, ibright);
    }
    LEDS.show();    
    delay(thisdelay);
}

// FLAMEISH 
void flame() {                                    
  int idelay = random(0,35);
  float hmin = 0.1; float hmax = 45.0;
  float hdif = hmax-hmin;
  int randtemp = random(0,3);
  float hinc = (hdif/float(TOP_INDEX))+randtemp;
  int ihue = hmin;
  for(int i = 0; i <= TOP_INDEX; i++ ) {
    ihue = ihue + hinc;
    leds[i] = CHSV(ihue, thissat, 255);
    int ih = horizontal_index(i);    
    leds[ih] = CHSV(ihue, thissat, 255);    
    leds[TOP_INDEX].r = 255; leds[TOP_INDEX].g = 255; leds[TOP_INDEX].b = 255;    
    LEDS.show();    
    delay(idelay);
  }
}

// RANDOM COLOR POP
void random_color_pop() {                         
  thisindex = random(0, NUM_LEDS);
  ihue = random(0, 255);
  one_color_all(0, 0, 0);
  leds[thisindex] = CHSV(ihue, thissat, 255);
  LEDS.show();
  delay(thisdelay);
}

// RGB PROPELLER 
void rgb_propeller() {                           
  thisindex++;
  int ghue = (thishue + 80) % 255;
  int bhue = (thishue + 160) % 255;
  int N3  = int(NUM_LEDS/3);
  int N6  = int(NUM_LEDS/6);  
  int N12 = int(NUM_LEDS/12);  
  for(int i = 0; i < N3; i++ ) {
    int j0 = (thisindex + i + NUM_LEDS - N12) % NUM_LEDS;
    int j1 = (j0+N3) % NUM_LEDS;
    int j2 = (j1+N3) % NUM_LEDS;    
    leds[j0] = CHSV(thishue, thissat, 255);
    leds[j1] = CHSV(ghue, thissat, 255);
    leds[j2] = CHSV(bhue, thissat, 255);    
  }
  LEDS.show();    
  delay(thisdelay);  
}

// BOUNCE COLOR (SINGLE LED)
void color_bounce() {                        
  if (bouncedirection == 0) {
    thisindex = thisindex + 1;
    if (thisindex == NUM_LEDS) {
      bouncedirection = 1;
      thisindex = thisindex - 1;
    }
  }
  if (bouncedirection == 1) {
    thisindex = thisindex - 1;
    if (thisindex == 0) {
      bouncedirection = 0;
    }
  }  
  for(int i = 0; i < NUM_LEDS; i++ ) {
    if (i == thisindex) {leds[i] = CHSV(random(0, 255), thissat, 255);}
    else {leds[i] = CHSV(0, 0, 0);}
  }
  LEDS.show();
  delay(thisdelay);
}

// BOUNCE COLOR (SIMPLE MULTI-LED FADE)
void color_bounceFADE() {                    
  if (bouncedirection == 0) {
    thisindex = thisindex + 1;
    if (thisindex == NUM_LEDS) {
      bouncedirection = 1;
      thisindex = thisindex - 1;
    }
  }
  if (bouncedirection == 1) {
    thisindex = thisindex - 1;
    if (thisindex == 0) {
      bouncedirection = 0;
    }
  }
  int iL1 = adjacent_cw(thisindex);
  int iL2 = adjacent_cw(iL1);
  int iL3 = adjacent_cw(iL2);
  int iR1 = adjacent_ccw(thisindex);
  int iR2 = adjacent_ccw(iR1);
  int iR3 = adjacent_ccw(iR2);
  for(int i = 0; i < NUM_LEDS; i++ ) {
    if (i == thisindex) {leds[i] = CHSV(thishue, thissat, 255);}
    else if (i == iL1) {leds[i] = CHSV(thishue, thissat, 150);}
    else if (i == iL2) {leds[i] = CHSV(thishue, thissat, 80);}
    else if (i == iL3) {leds[i] = CHSV(thishue, thissat, 20);}        
    else if (i == iR1) {leds[i] = CHSV(thishue, thissat, 150);}
    else if (i == iR2) {leds[i] = CHSV(thishue, thissat, 80);}
    else if (i == iR3) {leds[i] = CHSV(thishue, thissat, 20);}    
    else {leds[i] = CHSV(0, 0, 0);}
  }
  LEDS.show();
  delay(thisdelay);
}

// FADE 'UP' THE LOOP
void fade_vertical() {                    
  thisindex++;
  if (thisindex > TOP_INDEX) {thisindex = 0;}  
  int idexA = thisindex;
  int idexB = horizontal_index(idexA);
  ibright = ibright + 10;
  if (ibright > 255) {ibright = 0;}
  leds[idexA] = CHSV(thishue, thissat, ibright);
  leds[idexB] = CHSV(thishue, thissat, ibright);
  LEDS.show();
  delay(thisdelay);
}

// RANDOM MARCH CCW
void random_march() {                   
  copy_led_array();
  int iCCW;
  leds[0] = CHSV(random(0,255), 255, 255);
  for(int thisindex = 1; thisindex < NUM_LEDS ; thisindex++ ) {
    iCCW = adjacent_ccw(thisindex);
    leds[thisindex].r = ledsX[iCCW][0];
    leds[thisindex].g = ledsX[iCCW][1];
    leds[thisindex].b = ledsX[iCCW][2];
  }
  LEDS.show();  
  delay(thisdelay);
}

// R,W,B MARCH CCW
void rwb_march() {                    
  copy_led_array();
  int iCCW;
  thisindex++;
  if (thisindex > 2) {thisindex = 0;}
  switch (thisindex) {
    case 0:
      leds[0].r = 255;
      leds[0].g = 0;
      leds[0].b = 0;
    break;
    case 1:
      leds[0].r = 255;
      leds[0].g = 255;
      leds[0].b = 255;
    break;
    case 2:
      leds[0].r = 0;
      leds[0].g = 0;
      leds[0].b = 255;
    break;
  }
    for(int i = 1; i < NUM_LEDS; i++ ) {
      iCCW = adjacent_ccw(i);
      leds[i].r = ledsX[iCCW][0];
      leds[i].g = ledsX[iCCW][1];
      leds[i].b = ledsX[iCCW][2];    
    }
  LEDS.show();  
  delay(thisdelay);
}

// SORT OF RADIATION SYMBOLISH
void radiation() {                   
  int N3  = int(NUM_LEDS/3);
  int N6  = int(NUM_LEDS/6);  
  int N12 = int(NUM_LEDS/12);  
  for(int i = 0; i < N6; i++ ) {     //-HACKY, I KNOW...
    tcount = tcount + .02;
    if (tcount > 3.14) {tcount = 0.0;}
    ibright = int(sin(tcount)*255);    
    int j0 = (i + NUM_LEDS - N12) % NUM_LEDS;
    int j1 = (j0+N3) % NUM_LEDS;
    int j2 = (j1+N3) % NUM_LEDS;    
    leds[j0] = CHSV(thishue, thissat, ibright);
    leds[j1] = CHSV(thishue, thissat, ibright);
    leds[j2] = CHSV(thishue, thissat, ibright);    
  }    
  LEDS.show();    
  delay(thisdelay);    
}

// COLOR LOOP (SINGLE LED) w/ VARIABLE DELAY
void color_loop_vardelay() {                    
  thisindex++;
  if (thisindex > NUM_LEDS) {thisindex = 0;}
  int di = abs(TOP_INDEX - thisindex);
  int t = constrain((10/di)*10, 10, 500);
  for(int i = 0; i < NUM_LEDS; i++ ) {
    if (i == thisindex) {
      leds[i] = CHSV(0, thissat, 255);
    }
    else {
      leds[i].r = 0; leds[i].g = 0; leds[i].b = 0;
    }
  }
  LEDS.show();  
  delay(t);
}

// BRIGHTNESS SINE WAVE
void sin_bright_wave() {        
  for(int i = 0; i < NUM_LEDS; i++ ) {
    tcount = tcount + .1;
    if (tcount > 3.14) {tcount = 0.0;}
    ibright = int(sin(tcount)*255);
    leds[i] = CHSV(thishue, thissat, ibright);
    LEDS.show();    
    delay(thisdelay);
  }
}

// POP FROM LEFT TO RIGHT UP THE RING
void pop_horizontal() {        
  int ix;
  if (bouncedirection == 0) {
    bouncedirection = 1;
    ix = thisindex;  
  }
  else if (bouncedirection == 1) {
    bouncedirection = 0;
    ix = horizontal_index(thisindex);
    thisindex++;
    if (thisindex > TOP_INDEX) {thisindex = 0;}      
  }
  for(int i = 0; i < NUM_LEDS; i++ ) {
    if (i == ix) {
      leds[i] = CHSV(thishue, thissat, 255);
    }
    else {
      leds[i].r = 0; leds[i].g = 0; leds[i].b = 0;
    }
  }
  LEDS.show();
  delay(thisdelay);    
}

void demo_modeA(){
  int r = 10;
  thisdelay = 20; thisstep = 10; thishue = 0; thissat = 255;
  one_color_all(255,255,255); LEDS.show(); delay(1200);
  for(int i=0; i<r*25; i++) {rainbow_fade();}
  for(int i=0; i<r*20; i++) {rainbow_loop();}
  for(int i=0; i<r*20; i++) {random_burst();}
  for(int i=0; i<r*12; i++) {color_bounce();}
  thisdelay = 40;
  for(int i=0; i<r*12; i++) {color_bounceFADE();}
  for(int i=0; i<r*6; i++) {ems_lightsONE();}
  for(int i=0; i<r*5; i++) {ems_lightsALL();}
  thishue = 160; thissat = 50;  
  for(int i=0; i<r*40; i++) {flicker();}
  one_color_all(0,0,0); LEDS.show();
  thisdelay = 15; thishue = 0; thissat = 255;
  for(int i=0; i<r*50; i++) {pulse_one_color_all();}
  for(int i=0; i<r*40; i++) {pulse_one_color_all_rev();}
  thisdelay = 60; thishue = 180; 
  for(int i=0; i<r*5; i++) {fade_vertical();}
  random_red();
  thisdelay = 100;
  for(int i=0; i<r*5; i++) {rule30();}
  thisdelay = 60;
  for(int i=0; i<r*40; i++) {ripple();}
  thisdelay = 40;
  for(int i=0; i<r*8; i++) {random_march();}
  thisdelay = 80;
  for(int i=0; i<r*5; i++) {rwb_march();}
  one_color_all(0,0,0); ; LEDS.show();
  thisdelay = 60; thishue = 95; 
  for(int i=0; i<r*15; i++) {radiation();}
  for(int i=0; i<r*15; i++) {color_loop_vardelay();}
  thisdelay = 35; thishue = 180; 
  for(int i=0; i<r; i++) {sin_bright_wave();}
  thisdelay = 100; thishue = 0; 
  for(int i=0; i<r*5; i++) {pop_horizontal();}
  thisdelay = 100; thishue = 180; 
  for(int i=0; i<r*4; i++) {NewKITT(0xff, 0, 0, 50);}
  for(int i=0; i<r*3; i++) {flame();}
  thisdelay = 50;
  for(int i=0; i<r*12; i++) {rainbow_vertical();}
  thisdelay = 100;
  for(int i=0; i<r*3; i++) {ripple();}
  for(int i=0; i<r*3; i++) {RunningLights();}
  for(int i=0; i<r*120; i++) {new_rainbow_loop();}
//  one_color_all(255,0,0); LEDS.show(); delay(1200);
//  one_color_all(0,255,0); LEDS.show(); delay(1200);
//  one_color_all(0,0,255); LEDS.show(); delay(1200);
//  one_color_all(255,255,0); LEDS.show(); delay(1200);
//  one_color_all(0,255,255); LEDS.show(); delay(1200);
//  one_color_all(255,0,255); LEDS.show(); delay(1200);
}

#endif
