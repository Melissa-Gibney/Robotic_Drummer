// Drum Manager Class Header File
// author: Hanna Berger
// modified: 3/5/24

#ifndef drumManager_h
#define drumManger_h

#include <Arduino.h>
#include "Drum.h"

class DrumManager
{
  private:
    Drum kick;
    Drum snare;
    Drum tom;
    Drum hihat;


  public:
    Drum();
    void assignDrums(Drum kk, Drum sn, Drum tm, Drum hh);
    void checkSequence();
    void playKick();
    void playSnare();
    void playTom();
    void playHiHat();

    Drum drum;

};


#endif