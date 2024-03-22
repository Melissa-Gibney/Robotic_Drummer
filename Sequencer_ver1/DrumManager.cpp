// Drum Manager Class CPP FIle
// author: Hanna Berger
// modified: 3/18/24

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
void DrumManager::checkSequence(int flag, int offset)
{
  int dataKick = 0, dataSnare = 0, dataTom = 0, dataHiHat = 0;


  // Read in sequences from button matrix and parse them here!
  // Row 1 Address 0x2A - byte 1
  // Row 2 Address 0x2A - byte 2
  // Row 3 Address 0x2B - byte 1
  // Row 4 Address 0x2B - byte 2
  int kick_seq[WIN_LEN] = {0};
  int snare_seq[WIN_LEN] = {0};
  int tom_seq[WIN_LEN] = {0};
  int hihat_seq[WIN_LEN] = {0};

  if (flag == 3) {
    dataKick = 0b10101010;
    dataSnare = 0b01010101;
    dataTom = 0b01010101;
    dataHiHat = 0b01010101;
  }


  // Read TINY1
  if (flag == 1) {
    Wire.requestFrom(TINY1, 2);
    dataKick = Wire.read(); // Read Kick and save to data
    dataSnare = Wire.read();
    // Flush
    while (Wire.available()){
      Wire.read();
    }

    for (int i = 0; i < 8; i++)
      kick_seq[i] = (dataKick & (1<<i)) ? 1 : 0;

    // Assign the parsed sequence
    kick.update_sequence(kick_seq, offset);

    // Snare
    for (int i = 0; i < 8; i++)
      snare_seq[i] = (dataSnare & (1<<i)) ? 1 : 0;

    // Assign the parsed sequence
    snare.update_sequence(snare_seq, offset);
  }

  
  // Read TINY2
  if (flag == 2 ) {
    Wire.requestFrom(TINY2, 2);
    dataTom = Wire.read();
    dataHiHat = Wire.read();
    // Flush
    while (Wire.available()){
      Wire.read();
    }

    //Tom
    for (int i = 0; i < 8; i++)
      tom_seq[i] = (dataTom & (1<<i)) ? 1 : 0;

    // Assign the parsed sequence
    tom.update_sequence(tom_seq, offset);

    // HiHat
    for (int i = 0; i < 8; i++)
      hihat_seq[i] = (dataHiHat & (1<<i)) ? 1 : 0;
    
    // Assign the parsed sequence
    hihat.update_sequence(hihat_seq, offset);
  }

}

void DrumManager::playDrums(int beat_idx){
  timer = 0;
  kick.play(beat_idx);
  snare.play(beat_idx);
  tom.play(beat_idx);
  hihat.play(beat_idx);
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


void DrumManager::stopDrums(){
  if(timer > 30){
    timer = 0;

    kick.stop();
    snare.stop();
    tom.stop();
    hihat.stop();
  }
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