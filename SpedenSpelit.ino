#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// Use these 2 volatile variables for communicating between
// loop() function and interrupt handlers
volatile int buttonNumber = -1;           // for buttons interrupt handler
volatile bool newTimerInterrupt = false;  // for timer interrupt handler


void setup()
{
  /*
    Initialize here all modules
  */
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
     int randomNumber = random(0, 4);
     setLed(randomNumber);
  }
}

void initializeTimer(void)
{
	// see requirements for the function from SpedenSpelit.h
  // Hmm nämä menee Arduinon Verifystä läpi mutta VS Code ilmeisesti ei ymmärrä:
  // Timer asetukset
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // Aseta vertailuarvo (OCR1A) 0.1 sekunnin välein
  OCR1A = 1562;

  // Aseta CTC-tila ja prescaleri
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);

  // Ota käyttöön Timer1:n keskeytys
  TIMSK1 |= (1 << OCIE1A);
}
ISR(TIMER1_COMPA_vect)
{
  /*
  Communicate to loop() that it's time to make new random number.
  Increase timer interrupt rate after 10 interrupts.
  */
  
}


void checkGame(byte nbrOfButtonPush)
{
	// see requirements for the function from SpedenSpelit.h
}


void initializeGame()
{
	// see requirements for the function from SpedenSpelit.h
}

void startTheGame()
{
   // see requirements for the function from SpedenSpelit.h
}

