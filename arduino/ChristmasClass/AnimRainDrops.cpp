#include <Arduino.h>
#include "LightAnimation.h"

/// RainDrops
/// elects randomly a start led, and goes down due gravity
///
/// @param init indicates that we can make some sort of initialization
void LightAnimation::AnimRainDrops(bool init = false)
{ 
  // First fade all
  fadeToBlackBy( _leds, NUM_LEDS, 64);

  addGlitter(20);

  // Copy every white led down
  for (int i =  1; i < NUM_LEDS; i++)
  {
        // copy if white
        if (_leds[i].r >=  1)
           _leds[ i - 1 ] = _leds[i];    
  }
     
  delay ( 50 * _speed / 100 );
}
