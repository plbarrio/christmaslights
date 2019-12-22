#include <Arduino.h>
#include "LightAnimation.h"

/// we move a sinus wave and iterate through different colours
/// we try to put one period in the whole led strip
///
/// @param init indicates that we can make some sort of initialization
void LightAnimation::AnimWave(bool init = false)

{ // waves
    static int color = 0; // color of the wave
    static int t     = 0; // current "time"

    int T = NUM_LEDS;

    // copy each Led with previous one
    for (int i = 0; i < NUM_LEDS - 1; i++)
        _leds[i] = _leds[i + 1];
    
    // put color and value of last led
    _leds[NUM_LEDS - 1] = CHSV(color, 255, sin8 ( t * 255 / T ) / 2 + 120);
    
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