#include <Arduino.h>
#include "LightAnimation.h"

// Animation glitters
// elects randomly a start led, color and direction
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
