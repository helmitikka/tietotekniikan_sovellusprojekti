#include "buttons.h"

extern volatile int buttonNumber;

const int buttonPins[] = {8, 9, 10, 11};

void initButtonsAndButtonInterrupts(void)
{
    for (int i = 0; i < sizeof(buttonPins) / sizeof(buttonPins[0]); i++)
    {
      // Aktivoi napit käytettäviksi
      pinMode(buttonPins[i], INPUT_PULLUP);
    }
}

ISR(PCINT0_vect)
{
  // Saatu interrupt, tarkistetaan mistä pinnistä
  for (int i = 0; i < sizeof(buttonPins) / sizeof(buttonPins[0]); i++)
  {
    if (digitalRead(buttonPins[i]) == LOW)
    {
      buttonNumber = i;
    }
  }
}