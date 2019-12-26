#include <Arduino.h>
#include "LightAnimation.h"

/// KnightRider animation
/// 
/// @param init indicates that we can make some sort of initialization
void LightAnimation::AnimKnight( bool init = false)
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
