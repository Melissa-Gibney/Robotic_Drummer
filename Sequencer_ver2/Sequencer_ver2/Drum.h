// modified: 4/12/24

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
    int velocity[WIN_LEN] = {0};   

    elapsedMillis playTimer;      
    int playDur = 25;   // ms

    bool muted = false;

  public:
    Drum(int pin, int ledPin);
    
    void resetSequence();  // reset the sequence array to 0
    void resetVelocity();  // reset the velocity to the default (60)

    void updateSequence(int *new_sequence);
    void updateVelocity(int *new_velocity);

    void setPlayDur(int dur) { playDur = dur; }

    void toggleMute();

    void play(int beat);
    void loop();

    // flag to convert the drum sequence to a binary number
    int getBinSequence();
};
#endif