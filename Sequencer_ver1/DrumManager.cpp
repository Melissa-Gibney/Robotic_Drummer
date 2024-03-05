// Drum Manager Class CPP FIle
// author: Hanna Berger
// modified: 3/5/24

#include "DrumManager.h"
#include "Drum.h"
#include <Arduino.h>


DrumManager::DrumManager()
{

}

void DrumManager::assignDrums(Drum kk, Drum sn, Drum tm, Drum hh)
{
  kick = kk;
  snare = sn;
  tom = tm;
  hihat = hh;

}

// Check for change in the sequence
void DrumManager::checkSequence()
{

  // Read in sequences from button matrix and parse them here!


  // Assign the parsed messages to each drum
  // kick.update_sequence(const int *new_sequence);
  // snare.update_sequence(const int *new_sequence);
  // tom.update_sequence(const int *new_sequence);
  // hihat.update_sequence(const int *new_sequence);

}
void DrumManager::playKick()
{

}
void DrumManager::playSnare()
{

}
void DrumManager::playTom()
{

}
void DrumManager::playHiHat()
{

}
