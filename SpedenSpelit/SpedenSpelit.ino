#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <EEPROM.h>

volatile int buttonNumber = -1;           // Which button was pressed by the player 0,1,2,3

volatile bool newTimerInterrupt = false;  // Generates a new random number when True
int randomNumber;                         // Random number: 0,1,2,3
int numberList[100];                      // List of generated random numbers 0,1,2,3. This will be compared to when the user presses a button

volatile int currentScore = 0;            // Current score. Also equals to total number of correct presses
volatile bool gameRunning = false;
int missedPresses = 0;                    // Ends the game if reaches 5

volatile int highScore;
int highScoreMemoryAddress = 0;           // EEPROM memory address where the high score is saved

volatile int numberOfTimerInterrupts = 0; // Increased on every timer interrupt. Used to decrease timer interrupt interval
volatile int timerInterruptSpeed = 15624; // Timer interrupt interval (15624 = 1Hz)

volatile bool energySaveAllowed = true;
volatile bool highScoreShowAllowed = true;  // after 5 seconds of inactivity, show high score
volatile bool timerIncreaseAllowed = false; // after 10 timer interrupts, decreace the time between presses

long ledBlinkStartTime = 0;
bool ledIsBlinking = false;

void setup()
{
  Serial.begin(9600); // Serial for testing purposes
  initButtonsAndButtonInterrupts();
  initializeTimer();
  initializeLeds();
  initializeHighScore();
  initializeDisplay();  
  interrupts();  
}

void loop()
{
  if(newTimerInterrupt == true)
  {
    clearAllLeds();
    newTimerInterrupt = false;
    generateNewRandomNumber();
    setLed(randomNumber);
  }
  
  if(missedPresses > 6)
  {
    endGame();
  }
  
  if(gameRunning)
  {
    if(buttonNumber>=0 && buttonNumber < 4)
    {
      checkGame(buttonNumber);  // check the game if 0<=buttonNumber<4
      buttonNumber = -1;
    }
    if(numberOfTimerInterrupts % 10 == 0 && numberOfTimerInterrupts > 9 && timerIncreaseAllowed)
    {
      timerIncreaseAllowed = false; // needs to be set so this happens only once per 10
      timerInterruptSpeed = timerInterruptSpeed * 0.9;  // Speeds up the timer by 10% every 10th interrupt
      OCR1A = timerInterruptSpeed;
    }
    if(numberOfTimerInterrupts % 10 == 1)
    {
      timerIncreaseAllowed = true;  // We are at 11th interrupt -> allow to increase again at the next full 10
    }
  }

  else // Game not running
  {
    if(buttonNumber == 3)
    {
      ledIsBlinking = false;
      startTheGame();
    }
    
    // After 5 timer interrupts, show high score
    if(numberOfTimerInterrupts == 5 && highScoreShowAllowed)
    {
      highScoreShowAllowed = false;
      showNumber(highScore);
    }
    while(numberOfTimerInterrupts == 300 && energySaveAllowed)
    {
      energySaveAllowed = false;
      ledIsBlinking = true;
      clearAllLeds();
      shutDownDisplay();
        while(ledIsBlinking)  // Blinks led when energy save is on
        {
          setLed(3);
          delay(100);
          clearAllLeds();
          delay(1000);
          if(buttonNumber > -1 && buttonNumber <= 2)  // Brings back highscore when any button is pressed
          {
            buttonNumber = -1;
            ledIsBlinking = false;
            energySaveAllowed = true;
            numberOfTimerInterrupts = 0;
            enableDisplay();
            showNumber(highScore);
          }
          if(buttonNumber == 3)
          {
            startTheGame;          
          }
        }
    }
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
  numberOfTimerInterrupts++;
  if(gameRunning)
  {
    newTimerInterrupt = true; // generates new random number in loop
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
  missedPresses = 0;
  numberOfTimerInterrupts = 0;
  newTimerInterrupt = false; // No more new random numbers generated
  timerInterruptSpeed = 15624;
  OCR1A = timerInterruptSpeed;

  if(currentScore > highScore)
  {
    highScore = currentScore;
    writeHighScore(highScore);
  }
  /*
    Reset the timer interrupt amount here
    We can then easily compare for example if the amount is 5
    -> 5 seconds has passed -> show high score
  */
  highScoreShowAllowed = true;
  energySaveAllowed = true;
  setAllLeds();
  delay(500);
  clearAllLeds();
}

void initializeGame()
{
  clearAllLeds();
  initializeTimer();
  gameRunning = true;
  buttonNumber = -1;
  missedPresses = 0;
  numberOfTimerInterrupts = 0;
  currentScore = 0;
  enableDisplay();
}

void startTheGame()
{
  initializeGame();
  showNumber(currentScore);
}

void initializeHighScore()
{
  // Sources: https://docs.arduino.cc/learn/built-in-libraries/eeprom/
  byte checkByte = EEPROM.read(highScoreMemoryAddress);
  if(checkByte == 200)
  {
    // Reads the highScore from memory address + 1
    highScore = EEPROM.read(highScoreMemoryAddress + 1);
  }
  else
  {
    highScore = 0;
    writeHighScore(0);
  }
}

void writeHighScore(int score)
{
  EEPROM.write(highScoreMemoryAddress, 200);
  EEPROM.write(highScoreMemoryAddress + 1, highScore);
}

void generateNewRandomNumber()
{
  randomNumber = random(0, 4); // 0,1,2,3
  numberList[currentScore + missedPresses] = randomNumber;
  missedPresses++;
}