#include "buttons.h"

const int buttonPins[] = {8, 9, 10, 11};

void initButtonsAndButtonInterrupts(void) // Initializes all buttons
{
    for (int i = 0; i < sizeof(buttonPins) / sizeof(buttonPins[0]); i++)
    {
      pinMode(buttonPins[i], INPUT_PULLUP);
    }
}

ISR(PCINT0_vect) // got an interrupt
{
  for (int i = 0; i < sizeof(buttonPins) / sizeof(buttonPins[0]); i++)
  {
    if (digitalRead(buttonPins[i]) == LOW) // checks if any pins in buttonPins is LOW
    {
      buttonNumber = i; // buttonNumber will be 0-3
    }
  }
}