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
#define SOL_PIN_TOM 55
#define SOL_PIN_SNARE 56
#define SOL_PIN_HIHAT 57

// Define LED Pins
#define const int LED_TEMPO_PINS[8] = {2, 3, 4, 5, 6, 7, 8, 9};

// Declare Drums
Drum kick;
Drum snare;
Drum tom;
Drum hihat;
DrumManager manager;

bool drumsArePlaying = false; // Keep track of whether the drums are actuating/holding

const int sequencerLength = 8; // Amount of buttons on one row of the sequencer
int sequenceLength = 8; // Amount of steps in the sequence

//Declare Tempo and Timing Vars
elapsedMillis msBeatCount;
elapsedMillis msDrumReleaseCount;

int tempo = 120; // The tempo in bpm
int curBeatIndex = 0; // The current beat in the sequence
long unsigned int msPerBeat = 6000 / tempo;
long unsigned int msPullTimeKick = 6; // Time that the kick needs to actuate on the beat
long unsigned int msPullTimeTom = 6; // Time that the tom needs to actuate on the beat
long unsigned int msPullTimeSnare = 6; // Time that the snare needs to actuate on the beat
long unsigned int msPullTimeHiHat = 6; // Time that the hihat needs to actuate on the beat
long unsigned int msHoldTime = 10; // Time to hold the solenoid after the articulation and before the release
long unsigned int timeToRetractSolenoid = msHoldTime + msPerBeat; // Time to hold the solenoid after the articulation and before the release

// Dummy Sequence
int sequence[N_STEPS] = {1,0,0,1,1,1,0,1};
int sequence2[N_STEPS] = {1,0,1,0,1,0,1,0};
int sequence3[N_STEPS] = {1,0,1,0,1,0,1,0};
int sequence4[N_STEPS] = {0,1,1,0,0,1,1,0};

// Dummy Velocity
int velocity[N_STEPS] = {60, 75, 83, 75, 60, 52, 60, 60};

void setup() {
  // put your setup code here, to run once
  // Initialize milliseconds
  //startMillis = millis();
  //currentMillis = millis();

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

  // Test
  Wire.begin();     
  Serial.begin(9600);
  Serial.println("Intialized Sequence");
  // manager.printSnareSequence();
  
  delay(50);
  manager.checkSequence();
  Serial.println("Updated Sequence");
  // manager.printSnareSequence();

  /*
  // FOR TESTING
  Serial.begin(9600);

  Serial.println("Intialized Sequence");
  kick.print_sequence();

  kick.update_sequence(sequence);

  Serial.println("Updated Sequence");
  kick.print_sequence();

  Serial.println("Intialized Velocity");
  kick.print_velocity();

  kick.update_velocity(velocity);

  Serial.println("Updated Velocity");
  kick.print_velocity();
  */

}

void loop() {
  // put your main code here, to run repeatedly:
  //Keep track of elapsed milliseconds and update every set amount of milliseconds based on the tempo
  //currentMillis = millis();
  if(msBeatCount >= msPullTimeKick && !drumsArePlaying)
  {
    //Set drum timers to current time
    manager.setDrumTimers(msPullTimeKick, msPullTimeTom, msPullTimeSnare, msPullTimeHiHat);
    //Play drum at index
    manager.playKick(curBeatIndex);
    manager.playTom(curBeatIndex);
    manager.playSnare(curBeatIndex);
    manager.playHiHat(curBeatIndex);
    drumsArePlaying = true;

    //Set the amount of time the solenoid should be extended
    timeToRetractSolenoid = msHoldTime + msPerBeat;
  }

  //Check if there is a new beat
  if(msBeatCount >= msPerBeat)
  {
    //Reset count
    msBeatCount -= msPerBeat;
    curBeatIndex = (curBeatIndex + 1) % N_STEPS;
    drumsArePlaying = false;

    // Light up LED for that index
    for(int i = 0; i < 8; i++)
    {
      digitalWrite(LED_TEMPO_PINS[i], LOW);
    }
    digitalWrite(LED_TEMPO_PINS[curBeatIndex], HIGH);

    curBeatIndex = (curBeatIndex + 1) % 8; // add 1 to the beat index
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