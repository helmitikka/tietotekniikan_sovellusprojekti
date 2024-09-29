#ifndef DISPLAY_H
#define DISPLAY_H
#include <Arduino.h>

/* 
    Initializes the 7 segment displays ready for use
*/
void initializeDisplay(void);

/* 
    Shows the given number on two 7 segment displays
*/
void showNumber(int num);

void shutDownDisplay(void);

void enableDisplay(void);

#endif
