#include <Arduino.h>
#include "LightAnimation.h"

// Animation as painter brushes
// elects randomly a start led, color and direction
void LightAnimation::AnimDali(bool init = false)
{ 
  // First fade all
  fadeToBlackBy( _leds, NUM_LEDS, 32);

  // counter we change every 50 isf _speed= 100 -> 1 second
  static int  counter = 0;
  static uint8_t hue  = 0;
  static int  length  = 0;
  
  if (counter == 0 )
  {
    _movingLed = random(NUM_LEDS);
    _sense     = !_sense;
    hue        = random(256);
    length     = random(NUM_LEDS);
    counter ++;
  }
  else 
  {
    if (length > 0)
    {
        _leds[_movingLed] = CHSV(hue, 255, 255);
        if (_sense)
            _movingLed++;
        else
            _movingLed--;
        length --;
    }
    else
    {
        counter =0;
    }
  }
  
  

  delay ( 50 * _speed / 100 );
}
