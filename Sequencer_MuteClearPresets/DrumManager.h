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
    void assignSolenoids(int kickPin, int tomPin, int snarePin, int hihatPin);
    Drum getKick();
    Drum getTom();
    Drum getSnare();
    Drum getHiHat();
    void setDrumTimers(unsigned long kickTime, unsigned long tomTime, unsigned long snareTime, unsigned long hihatTime);
    void checkSequence(int flag);
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
    void printHiHatSequence(){
      hihat.print_sequence();
    }

    // Play Drums
    void playKick(int beat_idx);
    void playSnare(int beat_idx);
    void playTom(int beat_idx);
    void playHiHat(int beat_idx);

    //Stop Droms
    void stopKick();
    void stopTom();
    void stopSnare();
    void stopHiHat();

    //Mute and Clear Drums
    void clearKick();
    void clearSnare();
    void clearTom();
    void clearHiHat();

    void muteKick();
    void muteSnare();
    void muteTom();
    void muteHiHat();

};
#endif