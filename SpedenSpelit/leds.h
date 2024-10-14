#ifndef LEDS_H
#define LEDS_H
#include <Arduino.h>

extern bool gameRunning;
extern volatile int currentScore;

/*
  Initializes all LEDs in ledPins
*/
void initializeLeds();

/*
  Turns on a LED
*/
void setLed(byte ledNumber);

/*
  Turns off all LEDs
*/
void clearAllLeds(void);

/*
  Turns on all LEDs
*/
void setAllLeds(void);

/*
  1-15 binary number show on LEDs
*/
void show1(void);

#endif