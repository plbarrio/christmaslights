#include <Arduino.h>
#include "LightAnimation.h"

/// Animation glitters
/// elects randomly a start led, color and direction
/// @param init indicates that we can make some sort of initialization
void LightAnimation::AnimGlitter(bool init = false)
{ 
  // First fade all
  fadeToBlackBy( _leds, NUM_LEDS, 32);

  // Glitter
  _leds[ random16(NUM_LEDS) ] += CRGB::White;

  delay ( 50 * _speed / 100 );
}
