// Class that controls light Scheme.

#ifndef LIGHTANIMATION_H
#define LIGHTANIMATION_H

#include <Arduino.h>
#include <FastLED.h>

// Unfortunately in arduino is not safe to reserve memory dynamically.
// Put here the number of LEDs you have.
#ifndef NUM_LEDS
#define NUM_LEDS 50
#endif

// define the led strip output number.
#ifndef LED_PIN
#define LED_PIN 4
#endif

// define here your type of the strip.
#ifndef LED_TYPE
#define LED_TYPE WS2811
#endif

// define here the order of the strip.
#ifndef COLOR_ORDER
#define COLOR_ORDER RGB
#endif

/// Class that controls light Scheme.
class LightAnimation
{
  public:
    /// Constructor and destructor
    LightAnimation();

    /// Destructor
    ~LightAnimation();

    /// Update the ledstrip
    /// 
    /// To be called from Loop()
    /// it will iterate and update the led strip status
    Update();

    /// Change the animation
    ///
    /// @param mode mode to animate  
    ChangeAnimation(int mode);

    /// Change to next animation
    ChangeNextAnimation();

    /// Change the speed 100 is the normal
    /// 
    /// @param speed Speed of the led strip update
    ChangeSpeed (int speed);

    /// Change the general brightness
    /// @param brightness amount of brightness
    ChangeBrightness (int brightness);
            
    private:

    /// Led array
    CRGB _leds[NUM_LEDS];

    /// Current Animation
    int  _mode=0;

    /// Total number of animations, it is used to return to the first animation
    /// Once reached the end.
    int const MAX_MODES = 14;

    /// Indicates that the mode has just changed.
    bool _modeChanged = true;
  
    /// Actual speed 100 is normal.
    int _speed = 100;

    /// Current color 0-255 if 255 and make _hue++ it automaticly goes to 0.
    uint8_t _hue  = 0;

    /// number of the current led in moving light animations.
    int _movingLed = 0;

    /// direction of the animation in up/down animations.
    bool _sense;

    /// palette
    CRGBPalette16 _pal;

    // Helpers
    void AddGlitter( fract8 chanceOfGlitter);

    // Different animations
    void AnimWave          (bool init = false);
    void AnimHeartBeat     (bool init = false);
    void AnimArianna       (bool init = false);
    void AnimKnight        (bool init = false); 
    void AnimAlternating   (bool init = false); 
    void AnimDali          (bool init = false);
    void AnimGlitter       (bool init = false);
    void AnimRainDrops     (bool init = false);
    void AnimLightings     (bool init = false);

    // FastLight examples
    void AnimFLStaticRandom(bool init = false);
    void AnimFLFirstLight  (bool init = false);
    void AnimFLFire2012    (bool init = false);
    void AnimFLCylon       (bool init = false);
    void AnimFLJuggle      (bool init = false);
};
#endif  LIGHTSCHEME_H
