#include <Arduino.h>
#include <FastLED.h>

// Put here the number of LEDs you have.
#define NUM_LEDS 50

// define here your type of strip.
#define LED_TYPE WS2811

// define here the color order of the strip.
#define COLOR_ORDER RGB

// define the led strip output number.
#define LED_PIN 6

// pin where the button to change mode is connected
#define I_CHANGE_MODE 7

// Global variables
/// Led array
CRGB _leds[NUM_LEDS];

/// Current Animation
int  _mode=0;

/// Total number of animations, it is used to return to the first animation.
/// Once reached the end.
int const MAX_MODES = 14;

/// Indicates that the mode has just changed.
bool _modeChanged = true;
  
/// Actual speed 100 is normal.
int _speed = 100;

/// Current color 0-255 if 255 and make _hue++ it automatically goes to 0.
uint8_t _hue  = 0;

/// number of the current led in moving light animations
int _movingLed = 0;

/// direction of the animation in up/down animations
bool _sense;

/// palette
CRGBPalette16 _pal;

// Setup
void setup() {
  // Serial for debugging
  Serial.begin(9600);
  Serial.print("start");

  // out pin for led strip
  pinMode(LED_PIN, OUTPUT);

  // Init FastLED library
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(_leds, NUM_LEDS);

  // Define Change mode button input with pull-up
  pinMode(I_CHANGE_MODE, INPUT_PULLUP);
  
  ChangeAnimation (1);
}

// Loop
void loop() {
  // Change mode button state and last state to detect fall-Down
  int buttonState;
  static int LastButtonState;

  // read button, if button is just pressed change to next animation
  buttonState = digitalRead(I_CHANGE_MODE);

  if ( buttonState == LOW && LastButtonState==HIGH)
    ChangeNextAnimation();

  LastButtonState = buttonState;
  
  // Refresh animation  
  AnimationUpdate();
}

/// Change animation number mode.
void ChangeAnimation(int mode)
{
  _mode = mode;

  // flag that mode has changed -for initializations-
  _modeChanged = true;
}

/// Change to next animation
void ChangeNextAnimation()
{
  _mode++;

  // if we reached the total of animations return to first one
  if (_mode > MAX_MODES)
    _mode = 1;

  // set flag that mode has changed -for initializations-
  _modeChanged = true;
}

/// set speed of animations
void ChangeSpeed(int speed)
{
  _speed = speed;
}

/// set brightness
void ChangeBrightness(int brightnes)
{
  //Not implemented
}

/// Add randomly glitter
/// From FastLight Examples
/// @param chanceOfGlitter of 256
void AddGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter)
  _leds[ random16(NUM_LEDS) ] += CRGB::White;
}

/// we move a sinus wave and iterate through different colours
/// we try to put one period in the whole led strip
/// @param init indicates that we can make some sort of initialization
void AnimWave(bool init = false)
{ // waves
    static int t     = 0; // current "time"

    int T = NUM_LEDS;

    // copy each Led with previous one
    for (int i = 0; i < NUM_LEDS - 1; i++)
        _leds[i] = _leds[i + 1];
    
    // put color and value of last led
    _leds[NUM_LEDS - 1] = CHSV(_hue, 255, sin8 ( t * 255 / T ) / 2 + 120);
    
    // increase time
    t++;

    // if the end of the wave Period start a new wave again and change color
    if (t == T)
    {
        t = 0;
        _hue++;
    }

    // delay to next
    delay ( 50 * _speed / 100 );
}

/// Like waves but static, the whole strip fades in an out
/// @param init indicates that we can make some sort of initialization
void AnimHeartBeat(bool init = false)
{ 
    static int t     = 0; // current "time"

    int T = NUM_LEDS;
    
    // put color and value of first led
    _leds[0] = CHSV(_hue, 255, sin8 ( t * 255 / T ) / 2 + 32);

    // Copy all the leds
    for (int i = 1; i < NUM_LEDS; i++)
      _leds[i] = _leds[0];
      
    // increase time
    t++;

    // if the end of the wave Period start a new wave again and change color
    if (t == T)
    {
        t = 0;
        _hue++;
    }

    // delay to next
    delay ( 50 * _speed / 100 );
}

