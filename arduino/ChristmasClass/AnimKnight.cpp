#include <Arduino.h>
#include "LightAnimation.h"

// knight rider animation
void LightAnimation::AnimKnight( bool init = false)

{
  // Sense left to right or right to left
  
  
  if (init)
    _movingLed = 0;

  if (_sense)
  {
    if (_movingLed == 0)
      _leds[0] = CRGB::Red;
    else
      _leds[0].fadeToBlackBy(128);

    for (int i = NUM_LEDS - 1; i > 0; i--)
      _leds[i] = _leds[i - 1];
  }
  else
  {
    if (_movingLed == 0)
      _leds[NUM_LEDS - 1] = CRGB::Red;
    else
      _leds[NUM_LEDS - 1].fadeToBlackBy(128);

    for (int i = 0; i < NUM_LEDS - 1; i++)
      _leds[i] = _leds[i + 1];
  }

  _movingLed ++;

  if (_movingLed == NUM_LEDS - 1 )
  {
    _movingLed = 0;
    _sense = !_sense;
  }

  delay( 50 * _speed / 100 );
}
