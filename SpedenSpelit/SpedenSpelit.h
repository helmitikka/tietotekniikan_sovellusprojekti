#ifndef SPEDENSPELIT_H
#define SPEDENSPELIT_H
#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/*
  This function zeroes the timer and sets it up to give interruptions periodically
*/
void initializeTimer(void);

ISR(TIMER1_COMPA_vect);

/*
  Sets game variables to their initial values for a new game
*/
void initializeGame(void);

/*
  checkGame() subroutine is used to check the status
  of the Game after each player button press.
  
  If the latest player button press is wrong, the game stops
  and if the latest press was right, game display is incremented
  by 1.
  
  Parameters:
  byte lastButtonPress (Example value 1)
  
*/
void checkGame(byte);

/*
  Starts a new game
*/
void startTheGame(void);

/*
  Ends the game when the player pressed wrongly, and resets the game state
*/
void endGame(void);

/*
  Reads the high score from EEPROM memory to variable highScore. If not found, creates a new record to EEPROM.
*/
void initializeHighScore(void);

/*
  Writes the high score to EEPROM

  Parameters:
  int score (Example value 22)
*/
void writeHighScore(int);

/*
  Generates a new random number, adds it to numberList, and increments missedPresses
*/
void generateNewRandomNumber(void);


#endif