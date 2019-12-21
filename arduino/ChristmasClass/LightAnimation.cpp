// FastLED library Meopixel is an alternative
#include <Arduino.h>
#include <FastLED.h>
#include "LightAnimation.h"

// Constructor
LightAnimation::LightAnimation()
{
  pinMode(LED_PIN, OUTPUT);
  
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(_leds, NUM_LEDS);
}

// Destructor
LightAnimation::~LightAnimation()
{
}

LightAnimation::ChangeAnimation(int mode)
{
  _mode = mode;

  // flag that mode has changed for initializations
  _modeChanged = true;
}

LightAnimation::ChangeNextAnimation()
{
  _mode++;

  // if we reached the total of animation return to fisrt one
  if (_mode > MAX_MODES)
    _mode = 1;

  // flag that mode has changed for initializations
  _modeChanged = true;
}

LightAnimation::ChangeSpeed(int speed)
{
  _speed = speed;
}

LightAnimation::ChangeBrightness(int brightnes)
{
}

LightAnimation::Update()
{
  switch (_mode)
  {
  case 1:
    AnimWave(_modeChanged);
    break;
  case 2:
    AnimArianna(_modeChanged);
    break;
  case 3:
    AnimKnight(_modeChanged);
    break;
  case 4:
    AnimAlternating(_modeChanged);
    break;
    
  case 5:
    AnimFLStaticRandom(_modeChanged);
    break;
  case 6:
    AnimFLFirstLight(_modeChanged);
    break;
  case 7:
    AnimFLFire2012(_modeChanged);
    break;
  case 8:
    AnimCylon(_modeChanged);
    break;
  case 9:
    AnimFLJuggle(_modeChanged);
    break;
  }

  // return to mode not changed
  _modeChanged = false;

  // Show leds
  FastLED.show();
}
