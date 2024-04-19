// modified: 4/12/24

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
DrumManager drumManager(SOL_PIN_KICK, MUTE_KICK_LED, SOL_PIN_SNARE, MUTE_SNARE_LED, SOL_PIN_TOM, MUTE_TOM_LED, SOL_PIN_HIHAT, MUTE_HIHAT_LED);

// TINY Query Flag
Alt readFlag = DUMMY;

//Declare Tempo and Timing Vars
elapsedMillis msBeatCount;
int tempoChanged = 0;
elapsedMillis timeSinceTempoChange = 0;

int tempo; // The tempo in bpm
int curBeatIndex = 0; // The current beat in the sequence

long unsigned int msPerBeat;
long unsigned int tic = 0, toc = 0;

/********************************************************************* CONTROLS INIT **********************************************************************************/

// Rotary Encoder
Encoder rotary1(ROT1_PIN_CLK, ROT1_PIN_DT, ROT1_PIN_SW);
Encoder rotary2(ROT2_PIN_CLK, ROT2_PIN_DT, ROT2_PIN_SW);

// Buttons
Button button1(BUTTON1_PIN, true);
Button button2(BUTTON2_PIN, true);

Button clearkick(CLEAR_KICK, true);
Button clearsnare(CLEAR_SNARE, true);
Button cleartom(CLEAR_TOM, true);
Button clearhihat(CLEAR_HIHAT, true);

Button mutekick(MUTE_KICK, true);
Button mutesnare(MUTE_SNARE, true);
Button mutetom(MUTE_TOM, true);
Button mutehihat(MUTE_HIHAT, true);

Button reset(MASTER_RESET, true);
Button startstop(START_STOP, true);

int pause_timer;

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

  // Init tempo
  setTempo(TEMPO_DEFAULT);

  // Set Pin Modes for LED Tempo Pins
  for(int i = 0; i < 8; i++)
  {
    pinMode(LED_TEMPO_PINS[i], OUTPUT);
    digitalWrite(LED_TEMPO_PINS[i], LOW);
  }

  // Init sequence using DUMMY sequence
  drumManager.checkSequence(readFlag);
  readFlag = T1;
}


/********************************************************************* LOOP *******************************************************************************************/

void loop() {

  tic = millis();

  // Update control states
  updateControlStates();

  // Check buttons
  checkButtons();

  // Check for tempo change
  checkTempoChange();

  // Display buttons
  updateDisplay();
  
  // Check pause button
  if(startstop.justPressed())
  {
    drumManager.toggleStartStop();

    if(drumManager.isStopped())
      pause_timer = msBeatCount;
    
    else
      msBeatCount = pause_timer;
  }

  // Update tempo
  if((tempoChanged != 0) && (timeSinceTempoChange >= 150))
  {
    tempo += tempoChanged;
    setTempo(tempo);
    tempoChanged = 0;
  }


  // Begin new beat
  if((msBeatCount >= msPerBeat) && !drumManager.isStopped())
  {
    curBeatIndex = (curBeatIndex + 1) % WIN_LEN;

    // Update BPM LED
    for(int i = 0; i < 8; i++)
      digitalWrite(LED_TEMPO_PINS[i], LOW);
    digitalWrite(LED_TEMPO_PINS[curBeatIndex], HIGH);

    // Update sequences
    drumManager.checkSequence(readFlag);
    readFlag = (readFlag == T1) ? T2 : T1;
    
    // Play drums
    drumManager.play(curBeatIndex);
    
    // Update beat timer
    msBeatCount -= msPerBeat;
  }
  

  // Update drums
  drumManager.loop();

  toc = millis();
  // Serial.println(toc-tic);
}



void checkButtons()
{
  // Clear buttons
  if(clearkick.justPressed())
    drumManager.clearDrum(KICK);
  
  if(clearsnare.justPressed())
    drumManager.clearDrum(SNARE);

  if(cleartom.justPressed())
    drumManager.clearDrum(TOM);
    
  if(clearhihat.justPressed())
    drumManager.clearDrum(HIHAT);

  // Mute buttons
  if(mutekick.justPressed())
    drumManager.muteDrum(KICK);
  
  if(mutesnare.justPressed())
    drumManager.muteDrum(SNARE);
  
  if(mutetom.justPressed())
    drumManager.muteDrum(TOM);
  
  if(mutehihat.justPressed())
    drumManager.muteDrum(HIHAT);

  // Reset button
  if(reset.justPressed())
    drumManager.masterReset();
}



void setTempo(int t)
{
  if((t <= TEMPO_MAX) && (t >= TEMPO_MIN))
  {
    tempo = t;
    msPerBeat = 15000 / tempo;

    drumManager.setTempo(msPerBeat);
  }
}



void updateDisplay()
{
  if (button1.justPressed())
    dispManager.movePage(1);  // increment
  
  if (button2.justPressed())
    dispManager.movePage(-1); // decrement

  // Display rotary encoder
  if(rotary1.justPressed())
    dispManager.rotaryPress();

  if(rotary1.rotated() == 1)  // CW
    dispManager.rotaryCW();

  else if(rotary1.rotated() == 2) // CCW
    dispManager.rotaryCCW();
}



void checkTempoChange()
{
  if(rotary2.rotated() == 1)
  {
    tempoChanged++;
    timeSinceTempoChange = 0;
    dispManager.setTempo(tempo+tempoChanged);
  }  
  else if(rotary2.rotated() == 2)
  {
    tempoChanged--;
    timeSinceTempoChange = 0;
    dispManager.setTempo(tempo+tempoChanged);
  }
  if(rotary2.justPressed())
  {
    tempoChanged = TEMPO_DEFAULT - tempo;
    timeSinceTempoChange = 0;
    dispManager.setTempo(tempo+tempoChanged);
  }
}



void updateControlStates()
{
  rotary1.loop();
  rotary2.loop();
  button1.loop();
  button2.loop();
  clearkick.loop();
  clearsnare.loop();
  cleartom.loop();
  clearhihat.loop();
  mutekick.loop();
  mutesnare.loop();
  mutetom.loop();
  mutehihat.loop();
  reset.loop();
  startstop.loop();
}