// Drum Sequencer for Demo on 3/19/24
// authors: Hanna Berger
// modified: 3/4/24

#include "Drum.h"
#include "DrumManager.h"
#include <Arduino.h>

// Declare Drums
Drum kick;
Drum snare;
Drum tom;
Drum hihat;
DrumManager manager;

// Dummy Sequence
int sequence[8] = {1,0,0,1,1,1,0,1};
int sequence2[8] = {1,0,1,0,1,0,1,0};
int sequence3[8] = {1,0,1,0,1,0,1,0};
int sequence4[8] = {0,1,1,0,0,1,1,0};

// Dummy Velocity
int velocity[8] = {60, 75, 83, 75, 60, 52, 60, 60};


void setup() {
  // put your setup code here, to run once

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

}
