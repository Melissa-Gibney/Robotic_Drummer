// Drum Object Class Header File
// author: Hanna Berger
// modified: 3/18/24


#ifndef drum_h
#define drum_h
#include <Arduino.h>
#include <Wire.h>
#include <elapsedMillis.h>
#include "util.h"

class Drum 
{
  private:
    int nsteps = MAX_LEN;
    int sequence[MAX_LEN]; // array of states (on/off) for the sequence
    int velocity[MAX_LEN]; // array of velocities for the sequence
    int solenoidPin = 54; // pin output for solenoid
    unsigned long pullTime = 0; // amount of time before beat that drum needs to actuate
    elapsedMillis drumTimer; // keep track of time elapsed between beats, restart after each hold time

  public:
    Drum();
    void set_nsteps(int n); // set the number of steps in the sequence
    void set_solenoid_pin(int n); // set the pin number of the drum's corresponding solenoid
    void set_pull_time(unsigned long n);
    elapsedMillis get_drum_timer();
    void set_drum_timer(unsigned long n);
    void reset_sequence(); // reset the sequence array to 0
    void reset_velocity(); // reset the velocity to the default (1 for now)
    void update_sequence(int *new_sequence, int offset);
    void update_velocity(int *new_velocity);

    void play(int beat_idx);
    void stop();

    int getSeqBin(int offset);
    
    // For testing!
    void print_sequence();
    void print_velocity();
};
#endif