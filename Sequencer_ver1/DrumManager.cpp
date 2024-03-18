// Drum Manager Class CPP FIle
// author: Hanna Berger
// modified: 3/18/24

#include "DrumManager.h"
#include "Drum.h"
#include <Arduino.h>
#include <Wire.h>

// I2C addresses for the Tinys
#define TINY1 0x2A
#define TINY2 0x2B

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

void DrumManager::assignSolenoids(int kickPin, int tomPin, int snarePin, int hihatPin)
{
  kick.set_solenoid_pin(kickPin);
  tom.set_solenoid_pin(tomPin);
  snare.set_solenoid_pin(snarePin);
  hihat.set_solenoid_pin(hihatPin);
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

  // Request Kick and Snare Data from TINY 1
  Wire.requestFrom(TINY1, 2);
  int data = Wire.read(); // Read Kick and save to data

  // Kick
  //int data = 0b10101010; // dummy for now will eventually be read from the tinys
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
  //data = 0b01010101; // dummy for now will eventually be read from the tinys

  data = Wire.read(); // Read wire again to get the snare data
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

  // Now Request from TINY 2 to get Tom and HiHat Data
  Wire.requestFrom(TINY2, 2);
  data = Wire.read(); // assign Tom sequence to data

  // Tom
  //data = 0b00011001; // dummy for now will eventually be read from the tinys
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
  //data = 0b01101101; // dummy for now will eventually be read from the tinys
  data = Wire.read(); // read from TINY 2 byte 2 to get hihat sequence
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

void DrumManager::playKick(int beat_idx)
{
  kick.play(beat_idx);
}
void DrumManager::playSnare(int beat_idx)
{
  snare.play(beat_idx);
}
void DrumManager::playTom(int beat_idx)
{
  tom.play(beat_idx);
}
void DrumManager::playHiHat(int beat_idx)
{
  hihat.play(beat_idx);
}

// // Check for change in the sequence
// void DrumManager::checkFullSequence(int kickData, int tomData, int snareData, int hihatData)
// {
//   // Read in sequences from button matrix and parse them here!
//   // Row 1 Address 0x2A - byte 1
//   // Row 2 Address 0x2A - byte 2
//   // Row 3 Address 0x2B - byte 1
//   // Row 4 Address 0x2B - byte 2

//   int kick_seq[8];
//   int snare_seq[8];
//   int tom_seq[8];
//   int hihat_seq[8];

//   // Kick
//   int data = kickData; // dummy for now will eventually be read from the tinys
//   for (int i = 0; i < 8; i++)
//   {
//     if ((1<<i) & (data & (1<<i)))
//     {
//       kick_seq[i] = 1;
//     }
//     else
//     {
//       kick_seq[i] = 0;
//     }
//   }
//   // Assign the parsed sequence
//   kick.update_sequence(kick_seq);

//   // Snare
//   data = snareData; // dummy for now will eventually be read from the tinys
//   for (int i = 0; i < 8; i++)
//   {
//     if ((1<<i) & (data & (1<<i)))
//     {
//       snare_seq[i] = 1;
//     }
//     else
//     {
//       snare_seq[i] = 0;
//     }
//   }
//   // Assign the parsed sequence
//   snare.update_sequence(snare_seq);

//   // Tom
//   data = tomData; // dummy for now will eventually be read from the tinys
//   for (int i = 0; i < 8; i++)
//   {
//     if ((1<<i) & (data & (1<<i)))
//     {
//       tom_seq[i] = 1;
//     }
//     else
//     {
//       tom_seq[i] = 0;
//     }
//   }
//   // Assign the parsed sequence
//   tom.update_sequence(tom_seq);

//   // HiHat
//   data = hihatData; // dummy for now will eventually be read from the tinys
//   for (int i = 0; i < 8; i++)
//   {
//     if ((1<<i) & (data & (1<<i)))
//     {
//       hihat_seq[i] = 1;
//     }
//     else
//     {
//       hihat_seq[i] = 0;
//     }
//   }
//   // Assign the parsed sequence
//   hihat.update_sequence(hihat_seq);
// }

// // Check for change in one drum's sequence
// void DrumManager::checkSingleSequence(int newData, int drumIndex)
// {
//   int new_seq[8];

//   int data = newData; // dummy for now will eventually be read from the tinys
//   for (int i = 0; i < 8; i++)
//   {
//     if ((1<<i) & (data & (1<<i)))
//     {
//       new_seq[i] = 1;
//     }
//     else
//     {
//       new_seq[i] = 0;
//     }
//   }

//   // Update the drum based on the index
//   // Assign the parsed sequence
//   switch(drumIndex)
//   {
//     case 0:
//     {
//       kick.update_sequence(new_seq);
//       break;
//     }
//     case 1:
//     {
//       tom.update_sequenc