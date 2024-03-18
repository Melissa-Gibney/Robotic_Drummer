// Drum Sequencer for Demo on 3/19/24
// authors: Hanna Berger
// modified: 3/4/24

#include "Drum.h"
#include "DrumManager.h"
#include <Arduino.h>
#include <ezButton.h>

// Declare Drums
Drum kick;
Drum snare;
Drum tom;
Drum hihat;
DrumManager manager;

const int sequencerLength = 8;
int sequenceLength = 8;

// Initialize Kick Button Pins
int kickPins[sequencerLength] = {11, 12, 13, 14, 15, 16, 17, 18};

// Initialize Tom Button Pins
int tomPins[sequencerLength] = {21, 22, 23, 24, 25, 26, 27, 28};

// Initialize Snare Button Pins
int snarePins[sequencerLength] = {31, 32, 33, 34, 35, 36, 37, 38};

// Initialize Hi Hat Button Pins
int hihatPins[sequencerLength] = {41, 42, 43, 44, 45, 46, 47, 48};

// Declare Kick Buttons
ezButton kickButtons[] = {kickPins[0], kickPins[1], kickPins[2], kickPins[3], kickPins[4], kickPins[5], kickPins[6], kickPins[7]};
// ezButton kickButton1(kickButton1Pin);
// ezButton kickButton2(kickButton2Pin);
// ezButton kickButton3(kickButton3Pin);
// ezButton kickButton4(kickButton4Pin);
// ezButton kickButton5(kickButton5Pin);
// ezButton kickButton6(kickButton6Pin);
// ezButton kickButton7(kickButton7Pin);
// ezButton kickButton8(kickButton8Pin);

// Declare Tom Buttons
ezButton tomButtons[] = {tomPins[0], tomPins[1], tomPins[2], tomPins[3], tomPins[4], tomPins[5], tomPins[6], tomPins[7]};

// Declare Snare Buttons
ezButton snareButtons[] = {snarePins[0], snarePins[1], snarePins[2], snarePins[3], snarePins[4], snarePins[5], snarePins[6], snarePins[7]};

// Declare Hi Har Buttons
ezButton hihatButtons[] = {hihatPins[0], hihatPins[1], hihatPins[2], hihatPins[3], hihatPins[4], hihatPins[5], hihatPins[6], hihatPins[7]};

// Dummy Sequence
int sequence[8] = {1,0,0,1,1,1,0,1};
int sequence2[8] = {1,0,1,0,1,0,1,0};
int sequence3[8] = {1,0,1,0,1,0,1,0};
int sequence4[8] = {0,1,1,0,0,1,1,0};

// Dummy Velocity
int velocity[8] = {60, 75, 83, 75, 60, 52, 60, 60};


void setup() {
  // put your setup code here, to run once

  //Initialize Buttons
  for(int i = 0; i < sequencerLength; i++)
  {
    kickButtons[i].setDebounceTime(50);
    tomButtons[i].setDebounceTime(50);
    snareButtons[i].setDebounceTime(50);
    hihatButtons[i].setDebounceTime(50);
  }

  // Test
  Serial.begin(9600);
  //kick.update_sequence(sequence);
  Serial.println("Intialized Sequence");
  kick.print_sequence();
  manager.assignDrums(&kick, &snare, &tom, &hihat);
  manager.checkSequence();
  Serial.println("Updated Sequence");
  manager.printKickSequence();

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
  //Go through all of the sequencer buttons

  for(int i = 0; i < sequencerLength; i++)
  {
    //Set buttons to loop
    kickButtons[i].loop();
    tomButtons[i].loop();
    snareButtons[i].loop();
    hihatButtons[i].loop();

    // Update Kick sequence on press
    if(kickButtons[i].isPressed())
    {
      sequence[i] = !sequence[i];
      // Change sequence
      manager.checkSingleSequence(sequenceToBitwise(sequence), 0);
      // Update button LEDs
    }

    if(tomButtons[i].isPressed())
    {
      sequence2[i] = !sequence2[i];
      // Change sequence
      manager.checkSingleSequence(sequenceToBitwise(sequence2), 1);
      // Update button LEDs
    }

    if(snareButtons[i].isPressed())
    {
      sequence3[i] = !sequence3[i];
      // Change sequence
      manager.checkSingleSequence(sequenceToBitwise(sequence3), 2);
      // Update button LEDs
    }

    if(hihatButtons[i].isPressed())
    {
      sequence4[i] = !sequence4[i];
      // Change sequence
      manager.checkSingleSequence(sequenceToBitwise(sequence4), 3);
      // Update button LEDs
    }
  }
}

int sequenceToBitwise(int seqData[])
{
  int bitwiseNum = 0b00000000;
  for(int i = 0; i < sequenceLength; i++)
  {
    bitwiseNum = bitwiseNum << 1;
    bitwiseNum = bitwiseNum + (seqData[i] & 0b00000001);
  }
  return bitwiseNum;
}
