#include <Arduino.h>
#include "LightAnimation.h"

/// Alternating between odds an evens
///
/// @param init indicates that we can make some sort of initialization 
void LightAnimation::AnimAlternating(bool init = false)
{
  // counter we change every 50 isf _speed= 100 -> 1 second
  static int counter = 0;
  static bool pair = false ; // current moving led
  
  if (init){
    // everyled off
    for (int i = 0; i < NUM_LEDS; i++)
    _leds[i] = CRGB::Black;
    counter = 0;
  }

  // put first led to a random color
  if (counter == 0)
  {
    // move every led value to next one
    for (int i = NUM_LEDS - 1; i > 0; i--)
      _leds[i] = _leds[i - 1];
    
    // Put a random color if we are on odds
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