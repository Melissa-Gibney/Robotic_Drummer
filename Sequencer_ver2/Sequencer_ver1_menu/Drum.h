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
    int sequence[WIN_LEN] = {0};    
    int velocity[WIN_LEN] = {0};   

    elapsedMillis playTimer;      
    int playDur = 25;   // ms

  public:
    Drum(int pin);
    
    void reset_sequence();  // reset the sequence array to 0
    void reset_velocity();  // reset the velocity to the default (60)

    void update_sequence(int *new_sequence);
    void update_velocity(int *new_velocity);

    void setPlayDur(int dur) { playDur = dur; }

    void play(int beat);
    void loop();

    // flag that drum is muted
    bool mute = 0;

    // flag to convert the drum sequence to a binary number
    int get_sequence();
};
#endif