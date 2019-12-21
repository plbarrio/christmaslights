#include <Arduino.h>
#include "LightAnimation.h"

void LightAnimation::AnimArianna(bool init = false)
{ //Arianna

  static int lastLED   = NUM_LEDS; // last led

  if (init){
    _movingLed = 0;
    lastLED   = NUM_LEDS;
  }
  
  // Put a color if is the first led of an iteration or fade it
  if (_movingLed == 0)
  {
    _leds[0] = CHSV(random(256), 255, 255);
    lastLED--;
  }
  else
    _leds[0].fadeToBlackBy(192);

  // move every led value to next one
  for (int i = lastLED; i > 0; i--)
    _leds[i] = _leds[i - 1];
  
  // moving led is the next one
  _movingLed++;

  // if reaches the end begin again
  if (_movingLed == lastLED )
    _movingLed = 0;

  // if the last led is the first one
  // begin again
  if (lastLED == 1)
    lastLED=NUM_LEDS;

  delay ( 50 * _speed / 100 );
}

