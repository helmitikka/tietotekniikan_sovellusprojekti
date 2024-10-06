#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <EEPROM.h>

volatile int buttonNumber = -1;           // Which button was pressed by the player | Can get values: 0,1,2,3

volatile bool newTimerInterrupt = false;  // When True, a new random number will be generated for the game
int randomNumber;                         // Random number | Can get values: 0,1,2,3
int numberList[100];                      // List of generated random numbers in current game. | Example values: [0,1,2,3]

int currentScore = 0;            // Current score. Also equals to total number of correct presses
volatile bool gameRunning = false;
int missedPressesAllowed = 5;             // Ends the game if this amount of missed presses is reached
int missedPresses = 0;                    // Running amount of missed presses by the player

int highScore;
int highScoreMemoryAddress = 0;           // EEPROM memory address where the high score is saved

volatile int countOfTimerInterrupts = 0;  // Increased on every timer interrupt. Used as running count of how long the game has been running / idling
int timerInterruptSpeed = 15624; // Timer interrupt interval (15624 = 1 Hz)

bool energySaveAllowed = true;     // Allowed to enter Energy saving mode
int energySaveAfterSeconds = 300;

bool highScoreShowAllowed = true;  // Allowed to show High Scores while the game is idling
int highScoreShowAfterSeconds = 5;

bool timerIncreaseAllowed = false; // After every 10 timer interrupts, decrease the time between presses (makes the game harder)


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
    clearAllLeds();    
    generateNewRandomNumber();
    setLed(randomNumber);
  }
  
  if(missedPresses > missedPressesAllowed)
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
      buttonNumber = -1;
    }

    if(countOfTimerInterrupts % 10 == 0 && countOfTimerInterrupts > 9 && timerIncreaseAllowed)
    {
      timerIncreaseAllowed = false; // needs to be set so this happens only once per 10
      // Speeds up the timer by 10% every 10th interrupt
      timerInterruptSpeed = timerInterruptSpeed * 0.9;
      OCR1A = timerInterruptSpeed;
    }
    
    if(countOfTimerInterrupts % 10 == 1)
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

    if(countOfTimerInterrupts == highScoreShowAfterSeconds && highScoreShowAllowed) // Show High Score
    {
      highScoreShowAllowed = false;
      Serial.print("Now showing high score: ");
      Serial.println(highScore);
      showNumber(highScore);
    }

    if(countOfTimerInterrupts == energySaveAfterSeconds && energySaveAllowed) // Show Energy save mode
    {
      energySaveAllowed = false;
      clearAllLeds();
      shutDownDisplay();
      Serial.println("mennään virransäästö");
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
  countOfTimerInterrupts++;
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
  countOfTimerInterrupts = 0;
  newTimerInterrupt = false; // No more new random numbers generated
  timerInterruptSpeed = 15624;
  OCR1A = timerInterruptSpeed;
  highScoreShowAllowed = true;
  energySaveAllowed = true;

  if(currentScore > highScore)
  {
    highScore = currentScore;
    writeHighScore(highScore);
  }

  setAllLeds();
  delay(500);
  clearAllLeds();
}

void initializeGame()
{
  initializeTimer();
  gameRunning = true;
  buttonNumber = -1;
  missedPresses = 0;
  countOfTimerInterrupts = 0;
  currentScore = 0;
  enableDisplay();
}

void startTheGame()
{
  Serial.println("Starting a new game");
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

    Serial.print("New random number: ");
    Serial.println(randomNumber);
}