/// Move a random color to top
///
/// @param init indicates that we can make some sort of initialization 
void AnimArianna(bool init = false)
{ //Arianna

  static int lastLED   = NUM_LEDS; // last led

  if (init){
    _movingLed = 0;
    lastLED   = NUM_LEDS;
  }
  
  // Put a color if is the first led of an iteration or fade it
  if (_movingLed == 0)
  {
    _leds[0] = CHSV(random(256), 255, 255);
    lastLED--;
  }
  else
    _leds[0].fadeToBlackBy(192);

  // move every led value to next one
  for (int i = lastLED; i > 0; i--)
    _leds[i] = _leds[i - 1];
  
  // moving led is the next one
  _movingLed++;
 
  // if the last led is the first one
  // begin again
  if (lastLED == 1)
    lastLED=NUM_LEDS;

  delay ( 50 * _speed / 100 );
}

/// KnightRider animation
/// 
/// @param init indicates that we can make some sort of initialization
void AnimKnight( bool init = false)
{
  fadeToBlackBy(_leds, NUM_LEDS,64); // attenuate every led a little

  if (init)
    _movingLed = 0;

  if (_sense) // one direction
    _leds[_movingLed]              = CRGB::Red;
  else        // other direction
    _leds[NUM_LEDS -1 -_movingLed] = CRGB::Red;

    _movingLed ++;

  if (_movingLed == NUM_LEDS )
     _sense = !_sense;
      
  delay( 50 * _speed / 100 );
}

/// Alternating between odds an evens
///
/// @param init indicates that we can make some sort of initialization 
void AnimAlternating(bool init = false)
{

  // counter we change every 50 isf _speed= 100 -> 1 second
  static int counter = 0;
  static bool pair = false ;        // current moving led
  
  if (init){
    // everyled off
    for (int i = 0; i < NUM_LEDS; i++)
    _leds[i] = CRGB::Black;
    counter = 0;
  }

  // put every led to the same  random color
  if (counter == 0)
  {

    // move every led value to next one
    for (int i = NUM_LEDS - 1; i > 0; i--)
      _leds[i] = _leds[i - 1];
    
    // Put a color if is the first led of an iteration or fade it
    if (pair)
      _leds[0] = CHSV(random(256), 255, 255);
    else
      _leds[0] = CRGB::Black;
   
    //alternate pair value & start counter
    pair = !pair;
    counter = 10;
  }
  else
    counter--;
  
  delay ( 50 * _speed / 100 );
}

/// Animation as painter brushes
/// elects randomly a start led, color and direction
///
/// @param init indicates that we can make some sort of initialization 
void AnimDali(bool init = false)
{ 
  // First fade all
  fadeToBlackBy( _leds, NUM_LEDS, 32);

  static int  length  = 0;
  
  // if we are not painting start a new
  if (length == 0 )
  {
    _movingLed = random(NUM_LEDS);
    _sense     = !_sense;
    _hue       = random(256);
    length     = random(NUM_LEDS);
  }
  else 
  {
    // If we have not ended painting paint it
    _leds[_movingLed] = CHSV(_hue, 255, 255);

    // Mark next pixel to be painted, decrease the remaining length
    // to be painted
    if (_sense)
        _movingLed++;
    else
        _movingLed--;
    length --;
 }
  
  delay ( 50 * _speed / 100 );
}

/// Animation glitters
/// elects randomly a start led, color and direction
/// @param init indicates that we can make some sort of initialization
void AnimGlitter(bool init = false)
{ 
  // First fade all
  fadeToBlackBy( _leds, NUM_LEDS, 32);

  // Glitter
  _leds[ random16(NUM_LEDS) ] += CRGB::White;

  delay ( 50 * _speed / 100 );
}

/// RainDrops
/// elects randomly a start led, and goes down due gravity
///
/// @param init indicates that we can make some sort of initialization
void AnimRainDrops(bool init = false)
{ 
  // Generate new drops
  AddGlitter(20);

  // Copy every white led down
  for (int i =  0; i < NUM_LEDS; i++)
  {
        // copy to previous if white (r=g=b=255) and is not the first
        if ( (_leds[i].r ==  255 ) && ( i != 0 ) )
           _leds[ i - 1 ] = _leds[i]; 

        // fade to black
        _leds[i].fadeToBlackBy(64); 
  }
     
  delay ( 25 * _speed / 100 );
}

/// Lightings
/// like glitter but with length
///
/// @param init indicates that we can make some sort of initialization
void AnimLightings(bool init = false)
{ 
  // First fade all
  fadeToBlackBy( _leds, NUM_LEDS, 128);

  // Choice of lighting 
  if( random8() < 40) {
    int nled   = random16(NUM_LEDS);
    int length = random16(NUM_LEDS/4);
      
    // copy up and down, check limits
    for (int i =  0; i < length; i++){
      if ( (nled+ i ) < NUM_LEDS )
        _leds[ nled + i ] += CRGB::White;
        
      if ( (nled-i ) >= NUM_LEDS )
        _leds[ nled - i ] += CRGB::White;
    }
    
  }
  delay ( 50 * _speed / 100 );
}

