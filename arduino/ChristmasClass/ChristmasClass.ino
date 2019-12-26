#include "LightAnimation.h"

// define a globall class G_Animation
LightAnimation G_Animation;

// pin where the button to change mode is connected
#define I_CHANGE_MODE 5

void setup() {
  // Serial for debugging
  Serial.begin(9600);
  Serial.print("start");

  // Define Change mode button input
  pinMode(I_CHANGE_MODE, INPUT_PULLUP);
  
  G_Animation.ChangeAnimation (1);
}

void loop() {
  // Change mode button state and last state to detect fall-Down
  int buttonState;
  static int LastButtonState;

  // if button is just pressed change to next animation
  buttonState = digitalRead(I_CHANGE_MODE);

  if ( buttonState == LOW && LastButtonState==HIGH)
    G_Animation.ChangeNextAnimation();

  LastButtonState = buttonState;
  
  // Refresh animation  
  G_Animation.Update();
  
}
