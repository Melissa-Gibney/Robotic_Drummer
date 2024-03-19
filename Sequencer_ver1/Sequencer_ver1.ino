// Drum Sequencer for Demo on 3/19/24
// authors: Hanna Berger, Melissa Gibney
// modified: 3/18/24

#include "Drum.h"
#include "DrumManager.h"
#include <Arduino.h>
#include <ezButton.h>
#include <elapsedMillis.h>
#include <Wire.h>

#define N_STEPS 8

//Define Solenoid Pins
#define SOL_PIN_KICK 54
#define SOL_PIN_SNARE 55
#define SOL_PIN_TOM 56
#define SOL_PIN_HIHAT 57

// Define LED Pins
#define const int LED_TEMPO_PINS[8] = {2, 3, 4, 5, 6, 7, 8, 9};

// Declare Drums
Drum kick;
Drum snare;
Drum tom;
Drum hihat;
DrumManager manager;

int alternate = 3;

bool drumsArePlaying = false; // Keep track of whether the drums are actuating/holding

const int sequencerLength = 8; // Amount of buttons on one row of the sequencer
int sequenceLength = 8; // Amount of steps in the sequence

//Declare Tempo and Timing Vars
elapsedMillis msBeatCount;
elapsedMillis msDrumReleaseCount;

int tempo = 60; // The tempo in bpm
int curBeatIndex = 0; // The current beat in the sequence
long unsigned int msPerBeat = 15000 / tempo;
long unsigned int msPullTimeKick = 30; // Time that the kick needs to actuate on the beat
long unsigned int msPullTimeTom = 30; // Time that the tom needs to actuate on the beat
long unsigned int msPullTimeSnare = 30; // Time that the snare needs to actuate on the beat
long unsigned int msPullTimeHiHat = 30; // Time that the hihat needs to actuate on the beat
long unsigned int msHoldTime = 10; // Time to hold the solenoid after the articulation and before the release
long unsigned int timeToRetractSolenoid = msHoldTime + msPerBeat; // Time to hold the solenoid after the articulation and before the release

// Dummy Sequence
// int sequence[N_STEPS] = {1,0,0,1,1,1,0,1};
// int sequence2[N_STEPS] = {1,0,1,0,1,0,1,0};
// int sequence3[N_STEPS] = {1,0,1,0,1,0,1,0};
// int sequence4[N_STEPS] = {0,1,1,0,0,1,1,0};

// Dummy Velocity
int velocity[N_STEPS] = {60, 75, 83, 75, 60, 52, 60, 60};

void setup() {
  // put your setup code here, to run once

  // Test
  Wire.begin();     
  Serial.begin(9600);

  //Serial.println("Hello World");
  // Set Pin Modes for LED Tempo Pins
  for(int i = 0; i < 8; i++)
  {
    // Serial.println("Hello World");
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

  // Serial.println("Intialized Sequence");
  // manager.printHiHatSequence();
  
  // delay(10);
  // manager.checkSequence();
  // Serial.println("Updated Sequence");
  // manager.printHiHatSequence();
  
  manager.checkSequence(alternate);
  alternate = 1;
  // Serial.println("Kick Sequence");
  // manager.printKickSequence();
  // Serial.println("Snare Sequence");
  // manager.printSnareSequence();
  // Serial.println("Tom Sequence");
  // manager.printTomSequence();
  // Serial.println("Hi-Hat Sequence");
  // manager.printHiHatSequence();
}

void loop() {
  // put your main code here, to run repeatedly:
  // Keep track of elapsed milliseconds and update every set amount of milliseconds based on the tempo
  // if(msBeatCount >= msPerBeat-msPullTimeKick && !drumsArePlaying)
  // {
  //   //Set drum timers to current time
  //   manager.setDrumTimers(msPullTimeKick, msPullTimeTom, msPullTimeSnare, msPullTimeHiHat);
  //   //Play drum at index
  //   manager.playKick(curBeatIndex);
  //   manager.playTom(curBeatIndex);
  //   manager.playSnare(curBeatIndex);
  //   manager.playHiHat(curBeatIndex);
  //   drumsArePlaying = true;

  //   //Set the amount of time the solenoid should be extended
  //   timeToRetractSolenoid = msHoldTime + msPerBeat;
  // }

  // if(msBeatCount >= msPerBeat-msPullTimeKick && !drumsArePlaying)
  // {
  //   curBeatIndex = (curBeatIndex + 1) % N_STEPS;
  //   manager.checkSequence();
  //   //kick.print_sequence();
  //   manager.setDrumTimers(msPerBeat-msPullTimeKick, msPullTimeTom, msPullTimeSnare, msPullTimeHiHat);
  //   manager.playKick(curBeatIndex);
  //   //manager.playTom(curBeatIndex);
  //   drumsArePlaying = true;
  // }

  //Check if there is a new beat
  if(msBeatCount >= msPerBeat)
  {
    curBeatIndex = (curBeatIndex + 1) % N_STEPS;
    manager.checkSequence(alternate);
    if (alternate == 1){
      alternate = 2;
    } else {
      alternate = 1;
    }
    
    //kick.print_sequence();
    manager.setDrumTimers(msPerBeat-msPullTimeKick, msPerBeat - msPullTimeTom, msPerBeat-msPullTimeSnare, msPerBeat - msPullTimeHiHat);
    manager.playKick(curBeatIndex);
    manager.playSnare(curBeatIndex);
    manager.playTom(curBeatIndex);
    manager.playHiHat(curBeatIndex);

    //Serial.println("Kick Sequence");
    //manager.printKickSequence();
    //Serial.println("Snare Sequence");
    // manager.printSnareSequence();
    //Serial.println("Tom Sequence");
    // manager.printTomSequence();
    //Serial.println("Hi-Hat Sequence");
    // manager.printHiHatSequence();
    //Reset count
    //msBeatCount -= msPerBeat;
    drumsArePlaying = false;

    // Light up LED for that index
    for(int i = 0; i < 8; i++)
    {
      digitalWrite(LED_TEMPO_PINS[i], LOW);
    }
    digitalWrite(LED_TEMPO_PINS[curBeatIndex], HIGH);

    msBeatCount = 0;
  }

  //Check if each drum timer has reached the retraction time
  if(manager.getKick().get_drum_timer() >= timeToRetractSolenoid)
  {
    //Retract the kick
    manager.stopKick();
  }
  if(manager.getTom().get_drum_timer() >= timeToRetractSolenoid)
  {
    //Retract the tom
    manager.stopTom();
  }
  if(manager.getSnare().get_drum_timer() >= timeToRetractSolenoid)
  {
    //Retract the snare
    manager.stopSnare();
  }
  if(manager.getHiHat().get_drum_timer() >= timeToRetractSolenoid)
  {
    //Retract the hihat
    manager.stopHiHat();
  }
}

int sequenceToBitwise(int seqData[])
{
  int bitwiseNum = 0b00000000;
  for(int i = 0; i < N_STEPS; i++)
  {
    bitwiseNum = bitwiseNum << 1;
    bitwiseNum = bitwiseNum + (seqData[i] & 0b00000001);
  }
  return bitwiseNum;
}