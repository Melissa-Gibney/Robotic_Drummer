// Drum Manager Class Header File
// author: Hanna Berger
// modified: 3/18/24

#ifndef drumManager_h
#define drumManger_h

#include <Arduino.h>
#include "Drum.h"
#include <Wire.h>

class DrumManager
{
  private:
    Drum kick;
    Drum snare;
    Drum tom;
    Drum hihat;


  public:
    DrumManager();
    void assignDrums(Drum *kk, Drum *sn, Drum *tm, Drum *hh);
    void checkSequence();
    void checkFullSequence(int kickData, int tomData, int snareData, int hihatData);
    void checkSingleSequence(int newData, int drumIndex);

    // Print Sequence Functions
    void printKickSequence(){
      kick.print_sequence();
    }
    void printSnareSequence(){
      snare.print_sequence();
    }
    void printTomSequence(){
      tom.print_sequence();
    }
    void printHihatSequence(){
      hihat.print_sequence();
    }

    // Play Drums
    void playKick(int beat_idx);
    void playSnare(int beat_idx);
    void playTom(int beat_idx);
    void playHiHat(int beat_idx);

};


#endif