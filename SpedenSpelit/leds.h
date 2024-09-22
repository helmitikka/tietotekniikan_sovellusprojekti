#ifndef LEDS_H
#define LEDS_H
#include <arduino.h>

extern volatile bool gameRunning;
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

/*
  show2(int) subroutine shows leds 0,1,2,3,0,1,2,3,.... with increasing
  changing rate. And when top change speed has been reached

    Parameters:
  
  int rounds: This parameter determines how many times 0,1,2,3 sequence
              is shown. 
*/
void show2(int);

#endif