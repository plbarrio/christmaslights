#include <Arduino.h>
#include "LightAnimation.h"

/// we move a sinus wave and iterate through different colours
/// we try to put one period in the whole led strip
/// @param init indicates that we can make some sort of initialization
void LightAnimation::AnimHeartBeat(bool init = false)

{ // waves
    static int color = 0; // color of the wave
    static int t     = 0; // current "time"

    int T = NUM_LEDS;
    
    // put color and value of first led
    _leds[0] = CHSV(color, 255, sin8 ( t * 255 / T ) / 2 + 32);

    // Copy all the leds
    for (int i = 1; i < NUM_LEDS; i++)
      _leds[i] = _leds[0];
      
    // increase time
    t++;

    // if the end of the wave Period start a new wave again and change color
    if (t == T)
    {
        t = 0;
        color++;
        
        // if colors end begin again
        if (color > 255)
            color = 0;
    }

    // delay to next
    delay ( 50 * _speed / 100 );
}
