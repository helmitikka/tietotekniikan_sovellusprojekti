#include "leds.h"

const int ledPins[] = {2,3,4,5}; // Pins for LEDs (A2-A5)

void initializeLeds()
{
    // initialized all LEDs in ledPins:
    for (int i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++)
    {
        pinMode(ledPins[i], OUTPUT);
    }
}

void setLed(byte ledNumber)
{
    // Turns on a LED
    digitalWrite(ledNumber, HIGH); 
}

void clearAllLeds()
{
    // Turn off all LEDs
    for (int i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++)
    {
        digitalWrite(ledPins[i], LOW);
    } 
}

void setAllLeds()
{
// see requirements for this function from leds.h
}


void show1()
{
// see requirements for this function from leds.h
}

void show2(int rounds)
{
// see requirements for this function from leds.h  
}