// modified: 5/2/24

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

//Declare Tempo and Timing Vars
elapsedMillis msBeatCount;
int tempoChanged = 0;
elapsedMillis timeSinceTempoChange = 0;
int pause_timer;

int tempo; // The tempo in bpm
int curBeatIndex = 0; // The current beat in the sequence

long unsigned int msPerBeat; // beat converted to ms
long unsigned int tic = 0, toc = 0;

elapsedMillis flashTimer = 0;
bool flash = true;  // high or low
int velocityMode = 0; // is velocity mode on or off

// TINY Query Flag
Alt readFlag = DUMMY;

int newVelocity;
int newTempo;

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

/********************************************************************* PROTOTYPES *************************************************************************************/

void setTempo(int);
void updateControlStates();
void checkButtons();
void checkTempoChange();
void updateDisplay();
void setTempo(int);


/********************************************************************* SETUP ******************************************************************************************/

void setup() {

  // Begin TWI
  Wire.begin();     
  Wire.setClock(400000UL);
  Wire.setWireTimeout(1500);    // When I2C bus locks, loop() does not lock

  // Disable Mega pull-up resistors
  digitalWrite(SDA, LOW);
  digitalWrite(SCL, LOW);

  // Begin display
  dispManager.init();

  // Init tempo
  setTempo(TEMPO_DEFAULT);
  // Init velocity
  drumManager.resetVelocity();

  // Set Pin Modes for LED Tempo Pins
  for(int i = 0; i < 8; i++)
  {
    pinMode(LED_TEMPO_PINS[i], OUTPUT);
    digitalWrite(LED_TEMPO_PINS[i], LOW);
  }

  // // Init sequence using DUMMY sequence
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

  // Check tempo encoder
  checkTempoChange();

  // Update OLED
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
    
    // Stop drums
    drumManager.endBeat();

    // Start new beat
    drumManager.play(curBeatIndex);
    
    // Update beat timer
    msBeatCount -= msPerBeat;
  }
  

  // Update drums
  drumManager.loop();

  // Velocity mode flash
  if(!velocityMode)
    flashTimer = 0;

  else if(flashTimer >= 500)
  {
    flash = !flash;
    drumManager.flash(flash);
    flashTimer -= 500;
  }

  toc = millis();
}
  


void checkButtons()
{
  // Clear buttons
  if(clearkick.justPressed())
  {
    if(!velocityMode)
      drumManager.clearDrum(KICK);

    else
      drumManager.resetVelocity(KICK);
  }
  
  if(clearsnare.justPressed())
  {
    if(!velocityMode)
      drumManager.clearDrum(SNARE);

    else
      drumManager.resetVelocity(SNARE);
  }

  if(cleartom.justPressed())
  {
    if(!velocityMode)
      drumManager.clearDrum(TOM);

    else
      drumManager.resetVelocity(TOM);
  }
    
  if(clearhihat.justPressed())
  {
    if(!velocityMode)
      drumManager.clearDrum(HIHAT);

    else
      drumManager.resetVelocity(HIHAT);
  }

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
  {
    if(!velocityMode)
      drumManager.masterReset();
    else
      drumManager.resetVelocity();
  }
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
  {
    dispManager.movePage(1);  // increment page
    if(dispManager.getPage() == 2) // if display is on the velocity page turn velocity mode on
      velocityMode = 1;
    else
      velocityMode = 0; // if the display is on a different page turn velocity mode off
    
    drumManager.setVelocityMode(velocityMode);
  }
  
  if (button2.justPressed())
  {
    dispManager.movePage(-1); // decrement page
    if(dispManager.getPage() == 2)
      velocityMode = 1;
    else
      velocityMode = 0;
    
    drumManager.setVelocityMode(velocityMode);
  }

  // Display rotary encoder
  if(rotary1.justPressed())
  {
    dispManager.rotaryPress(); // call function for current page 

    if(dispManager.getPage() == 0) // if on preset page when encoder pressed tell drum manager to set preset velocities 
    {
      drumManager.set_vel_preset(dispManager.getPreset());
    }

    if(velocityMode) // if velocity mode is on (currently on velocity page) set the current step's velocity to the default
      drumManager.setStepVelocity(VELOCITY_DEFAULT);
  }

  if(rotary1.rotated() == 1)  // CW
  {
    dispManager.rotaryCW(); // call function for current page 

    if(velocityMode) // if velocity mode is on (currently on velocity page) add one to the current step's velocity
      newVelocity = drumManager.getStepVelocity() + 1;
      if (newVelocity > VELOCITY_MAX)
      {
        newVelocity = VELOCITY_MAX;
      }
      drumManager.setStepVelocity(newVelocity); 
  }

  else if(rotary1.rotated() == 2) // CCW
  {
    dispManager.rotaryCCW();

    if(velocityMode) // if velocity mode is on (currently on velocity page) subtract one to the current step's velocity
      newVelocity = drumManager.getStepVelocity() - 1;
      if (newVelocity < VELOCITY_MIN)
      {
        newVelocity = VELOCITY_MIN;
      }
      drumManager.setStepVelocity(newVelocity); 
  }

  if(velocityMode && (drumManager.getStepVelocity() != dispManager.getVel())) // if the current velocity doesn't match the displayed one fix it
    dispManager.setVel(drumManager.getStepVelocity());
}



void checkTempoChange()
{
  if(rotary2.rotated() == 1 && (tempo < TEMPO_MAX))  // increment
  {
    velocityMode = 0;
    tempoChanged++;
    timeSinceTempoChange = 0;
    newTempo = tempoChanged + tempo;
    if((newTempo) > TEMPO_MAX)
    {
      newTempo = TEMPO_MAX;
    }
    //dispManager.setTempo(tempo+tempoChanged);
    dispManager.setTempo(newTempo);
    drumManager.setVelocityMode(velocityMode);
  }  
  else if(rotary2.rotated() == 2 && (tempo > TEMPO_MIN)) // decrement
  {
    velocityMode = 0;
    tempoChanged--;
    timeSinceTempoChange = 0;
    newTempo = tempoChanged + tempo;
    if((newTempo) < TEMPO_MIN)
    {
      newTempo = TEMPO_MIN;
    }
    //dispManager.setTempo(tempo+tempoChanged);
    dispManager.setTempo(newTempo);
    drumManager.setVelocityMode(velocityMode);
  }
  if(rotary2.justPressed()) // reset
  {
    velocityMode = 0;
    tempoChanged = TEMPO_DEFAULT - tempo;
    timeSinceTempoChange = 0;
    dispManager.setTempo(tempo+tempoChanged);
    drumManager.setVelocityMode(velocityMode);
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


