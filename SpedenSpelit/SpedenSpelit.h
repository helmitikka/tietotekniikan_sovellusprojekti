#ifndef SPEDENSPELIT_H
#define SPEDENSPELIT_H
#include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/*
  This function zeroes the timer and sets it up to give interruptions periodically
*/
void initializeTimer(void);

ISR(TIMER1_COMPA_vect);

/*
  initializeGame() subroutine is used to initialize all variables
  needed to store random numbers and player button push data.
  This function is called from startTheGame() function.
  
*/
void initializeGame(void);

/*
  checkGame() subroutine is used to check the status
  of the Game after each player button press.
  
  If the latest player button press is wrong, the game stops
  and if the latest press was right, game display is incremented
  by 1.
  
  Parameters
  byte lastButtonPress of the player 0 or 1 or 2 or 3
  
*/
void checkGame(byte);


/*
  startTheGame() subroutine calls InitializeGame()
  function and enables Timer1 interrupts to start
  the Game.
*/
void startTheGame(void);

/*
  Ends the game when the player pressed wrongly
*/
void endGame(void);

#endif