/* Adapted from
 *  FastLedExamples
 */

#include <Arduino.h>
#include "LightAnimation.h"

/// Fixed random colors
void LightAnimation::AnimFLStaticRandom(bool init = false)
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
void LightAnimation::AnimFLFirstLight(bool init = false)
{  
  // Delete last one
  _leds[_movingLed] = CRGB::Black;
  
  // moving led is the next one
  _movingLed++;

  // if reaches the end begin again
  if (_movingLed >= NUM_LEDS )
    _movingLed = 0;

  // light this one
  _leds[_movingLed] = CRGB::White;

  delay ( 50 * _speed / 100 );
}

void LightAnimation::AnimFLCylon(bool init = false)
{
  fadeToBlackBy(_leds, NUM_LEDS,16); // attenuate every led a little

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

void LightAnimation::AnimFLFire2012(bool init = false)
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

void LightAnimation::AnimFLJuggle(bool init = false) {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( _leds, NUM_LEDS, 32);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    _leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
   delay ( 50 * _speed / 100 );
}
