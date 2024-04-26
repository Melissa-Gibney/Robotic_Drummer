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
    // int velocity[WIN_LEN] = {0};   

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
    // void resetVelocity();  // reset the velocity to the default (60)

    void updateSequence(int *new_sequence);
    // void updateVelocity(int *new_velocity);

    void setBeatDur(int dur) { beatDur = dur; }
    void setVel(int midiVel);

    void toggleMute();

    void startBeat(int b) {waitTimer = 0; beat = b;}
    void play();
    void stop();
    void loop();

    // flag to convert the drum sequence to a binary number
    int getBinSequence();
};
#endif