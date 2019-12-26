#include <Arduino.h>
#include "LightAnimation.h"

/// we move a sinus wave and iterate through different colours
/// we try to put one period in the whole led strip
/// @param init indicates that we can make some sort of initialization
void LightAnimation::AnimHeartBeat(bool init = false)

{ 
    static int t     = 0; // current "time"

    int T = NUM_LEDS;
    
    // put color and value of first led
    _leds[0] = CHSV(_hue, 255, sin8 ( t * 255 / T ) / 2 + 32);

    // Copy all the leds
    for (int i = 1; i < NUM_LEDS; i++)
      _leds[i] = _leds[0];
      
    // increase time
    t++;

    // if the end of the wave Period start a new wave again and change color
    if (t == T)
    {
        t = 0;
        _hue++;
    }

    // delay to next
    delay ( 50 * _speed / 100 );
}
