// Drum Class Header File
// modified: 4/25/24

#ifndef DRUM_H
#define DRUM_H

#include "util.h"
#include <Arduino.h>
#include <Wire.h>
#include <elapsedMillis.h>

class Drum 
{
  private:
    int PIN = -1;
    int LED_PIN = -1;
    int sequence[WIN_LEN] = {0};     

    elapsedMillis playTimer;     
    elapsedMillis waitTimer; 
    int beatDur = 25;   // ms
    int beat = 0;

    int velocity = 0; // of 255
    int pullTime = 0;

    bool muted = false;
    bool on = false;

  public:
    Drum(int pin, int ledPin);
    
    void resetSequence();  // reset the sequence array to 0

    void updateSequence(int *new_sequence);

    void setBeatDur(int dur) { beatDur = dur; } // Set duration of a beat
    void setVel(int midiVel); // Set current velocity

    void toggleMute();

    void startBeat(int b) {waitTimer = 0; beat = b;}
    void play();
    void stop();
    void loop();

    // flag to convert the drum sequence to a binary number
    int getBinSequence();
};
#endif