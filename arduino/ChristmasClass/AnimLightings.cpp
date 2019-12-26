#include <Arduino.h>
#include "LightAnimation.h"

/// Lightings
/// like glitter but with length
///
/// @param init indicates that we can make some sort of initialization
void LightAnimation::AnimLightings(bool init = false)
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
