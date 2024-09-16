#include "buttons.h"

extern volatile int buttonNumber;

void initButtonsAndButtonInterrupts(void)
{
  // See requirements for this function from buttons.h
    // Initialize button pins
    for (int i = firstPin; i <= lastPin; i++)
    {
      pinMode(i, INPUT_PULLUP); // Set pins 2,3,4,5,6 as INPUT_PULLUP
    }
}

ISR(PCINT2_vect) {
   /*
     Here you implement logic for handling
	 interrupts from 2,3,4,5 pins for Game push buttons
	 and for pin 6 for start Game push button.
   */
    for (int i = firstPin; i <= lastPin; i++)
    {
      if (digitalRead(i) == LOW)
      {
        buttonNumber = i;
        return;
      }
    }
}