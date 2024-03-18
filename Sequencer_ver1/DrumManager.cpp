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
  data = 0b01010101; // dummy for now will eventually be read from the tinys
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
  data = 0b00011001; // dummy for now will eventually be read from the tinys
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
  data = 0b01101101; // dummy for now will eventually be read from the tinys
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

// Check for change in the sequence
void DrumManager::checkFullSequence(int kickData, int tomData, int snareData, int hihatData)
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
  int data = kickData; // dummy for now will eventually be read from the tinys
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
  data = snareData; // dummy for now will eventually be read from the tinys
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
  data = tomData; // dummy for now will eventually be read from the tinys
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
  data = hihatData; // dummy for now will eventually be read from the tinys
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

// Check for change in one drum's sequence
void DrumManager::checkSingleSequence(int newData, int drumIndex)
{
  int new_seq[8];

  int data = newData; // dummy for now will eventually be read from the tinys
  for (int i = 0; i < 8; i++)
  {
    if ((1<<i) & (data & (1<<i)))
    {
      new_seq[i] = 1;
    }
    else
    {
      new_seq[i] = 0;
    }
  }

  // Update the drum based on the index
  // Assign the parsed sequence
  switch(drumIndex)
  {
    case 0:
    {
      kick.update_sequence(new_seq);
      break;
    }
    case 1:
    {
      tom.update_sequence(new_seq);
      break;
    }
    case 2:
    {
      snare.update_sequence(new_seq);
      break;
    }
    default:
    {
      hihat.update_sequence(new_seq);
      break;
    }
  }
}

void DrumManager::playKick(int beatIndex)
{
  kick.play(beatIndex);
}

void DrumManager::playSnare()
{
  snare.play(beatIndex);
}

void DrumManager::playTom()
{
  tom.play(b