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
    AnimFLStaticRandom(_modeChanged);
    break;
  case 10:
    AnimFLFirstLight(_modeChanged);
    break;
  case 11:
    AnimFLFire2012(_modeChanged);
    break;
  case 12:
    AnimFLCylon(_modeChanged);
    break;
  case 13:
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
