// FastLED library Neopixel is an alternative
#include <Arduino.h>
#include <FastLED.h>
#include "LightAnimation.h"

/// Construct a new Light Animation object.
LightAnimation::LightAnimation()
{
  pinMode(LED_PIN, OUTPUT);
  
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(_leds, NUM_LEDS);
}

/// Destroy the LightAnimation object.
LightAnimation::~LightAnimation()
{
}

/// Changes to a new Animation.
/// @param mode number of the new animation 
LightAnimation::ChangeAnimation(int mode)
{
  _mode = mode;

  // flag that mode has changed for initializations
  _modeChanged = true;
}

/// Changes to next Animation.
LightAnimation::ChangeNextAnimation()
{
  _mode++;

  // if we reached the total number of animations return to fisrt one
  if (_mode > MAX_MODES)
    _mode = 1;

  // flag that mode has changed for initializations
  _modeChanged = true;
}

/// Changes speed of Animations.
/// @param speed Speed of the animation 100 is normal
LightAnimation::ChangeSpeed(int speed)
{
  _speed = speed;
}

/// Changes Brightness.
/// @param brightnes
LightAnimation::ChangeBrightness(int brightnes)
{
  /// Not implemented
}

LightAnimation::Update()
{
  switch (_mode)
  {
    case 1:
      AnimWave(_modeChanged);
      break;
    case 2:
      AnimHeartBeat(_modeChanged);
      break; 
    case 3:
      AnimArianna(_modeChanged);
      break;
    case 4:
      AnimKnight(_modeChanged);
      break;
    case 5:
      AnimAlternating(_modeChanged);
      break;
    case 6:
      AnimDali(_modeChanged);
      break;
    case 7:
      AnimGlitter(_modeChanged);  
      break;
    case 8:
      AnimRainDrops(_modeChanged);  
      break;
    case 9:
      AnimLightings(_modeChanged);
      break;
    case 10:
      AnimFLStaticRandom(_modeChanged);
      break;
    case 11:
      AnimFLFirstLight(_modeChanged);
      break;
    case 12:
      AnimFLFire2012(_modeChanged);
      break;
    case 13:
      AnimFLCylon(_modeChanged);
      break;
    case 14:
      AnimFLJuggle(_modeChanged);
      break;
  }

  // Control of _movingled if reaches any of both ends
  // if reaches the end or begin, begin again
  if (_movingLed >= NUM_LEDS )
    _movingLed = 0;

  if (_movingLed <= -1 )
    _movingLed = NUM_LEDS -1;

  // return to mode not changed
  _modeChanged = false;

  // Show leds
  FastLED.show();
}
