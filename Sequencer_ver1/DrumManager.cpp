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

Drum DrumManager::getKick()
{
  return kick;
}

Drum DrumManager::getTom()
{
  return tom;
}

Drum DrumManager::getSnare()
{
  return snare;
}

Drum DrumManager::getHiHat()
{
  return hihat;
}

// Check for change in the sequence
void DrumManager::checkSequence(int flag)
{
  // Read in sequences from button matrix and parse them here!
  // Row 1 Address 0x2A - byte 1
  // Row 2 Address 0x2A - byte 2
  // Row 3 Address 0x2B - byte 1
  // Row 4 Address 0x2B - byte 2
  Serial.print("Entered check sequence");
  int kick_seq[8];
  int snare_seq[8];
  int tom_seq[8];
  int hihat_seq[8];

  //Check the flag and assign the default kick, snare, tom, and hi-hat
  if (flag == 3) {
    int dataKick = 0b10101010;
    int dataSnare = 0b01010101;
    int dataTom = 0b01010101;
    int dataHiHat = 0b01010101;
  }

  //Check the flag, read the wire requests, and assign the sequences
  if (flag == 1) {
    Wire.requestFrom(TINY1, 2);
    int dataKick = Wire.read(); // Read Kick and save to data
    int dataSnare = Wire.read();
    // flush
    while (Wire.available()){
      Wire.read();
    }

    // Kick
    for (int i = 0; i < 8; i++)
    {
      if ((1<<i) & (dataKick & (1<<i)))
      {
        kick_seq[i] = 1;
        //Serial.print(1);
      }
      else
      {
        kick_seq[i] = 0;
        //Serial.print(0);
      }
    }
    // Assign the parsed sequence
    kick.update_sequence(kick_seq);

    // Snare
    for (int i = 0; i < 8; i++)
    {
      if ((1<<i) & (dataSnare & (1<<i)))
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
  }

  //Check the flag, read the wire requests, and assign the sequences
  if (flag == 2)
  {
    Wire.requestFrom(TINY2, 2);
    int dataTom = Wire.read();
    int dataHiHat = Wire.read();
    // Flush
    while (Wire.available())
    {
      Wire.read();
    }

    //Tom
    Serial.print(dataTom);
    for (int i = 0; i < 8; i++)
    {
      if ((1<<i) & (dataTom & (1<<i)))
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
    for (int i = 0; i < 8; i++)
    {
      if ((1<<i) & (dataHiHat & (1<<i)))
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

void DrumManager::stopKick()
{
  kick.stop();
}
void DrumManager::stopTom()
{
  tom.stop();
}
void DrumManager::stopSnare()
{
  snare.stop();
}
void DrumManager::stopHiHat()
{
  hihat.stop();
}

void DrumManager::setDrumTimers(unsigned long kickTime, unsigned long tomTime, unsigned long snareTime, unsigned long hihatTime)
{
  kick.set_drum_timer(kickTime);
  tom.set_drum_timer(tomTime);
  snare.set_drum_timer(snareTime);
  hihat.set_drum_timer(hihatTime);
}

