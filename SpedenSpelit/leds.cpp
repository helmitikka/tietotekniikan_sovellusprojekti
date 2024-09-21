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
    digitalWrite(ledPins[ledNumber], HIGH); 
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
// Turn on all LEDs
    for (int i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++)
    {
        digitalWrite(ledPins[i], HIGH);
    }
}


void show1()
{
// 1-15 binary numbers LED show

    //for()
    {
        // 1
        setLed(0);
        delay(1500);
        void clearAllLeds();
        delay(2000);
        // 2
        setLed(1);
        delay(1500);
        void clearAllLeds();
        delay(2000);
        // 3
        setLed(0);
        setLed(1);
        delay(1500);
        void clearAllLeds();
        delay(2000);
        // 4
        setLed(2);
        delay(1500);
        void clearAllLeds();
        delay(2000);
        // 5
        setLed(0);
        setLed(2);
        delay(1500);
        void clearAllLeds();
        delay(2000);
        // 6
        setLed(1);
        setLed(2);
        delay(1500);
        void clearAllLeds();
        delay(2000);
        // 7
        setLed(0);
        setLed(1);
        setLed(2);
        delay(1500);
        void clearAllLeds();
        delay(2000);
        // 8
        setLed(3);
        delay(1500);
        void clearAllLeds();
        delay(2000);
        // 9
        setLed(0);
        setLed(3);
        delay(1500);
        void clearAllLeds();
        delay(2000);
        // 10
        setLed(1);
        setLed(3);
        delay(1500);
        void clearAllLeds();
        delay(2000);
        // 11
        setLed(0);
        setLed(1);
        setLed(3);
        delay(1500);
        void clearAllLeds();
        delay(2000);
        // 12
        setLed(2);
        setLed(3);
        delay(1500);
        void clearAllLeds();
        delay(2000);
        // 13
        setLed(0);
        setLed(2);
        setLed(3);
        delay(1500);
        void clearAllLeds();
        delay(2000);
        // 14
        setLed(1);
        setLed(2);
        setLed(3);
        delay(1500);
        void clearAllLeds();
        delay(2000);
        // 15
        setLed(0);
        setLed(1);
        setLed(2);
        setLed(3);
        delay(1500);
        void clearAllLeds();
        delay(2000);
    
    }

}

void show2(int rounds)
{
// see requirements for this function from leds.h  
}