#include <Arduino.h>
#include "LightAnimation.h"

/// RainDrops
/// elects randomly a start led, and goes down due gravity
///
/// @param init indicates that we can make some sort of initialization
void LightAnimation::AnimRainDrops(bool init = false)
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
