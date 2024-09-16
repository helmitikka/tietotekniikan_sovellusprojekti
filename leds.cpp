#include "leds.h"

const int ledPins[] = {A2, A3, A4, A5}; // Pins for LEDs

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
    if (ledNumber >= 0 && ledNumber < sizeof(ledPins) / sizeof(ledPins[0]))
    {
        digitalWrite(ledPins[ledNumber], HIGH); 
    }
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