#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile int buttonNumber = -1;           // Which button was pressed by the player 0,1,2,3
volatile bool newTimerInterrupt = false;  // Generates a new random number when True
int randomNumber;                         // Random number: 0,1,2,3
volatile int currentScore = 0;            // Current score. Also equals to total number of correct presses
volatile bool gameRunning = false;
volatile int highScore;

int numberList[100];  // List of generated random numbers 0,1,2,3. This will be compared to when the user presses a button

void setup()
{
  initializeLeds();
  initializeDisplay();
  initButtonsAndButtonInterrupts();
}

void loop()
{
  if(buttonNumber>=0 && buttonNumber < 4)
  {
     // start the game if buttonNumber == 4
     // check the game if 0<=buttonNumber<4
     checkGame(buttonNumber);
  }

  if(newTimerInterrupt == true)
  {
     // new random number must be generated
     // and corresponding led must be activated
     // add random number to number list for comparing
     randomNumber = random(0, 4); // 0,1,2,3
     setLed(randomNumber);
     numberList[currentScore] = randomNumber;
     newTimerInterrupt = false;
  }
}

void initializeTimer(void)
{
  TCCR1A = 0; // Timers to 0
  TCCR1B = 0;
  TCNT1 = 0;

  OCR1A = 15624; // Timer interrupts set to 1 sec intervals

  TCCR1B |= (1 << WGM12); // CTC (Clear timer on Compare Match) enabled
  TCCR1B |= (1 << CS12) | (1 << CS10); // Prescaler to 1024

  TIMSK1 |= (1 << OCIE1A); // Timer1 interrupts are now enabled
}
ISR(TIMER1_COMPA_vect) // This is triggered on every Timer interrupt
{
  newTimerInterrupt = true; // generates new number in loop  
}


void checkGame(byte nbrOfButtonPush)
{
	// see requirements for the function from SpedenSpelit.h
  if(nbrOfButtonPush == numberList[currentScore])
  {
    // User pressed correctly
    currentScore++;
    showNumber(currentScore);

    buttonNumber = -1;
    clearAllLeds();
  }
  else
  {
    endGame();
  }
}

void endGame()
{
  if(currentScore > highScore)
  {
    highScore = currentScore;
  }
}

void initializeGame()
{
	

}

void startTheGame()
{
   // see requirements for the function from SpedenSpelit.h

   currentScore = 0;
   gameRunning = true;
   newTimerInterrupt = true;
   buttonNumber = -1;
}