// From FasLED examples
/// @param init indicates that we can make some sort of initialization
void AnimFLStaticRandom(bool init = false)
{ 
  // counter we change every 50 isf _speed= 100 -> 1 second
  static int counter = 0;

  // At start counter to cero to start animation
  if (init)
    counter = 0; 

  // put every led to the same  random color
  if (counter == 0)
  {
    _leds[0] = CHSV(random(256), 255, 255);
      
    for (int i = 1; i < NUM_LEDS-1; i++)
      _leds[i] = _leds[0];

    counter = 40;
  }
  else
    counter--;
  
  delay ( 50 * _speed / 100 );
}


/// first light, a running white led
/// @param init indicates that we can make some sort of initialization
void AnimFLFirstLight(bool init = false)
{
  // Delete last one
  _leds[_movingLed] = CRGB::Black;
  
  // moving led is the next one
  _movingLed++;

  // we do it here since we can have array overflow
  if (_movingLed >= NUM_LEDS )
    _movingLed = 0;

  // light this one
  _leds[_movingLed] = CRGB::White;

  delay ( 50 * _speed / 100 );
}

/// no idea what is this
/// @param init indicates that we can make some sort of initialization
void AnimFLCylon(bool init = false)
{
  fadeToBlackBy(_leds, NUM_LEDS,16); // attenuates every led a little

  if (init)
    _movingLed = 0;

  if (_sense) // one direction
    _leds[_movingLed]              = CHSV(_hue++, 255, 255);
  else // other direction
    _leds[NUM_LEDS -1 -_movingLed] = CHSV(_hue++, 255, 255);

    _movingLed ++;

  if (_movingLed == NUM_LEDS )
    _sense = !_sense;
      
    delay ( 50 * _speed / 100 );
  }

/// Fire from fastLED examples
/// @param init indicates that we can make some sort of initialization
void AnimFLFire2012(bool init = false)
{
  if (init)
    _pal = HeatColors_p;
  
  // Add entropy to random number generator; we use a lot of it.
  random16_add_entropy( random());

  // Array of temperature readings at each simulation cell
  static byte heat[NUM_LEDS];
  static byte cooling = 50;
  static byte sparkling = 120;

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((cooling * 10) / NUM_LEDS) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < sparkling ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUM_LEDS; j++) {
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
      _leds[j] = ColorFromPalette( _pal,  scale8(heat[j], 240));
     
    }
  delay ( 50 * _speed / 100 );
}

/// Juggle form fastLED examples
/// @param init indicates that we can make some sort of initialization
void AnimFLJuggle(bool init = false) {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( _leds, NUM_LEDS, 32);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    _leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
   delay ( 50 * _speed / 100 );
}

/// Updates the animation, if there is a mode change it changes the mode informating that mode has just changed
void AnimationUpdate()
{
  switch (_mode)
  {
    case 1:
      AnimWave(_modeChanged);
      break;
    case 2:
      AnimHeartBeat(_modeChanged);
      break; 
    case 3:
      AnimArianna(_modeChanged);
      break;
    case 4:
      AnimKnight(_modeChanged);
      break;
    case 5:
      AnimAlternating(_modeChanged);
      break;
    case 6:
      AnimDali(_modeChanged);
      break;
    case 7:
      AnimGlitter(_modeChanged);  
      break;
    case 8:
      AnimRainDrops(_modeChanged);  
      break;
    case 9:
      AnimLightings(_modeChanged);
      break;
    case 10:
      AnimFLStaticRandom(_modeChanged);
      break;
    case 11:
      AnimFLFirstLight(_modeChanged);
      break;
    case 12:
      AnimFLFire2012(_modeChanged);
      break;
    case 13:
      AnimFLCylon(_modeChanged);
      break;
    case 14:
      AnimFLJuggle(_modeChanged);
      break;
  }

  // Control of _movingled if reaches any of both ends
  // if reaches the end or begin, begin again
  if (_movingLed >= NUM_LEDS )
    _movingLed = 0;

  if (_movingLed <= -1 )
    _movingLed = NUM_LEDS -1;

  // return to mode not changed
  _modeChanged = false;

  // Show leds
  FastLED.show();
}


