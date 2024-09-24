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

volatile bool highScoreShowAllowed = true;  // after 5 seconds of inactivity, show high score
volatile bool timerIncreaseAllowed = false; // after 10 timer interrupts, decreace the time between presses

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
    newTimerInterrupt = false;
    // new random number must be generated
    // and corresponding led must be activated
    // add random number to number list for comparing
    generateNewRandomNumber();
    setLed(randomNumber);
    delay(100);
    clearAllLeds();
     
  }
  
  if(missedPresses > 4)
  {
    Serial.println("Too many missed presses");
    endGame();
  }

  if(gameRunning)
  {
    if(buttonNumber>=0 && buttonNumber < 4)
    {
      Serial.print("Pressed button: ");
      Serial.println(buttonNumber);
      // check the game if 0<=buttonNumber<4
      checkGame(buttonNumber);
    }
    if(numberOfTimerInterrupts % 10 == 0 && timerIncreaseAllowed)
    {
      timerIncreaseAllowed = false; // needs to be set so this happens only once per 10
      // Speeds up the timer by 10% every 10th interrupt
      timerInterruptSpeed = timerInterruptSpeed * 0.9;
      OCR1A = timerInterruptSpeed;
    }
    if(numberOfTimerInterrupts % 10 == 1)
    {
      // We are at 11th interrupt -> allow to increase again at the next full 10
      timerIncreaseAllowed = true;
    }
  }

  else // Game not running
  {
    if(buttonNumber == 3)
    {
      startTheGame();
    }
    // After 5 timer interrupts, show high score
    if(numberOfTimerInterrupts == 5 && highScoreShowAllowed)
    {
      highScoreShowAllowed = false;
      Serial.print("Now showing high score: ");
      Serial.println(highScore);
      showNumber(highScore);
    }
  }

  buttonNumber = -1;
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
    Serial.print("Pressed correctly. Score is now: ");
    Serial.println(currentScore);
    showNumber(currentScore);

    buttonNumber = -1;
    clearAllLeds();
  }
  else
  {
    Serial.println("Pressed wrongly");
    endGame();
  }
}

void endGame()
{
  Serial.println("GAME OVER");
  gameRunning = false;
  missedPresses = 0;
  newTimerInterrupt = false; // No more new random numbers generated
  clearAllLeds();

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
  numberOfTimerInterrupts = 0;
  highScoreShowAllowed = true;
}

void initializeGame()
{
	

}

void startTheGame()
{
   // see requirements for the function from SpedenSpelit.h
  Serial.println("Starting a new game");
  currentScore = 0;
  showNumber(currentScore);
  gameRunning = true;
  buttonNumber = -1;
  missedPresses = 0;
  newTimerInterrupt = true;
  numberOfTimerInterrupts = 0;
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
    missedPresses++;
    numberList[currentScore + missedPresses] = randomNumber;    

    Serial.print("New random number: ");
    Serial.println(randomNumber);
}