#include <Arduino.h>
#include "LightAnimation.h"

/// Add randomly glitter
/// From FastLight Examples
/// @param chanceOfGlitter of 256
void LightAnimation::AddGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter)
  _leds[ random16(NUM_LEDS) ] += CRGB::White;
}
