// modified: 4/10/24

/* UTIL LIBRARIES */
#include "util.h"
#include <Arduino.h>
#include <elapsedMillis.h>
#include <Wire.h>

/* DRUM LIBRARIES */
#include "Drum.h"
#include "DrumManager.h"

/* DISPLAY LIBRARIES */
#include "Display.h"

/********************************************************************* DISPLAY INIT ***********************************************************************************/

DisplayManager dispManager;

/********************************************************************* SEQUENCER INIT *********************************************************************************/

// Declare Drums
DrumManager manager(SOL_PIN_KICK, SOL_PIN_SNARE, SOL_PIN_TOM, SOL_PIN_HIHAT);

// TINY Query Flag
Alt readFlag = DUMMY;

//Declare Tempo and Timing Vars
elapsedMillis msBeatCount;

int tempo = 60; // The tempo in bpm
int curBeatIndex = 0; // The current beat in the sequence

long unsigned int msPerBeat = 15000 / tempo;


/********************************************************************* CONTROLS INIT **********************************************************************************/

// Rotary Encoder
Encoder rotary1(ROT1_PIN_CLK, ROT1_PIN_DT, ROT1_PIN_SW);

// Buttons
Button button1(BUTTON1_PIN, true);
Button button2(BUTTON2_PIN, true);


/********************************************************************* SETUP ******************************************************************************************/

void setup() {
  Serial.begin(9600);   // for debug

  // Begin TWI
  Wire.begin();     
  Wire.setClock(100000UL);
  Wire.setWireTimeout(1500);    // When I2C bus locks, loop() does not lock

  // Disable Mega pull-up resistors
  digitalWrite(SDA, LOW);
  digitalWrite(SCL, LOW);

  // Begin display
  dispManager.init();

  // Set Pin Modes for LED Tempo Pins
  for(int i = 0; i < 8; i++)
  {
    pinMode(LED_TEMPO_PINS[i], OUTPUT);
    digitalWrite(LED_TEMPO_PINS[i], LOW);
  }

  // Init sequence using DUMMY sequence
  manager.checkSequence(readFlag);
  readFlag = T1;
}


/********************************************************************* LOOP *******************************************************************************************/

void loop() {

  // Update control states
  rotary1.loop();
  button1.loop();
  button2.loop();

  // Begin new beat
  if(msBeatCount >= msPerBeat)
  {
    curBeatIndex = (curBeatIndex + 1) % WIN_LEN;

    // Update BPM LED
    for(int i = 0; i < 8; i++)
      digitalWrite(LED_TEMPO_PINS[i], LOW);
    digitalWrite(LED_TEMPO_PINS[curBeatIndex], HIGH);

    // Update sequences
    manager.checkSequence(readFlag);
    readFlag = (readFlag == T1) ? T2 : T1;
    
    // Play drums
    manager.play(curBeatIndex);
    
    // Update beat timer
    msBeatCount -= msPerBeat;
  }

  // Update drums
  manager.loop();

  // Display buttons
  if (button1.justPressed())
    dispManager.movePage(1);
  
  if (button2.justPressed())
    dispManager.movePage(-1);


  // Display rotary encoder
  if(rotary1.justPressed())
    dispManager.rotaryPress();

  if(rotary1.rotated() == 1)  // CW
    dispManager.rotaryCW();

  else if(rotary1.rotated() == 2) // CCW
    dispManager.rotaryCCW();
}


// int sequenceToBitwise(int seqData[])
// {
//   int bitwiseNum = 0b00000000;
//   for(int i = 0; i < N_STEPS; i++)
//   {
//     bitwiseNum = bitwiseNum << 1;
//     bitwiseNum = bitwiseNum + (seqData[i] & 0b00000001);
//   }
//   return bitwiseNum;
// }