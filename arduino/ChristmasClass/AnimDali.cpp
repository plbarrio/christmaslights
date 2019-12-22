#include <Arduino.h>
#include "LightAnimation.h"

/// Animation as painter brushes
/// elects randomly a start led, color and direction
///
/// @param init indicates that we can make some sort of initialization 
void LightAnimation::AnimDali(bool init = false)
{ 
  // First fade all
  fadeToBlackBy( _leds, NUM_LEDS, 32);

  static uint8_t hue  = 0;
  static int  length  = 0;
  
  // if we are not painting start a new
  if (length == 0 )
  {
    _movingLed = random(NUM_LEDS);
    _sense     = !_sense;
    hue        = random(256);
    length     = random(NUM_LEDS);
  }
  else 
  {
    // If we have not ended painting paint it
    _leds[_movingLed] = CHSV(hue, 255, 255);

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
