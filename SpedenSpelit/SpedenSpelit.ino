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
int missedPresses;                        // Ends the game if reaches 5

volatile int numberOfTimerInterrupts = 0; // Increased on every timer interrupt. Used to decrease timer interrupt interval
volatile int timerInterruptSpeed = 15624; // Timer interrupt interval (15624 = 1Hz)

int numberList[100];  // List of generated random numbers 0,1,2,3. This will be compared to when the user presses a button

void setup()
{
  initializeLeds();
  initializeDisplay();
  initButtonsAndButtonInterrupts();
}

void loop()
{
  if(missedPresses > 4)
  {
    endGame();
  }

  if(buttonNumber>=0 && buttonNumber < 4)
  {
     // start the game if buttonNumber == 4
     if(buttonNumber == 4 && gameRunning == false)
     {
      startTheGame();
     }

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
     missedPresses++;
     newTimerInterrupt = false;
  }
}

void initializeTimer(void)
{
  TCCR1A = 0; // Timers to 0
  TCCR1B = 0;
  TCNT1 = 0;

  OCR1A = timerInterruptSpeed; // Timer interrupts set to 1 sec intervals

  TCCR1B |= (1 << WGM12); // CTC (Clear timer on Compare Match) enabled
  TCCR1B |= (1 << CS12) | (1 << CS10); // Prescaler to 1024

  TIMSK1 |= (1 << OCIE1A); // Timer1 interrupts are now enabled
}
ISR(TIMER1_COMPA_vect) // This is triggered on every Timer interrupt
{
  if(gameRunning)
  {
    numberOfTimerInterrupts++;
    newTimerInterrupt = true; // generates new random number in loop

    if(numberOfTimerInterrupts % 10 == 0)
    {
      // Speeds up the timer by 10% every 10th interrupt
      timerInterruptSpeed = timerInterruptSpeed * 0.9;
      OCR1A = timerInterruptSpeed;
    }
  }
  else // Game not running
  {
    // After 5 interrupts, show high score
    if(numberOfTimerInterrupts == 5)
    {
      showNumber(highScore);
    }
  }
}


void checkGame(byte nbrOfButtonPush)
{
  if(nbrOfButtonPush == numberList[currentScore])
  {
    // User pressed correctly
    missedPresses--;
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
  gameRunning = false;
  newTimerInterrupt = false; // No more new random numbers generated

  if(currentScore > highScore)
  {
    highScore = currentScore;
  }
  /*
    Reset the timer interrupt amount here
    We can then easily compare for example if the amount is 5
    -> 5 seconds has passed -> show high score
  */
  numberOfTimerInterrupts = 0;
}

void initializeGame()
{
	

}

void startTheGame()
{
   // see requirements for the function from SpedenSpelit.h

   currentScore = 0;
   gameRunning = true;
   buttonNumber = -1;
   missedPresses = 0;
   newTimerInterrupt = true;
   numberOfTimerInterrupts = 0;
}

