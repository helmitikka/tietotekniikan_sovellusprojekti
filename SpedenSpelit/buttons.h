#ifndef BUTTONS_H
#define BUTTONS_H
#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

extern volatile int buttonNumber;

/* 
  Initializes all buttons and Pin Change Interrupt service
*/
void initButtonsAndButtonInterrupts(void);

/* 
  Pin Change Interrupt service
*/
ISR(PCINT0_vect);
#endif;