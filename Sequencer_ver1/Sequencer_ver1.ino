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
int kickButtonPins[sequencerLength] = {11, 12, 13, 14, 15, 16, 17, 18};
int kickLEDPins[sequencerLength] = {21, 22, 23, 24, 25, 26, 27, 28};

// Initialize Tom Button Pins
int tomButtonPins[sequencerLength] = {31, 32, 33, 34, 35, 36, 37, 38};
int tomLEDPins[sequencerLength] = {41, 42, 43, 44, 45, 46, 47, 48};

// Initialize Snare Button Pins
int snareButtonPins[sequencerLength] = {51, 52, 53, 54, 55, 56, 57, 58};
int snareLEDPins[sequencerLength] = {61, 62, 63, 64, 65, 66, 67, 68};

// Initialize Hi Hat Button Pins
int hihatButtonPins[sequencerLength] = {71, 72, 73, 74, 75, 76, 77, 78};
int hihatLEDPins[sequencerLength] = {81, 82, 83, 84, 85, 86, 87, 88};

// Declare Kick Buttons
ezButton kickButtons[] = {kickButtonPins[0], kickButtonPins[1], kickButtonPins[2], kickButtonPins[3], kickButtonPins[4], kickButtonPins[5], kickButtonPins[6], kickButtonPins[7]};

// Declare Tom Buttons
ezButton tomButtons[] = {tomButtonPins[0], tomButtonPins[1], tomButtonPins[2], tomButtonPins[3], tomButtonPins[4], tomButtonPins[5], tomButtonPins[6], tomButtonPins[7]};

// Declare Snare Buttons
ezButton snareButtons[] = {snareButtonPins[0], snareButtonPins[1], snareButtonPins[2], snareButtonPins[3], snareButtonPins[4], snareButtonPins[5], snareButtonPins[6], snareButtonPins[7]};

// Declare Hi Har Buttons
ezButton hihatButtons[] = {hihatButtonPins[0], hihatButtonPins[1], hihatButtonPins[2], hihatButtonPins[3], hihatButtonPins[4], hihatButtonPins[5], hihatButtonPins[6], hihatButtonPins[7]};

// Dummy Sequence
int sequence[8] = {1,0,0,1,1,1,0,1};
int sequence2[8] = {1,0,1,0,1,0,1,0};
int sequence3[8] = {1,0,1,0,1,0,1,0};
int sequence4[8] = {0,1,1,0,0,1,1,0};

// Dummy Velocity
int velocity[8] = {60, 75, 83, 75, 60, 52, 60, 60};


void setup() {
  // put your setup code here, to run once

  //Initialize Buttons and Pins
  for(int i = 0; i < sequencerLength; i++)
  {
    //Set LED pin modes
    pinMode(kickLEDPins[i], INPUT_PULLUP);
    pinMode(tomLEDPins[i], INPUT_PULLUP);
    pinMode(snareLEDPins[i], INPUT_PULLUP);
    pinMode(hihatLEDPins[i], INPUT_PULLUP);

    //Set button pins
    pinMode(kickButtonPins[i], OUTPUT);
    pinMode(tomButtonPins[i], OUTPUT);
    pinMode(snareButtonPins[i], OUTPUT);
    pinMode(hihatButtonPins[i], OUTPUT);

    //Set debounce on buttons
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
      if(sequence[i])
      {
        digitalWrite(kickLEDPins[i], LOW);
      }
      else
      {
        digitalWrite(kickLEDPins[i], HIGH);
      }
    }

    if(tomButtons[i].isPressed())
    {
      sequence2[i] = !sequence2[i];
      // Change sequence
      manager.checkSingleSequence(sequenceToBitwise(sequence2), 1);
      // Update button LEDs
      if(tomButtons[i].isPressed())
      {
        sequence[i] = !sequence[i];
        // Change sequence
        manager.checkSingleSequence(sequenceToBitwise(sequence), 0);
        // Update button LEDs
        if(sequence[i])
        {
          digitalWrite(tomLEDPins[i], LOW);
        }
        else
        {
          digitalWrite(tomLEDPins[i], HIGH);
        }
      }
    }

    if(snareButtons[i].isPressed())
    {
      sequence3[i] = !sequence3[i];
      // Change sequence
      manager.checkSingleSequence(sequenceToBitwise(sequence3), 2);
      // Update button LEDs
      if(snareButtons[i].isPressed())
      {
        sequence[i] = !sequence[i];
        // Change sequence
        manager.checkSingleSequence(sequenceToBitwise(sequence), 0);
        // Update button LEDs
        if(sequence[i])
        {
          digitalWrite(snareLEDPins[i], LOW);
        }
        else
        {
          digitalWrite(snareLEDPins[i], HIGH);
        }
      }
    }

    if(hihatButtons[i].isPressed())
    {
      sequence4[i] = !sequence4[i];
      // Change sequence
      manager.checkSingleSequence(sequenceToBitwise(sequence4), 3);
      // Update button LEDs
      if(sequence[i])
      {
        digitalWrite(hihatLEDPins[i], LOW);
      }
      else
      {
        digitalWrite(hihatLEDPins[i], HIGH);
      }
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
