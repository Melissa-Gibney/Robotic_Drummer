// Drum Sequencer for Demo on 3/19/24
// authors: Hanna Berger, Melissa Gibney
// modified: 3/18/24

#include "Drum.h"
#include "DrumManager.h"
#include <Arduino.h>
#include <ezButton.h>
#include <elapsedMillis.h>

#define N_STEPS 8
#include <Wire.h>
#include <elapsedMillis.h>

// Declare Drums
Drum kick;
Drum snare;
Drum tom;
Drum hihat;
DrumManager manager;

int beat_idx = 0; // beat index

const int sequencerLength = 8;
int sequenceLength = 8;

//Declare Tempo and Timing Vars
elapsedMillis msBeatCount;

//unsigned long startMillis;
//unsigned long currentMillis;

int tempo = 120; //The tempo in bpm
//unsigned long tempoInMillis = tempo/60*1000;
long unsigned int msPerBeat = 6000 / tempo;

int curBeatIndex = 0;

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

  // Test
  Wire.begin();     
  Serial.begin(9600);
  Serial.println("Intialized Sequence");
  manager.printSnareSequence();
  
  delay(50);
  manager.checkSequence();
  Serial.println("Updated Sequence");
  manager.printSnareSequence();
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
  if(msBeatCount >= msPerBeat)
  {
    //Reset count
    msBeatCount -= msPerBeat;
    currBeatIndex = (currBeatIndex + 1) % N_STEPS;

    // TO DO:
    // Light up LED for that index
    
    //Play drum at index
    manager.playKick(beat_idx);
    manager.playTom(beat_idx);
    manager.playSnare(beat_idx);
    manager.playHiHat(beat_idx);

    beat_idx = (beat_idx + 1) % 8; // add 1 to the beat index
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
// int sequenceToBitwise(int seqData[])
// {
//   int bitwiseNum = 0b00000000;
//   for(int i = 0; i < sequenceLength; i++)
//   {
//     bitwiseNum = bitwiseNum << 1;
//     bitwiseNum = bitwiseNum + (seqData[i] & 0b00000001);
//   }
//   return bitwiseNum;
// }
