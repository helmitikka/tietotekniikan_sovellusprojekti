#include "buttons.h"

const int buttonPins[] = {8, 9, 10, 11};

void initButtonsAndButtonInterrupts(void) // Initializes all buttons
{
  PCICR |= (1 << PCIE0);  // Enable pin change interrupt for PCINT0
  PCMSK0 |= (1 << PCINT0) | (1 << PCINT1) | (1 << PCINT2) | (1 << PCINT3);  // Enable interrupts for pins 8, 9, 10, 11

  Serial.println("Ititializing buttons");
    for (int i = 0; i < sizeof(buttonPins) / sizeof(buttonPins[0]); i++)
    {
      Serial.print("Button pin: ");
      Serial.println(buttonPins[i]);
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