// Drum Sequencer with Sliding Window
// authors: Hanna Berger, Melissa Gibney, Anna Boyd
// modified: 3/22/24

#include "util.h"
#include "Drum.h"
#include "DrumManager.h"
#include <Arduino.h>
#include <ezButton.h>
#include <elapsedMillis.h>
#include <Wire.h>

void updateBPMLights();
void updateSwitchMatrix();
void toggleLockSequence();

// Sequencing
int startMark = 4;
int lowerBound = 0;
int upperBound = MAX_LEN - WIN_LEN;
bool seqIsLocked = false;

// Encoder
Encoder control(13, 12, 11);

// Declare Drums
Drum kick;
Drum snare;
Drum tom;
Drum hihat;
DrumManager manager;

int alternate = 3;

//Declare Tempo and Timing Vars
elapsedMillis msBeatCount;

int tempo = 60; // The tempo in bpm
int curBeatIndex = 0; // The current beat in the sequence
long unsigned int msPerBeat = 15000 / tempo;
long unsigned int msPullTimeKick = 30; // Time that the kick needs to actuate on the beat
long unsigned int msPullTimeTom = 30; // Time that the tom needs to actuate on the beat
long unsigned int msPullTimeSnare = 30; // Time that the snare needs to actuate on the beat
long unsigned int msPullTimeHiHat = 30; // Time that the hihat needs to actuate on the beat
long unsigned int msHoldTime = 10; // Time to hold the solenoid after the articulation and before the release
long unsigned int timeToRetractSolenoid = msHoldTime + msPerBeat; // Time to hold the solenoid after the articulation and before the release

// Dummy Velocity
int velocity[] = {60, 75, 83, 75, 60, 52, 60, 60};

void setup() {

  Wire.begin();     
  Serial.begin(9600);

  // Set Pin Modes for LED Tempo Pins
  for(int i = 0; i < 8; i++)
  {
    pinMode(LED_TEMPO_PINS[i], OUTPUT);
    digitalWrite(LED_TEMPO_PINS[i], LOW);
  }

  // Set Pin Modes for Solenoid Pins
  pinMode(SOL_PIN_KICK, OUTPUT);
  pinMode(SOL_PIN_TOM, OUTPUT);
  pinMode(SOL_PIN_SNARE, OUTPUT);
  pinMode(SOL_PIN_HIHAT, OUTPUT);

  // Set Solenoid Pins to Low
  digitalWrite(SOL_PIN_KICK, LOW);
  digitalWrite(SOL_PIN_TOM, LOW);
  digitalWrite(SOL_PIN_SNARE, LOW);
  digitalWrite(SOL_PIN_HIHAT, LOW);

  //Assign Solenoid Pins to Drums
  manager.assignSolenoids(SOL_PIN_KICK, SOL_PIN_TOM, SOL_PIN_SNARE, SOL_PIN_HIHAT);
  manager.checkSequence(alternate, startMark);
  alternate = 1;

}

void loop() {
  // Check encoder
  control.loop();

  int dir = control.rotated();

  switch(dir){
    case 1:         // CW
      // Serial.println("CW");
      if(startMark < MAX_LEN - WIN_LEN){
        startMark++;
        lowerBound++;
        upperBound++;
        updateBPMLights();
        updateSwitchMatrix();
      }
      break;

    case 2:         // CCW
      // Serial.println("CCW");
      if(startMark > 0){
        startMark--;
        lowerBound--;
        upperBound--;
        updateBPMLights();
        updateSwitchMatrix();
      }
      break;

    default:
      break;
  }

  // Serial.println(startMark);

  if(control.justPressed()){
    // Serial.println("PRESS");
    toggleLockSequence();
  }



  //Check if there is a new beat
  if(msBeatCount >= msPerBeat)
  {
    // Update beat
    curBeatIndex++;
    if(curBeatIndex >= upperBound)
      curBeatIndex = lowerBound;

    // Check drum sequence
    manager.checkSequence(alternate, startMark);
    alternate = (alternate == 1) ? 2 : 1;
    
    // Play drums
    manager.setDrumTimers(msPerBeat-msPullTimeKick, msPerBeat - msPullTimeTom, msPerBeat-msPullTimeSnare, msPerBeat - msPullTimeHiHat);
    manager.playDrums(curBeatIndex);

    // Udpate BPM LED
    updateBPMLights();

    // Reset beat count
    msBeatCount -= msPerBeat;
  }

  //Check if each drum timer has reached the retraction time
  manager.stopDrums();
}


/* SEQUENCE LOCK */
void toggleLockSequence(){
  if(seqIsLocked){
    lowerBound = 0;
    upperBound = MAX_LEN - WIN_LEN;
  }

  else{
    lowerBound = startMark;
    upperBound = startMark + WIN_LEN;
  }

  seqIsLocked = !seqIsLocked;
}


/* LED CONTROL */
void updateBPMLights(){
  // Reset LEDs
  for(int i = 0; i < 8; i++)
    digitalWrite(LED_TEMPO_PINS[i], LOW);
  
  // Enable LED for current beat
  if(curBeatIndex >= startMark)
    digitalWrite(LED_TEMPO_PINS[curBeatIndex-startMark], HIGH);
}

void updateSwitchMatrix(){
  // TINY1
  Wire.beginTransmission(TINY1);
  Wire.write(manager.getKick().getSeqBin(startMark));
  Wire.write(manager.getSnare().getSeqBin(startMark));
  Wire.endTransmission();

  delay(2);

  // TINY2
  Wire.beginTransmission(TINY2);
  Wire.write(manager.getTom().getSeqBin(startMark));
  Wire.write(manager.getHiHat().getSeqBin(startMark));
  Wire.endTransmission();

  delay(2);
}
