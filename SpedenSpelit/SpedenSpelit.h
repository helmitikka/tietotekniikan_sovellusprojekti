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
  Reads the high score from EEPROM memory address defined in variable highScoreMemoryAddress to variable highScore.
  If not found, creates a new record to EEPROM.

  Note: The value in address defined in highScoreMemoryAddress should be int 200.
  This is used as a check byte to make sure the memory address contains our high score information.
  Actual high score will be read from memory address highScoreMemoryAddress + 1.
*/
void initializeHighScore(void);

/*
  Writes the high score to EEPROM memory address defined in variable highScoreMemoryAddress.
  
  Note: The address in highScoreMemoryAddress will be used as a check byte, and the actual score will be written to address highScoreMemoryAddress + 1.

  Parameters:
  int score (Example value 22)
*/
void writeHighScore(int);

/*
  Generates a new random number, adds it to numberList, and increments missedPresses
*/
void generateNewRandomNumber(void);


#endif