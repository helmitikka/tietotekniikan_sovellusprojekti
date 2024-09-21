#include "display.h"

int latchPin = 7;  // to RCLK
int clockPin = 12; // to SRCLK
int dataPin = 13;  // to SER

byte numbers[] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111  // 9
};

void initializeDisplay(void)
{
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
}

void showNumber(int num) // Shows the given number on two 7 segment displays
{
  int tens = num / 10;   // Get the tens digit
  int ones = num % 10;   // Get the ones digit

  digitalWrite(latchPin, LOW); // Latch down

  // First 8 bits goes through 1st registers Qh' -> 2nd registers SER
  shiftOut(dataPin, clockPin, MSBFIRST, numbers[ones]);

  // Second 8 bits stays on the 1st register
  shiftOut(dataPin, clockPin, MSBFIRST, numbers[tens]);

  digitalWrite(latchPin, HIGH); // Latch up -> Numbers shown
}