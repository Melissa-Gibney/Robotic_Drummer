// Drum Manager Class CPP FIle
// author: Hanna Berger
// modified: 3/5/24

#include "DrumManager.h"
#include "Drum.h"
#include <Arduino.h>
#include <Wire.h>

DrumManager::DrumManager()
{

}

void DrumManager::assignDrums(Drum *kk, Drum *sn, Drum *tm, Drum *hh)
{
  kick = *kk;
  snare = *sn;
  tom = *tm;
  hihat = *hh;

}

// Check for change in the sequence
void DrumManager::checkSequence()
{
  // Read in sequences from button matrix and parse them here!
  // Row 1 Address 0x2A - byte 1
  // Row 2 Address 0x2A - byte 2
  // Row 3 Address 0x2B - byte 1
  // Row 4 Address 0x2B - byte 2

  int kick_seq[8];
  int snare_seq[8];
  int tom_seq[8];
  int hihat_seq[8];

  // Kick
  int data = 0b10101010; // dummy for now will eventually be read from the tinys
  for (int i = 0; i < 8; i++)
  {
    if ((1<<i) & (data & (1<<i)))
    {
      kick_seq[i] = 1;
    }
    else
    {
      kick_seq[i] = 0;
    }
  }
  // Assign the parsed sequence
  kick.update_sequence(kick_seq);

  // Snare
  int data = 0b01010101; // dummy for now will eventually be read from the tinys
  for (int i = 0; i < 8; i++)
  {
    if ((1<<i) & (data & (1<<i)))
    {
      snare_seq[i] = 1;
    }
    else
    {
      snare_seq[i] = 0;
    }
  }
  // Assign the parsed sequence
  snare.update_sequence(snare_seq);

  // Tom
  int data = 0b00011001; // dummy for now will eventually be read from the tinys
  for (int i = 0; i < 8; i++)
  {
    if ((1<<i) & (data & (1<<i)))
    {
      tom_seq[i] = 1;
    }
    else
    {
      tom_seq[i] = 0;
    }
  }
  // Assign the parsed sequence
  tom.update_sequence(tom_seq);

  // HiHat
  int data = 0b01101101; // dummy for now will eventually be read from the tinys
  for (int i = 0; i < 8; i++)
  {
    if ((1<<i) & (data & (1<<i)))
    {
      hihat_seq[i] = 1;
    }
    else
    {
      hihat_seq[i] = 0;
    }
  }
  // Assign the parsed sequence
  hihat.update_sequence(hihat_seq);

}
// void DrumManager::playKick()
// {

// }
// void DrumManager::playSnare()
// {

// }
// void DrumManager::playTom()
// {

// }
// void DrumManager::playHiHat()
// {

// }
