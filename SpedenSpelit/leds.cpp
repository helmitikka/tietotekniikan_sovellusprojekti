#include "leds.h"

const int ledPins[] = {2,3,4,5}; // Pins for LEDs (D2,D3,D4,D5)

void initializeLeds()
{ 
    Serial.println("Ititializing leds");
    for (int i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++)
    {
        Serial.print("LED pin: ");
        Serial.println(ledPins[i]);
        pinMode(ledPins[i], OUTPUT);
    }
    setAllLeds();
    delay(100);
    clearAllLeds();
}

void setLed(byte ledNumber)
{
    digitalWrite(ledPins[ledNumber], HIGH); 
}

void clearAllLeds()
{
    for (int i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++)
    {
        digitalWrite(ledPins[i], LOW);
    } 
}

void setAllLeds()
{
    for (int i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++)
    {
        digitalWrite(ledPins[i], HIGH);
    }
}

void show1()
{
    while(gameRunning == false && currentScore == 0)
    {
        // 1
        setLed(3);
        delay(1500);
        clearAllLeds();
        delay(2000);
        // 2
        setLed(2);
        delay(1500);
        clearAllLeds();
        delay(2000);
        // 3
        setLed(3);
        setLed(2);
        delay(1500);
        clearAllLeds();
        delay(2000);
        // 4
        setLed(1);
        delay(1500);
        clearAllLeds();
        delay(2000);
        // 5
        setLed(3);
        setLed(1);
        delay(1500);
        clearAllLeds();
        delay(2000);
        // 6
        setLed(2);
        setLed(1);
        delay(1500);
        clearAllLeds();
        delay(2000);
        // 7
        setLed(3);
        setLed(2);
        setLed(1);
        delay(1500);
        clearAllLeds();
        delay(2000);
        // 8
        setLed(0);
        delay(1500);
        clearAllLeds();
        delay(2000);
        // 9
        setLed(0);
        setLed(3);
        delay(1500);
        clearAllLeds();
        delay(2000);
        // 10
        setLed(2);
        setLed(0);
        delay(1500);
        clearAllLeds();
        delay(2000);
        // 11
        setLed(0);
        setLed(2);
        setLed(3);
        delay(1500);
        clearAllLeds();
        delay(2000);
        // 12
        setLed(1);
        setLed(0);
        delay(1500);
        clearAllLeds();
        delay(2000);
        // 13
        setLed(0);
        setLed(1);
        setLed(3);
        delay(1500);
        clearAllLeds();
        delay(2000);
        // 14
        setLed(1);
        setLed(2);
        setLed(0);
        delay(1500);
        clearAllLeds();
        delay(2000);
        // 15
        setLed(0);
        setLed(1);
        setLed(2);
        setLed(3);
        delay(1500);
        clearAllLeds();
        delay(2000);
    
    }

}

void show2(int rounds)
{
// see requirements for this function from leds.h
    while(gameRunning == false && currentScore > 0)
    {
        rounds = 10;
        //for()
    }
}