// Drum Object Class Header File
// author: Hanna Berger
// modified: 3/18/24


#ifndef drum_h
#define drum_h
#include <Arduino.h>
#include <Wire.h>
#include <elapsedMillis.h>

class Drum 
{
  private:
    int nsteps = 8;
    int sequence[8]; // array of states (on/off) for the sequence
    int velocity[8]; // array of velocities for the sequence
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
    void update_sequence(int *new_sequence);
    void update_velocity(int *new_velocity);

    void play(int beat_idx);
    void stop();
    
    // For testing!
    void print_sequence();
    void print_velocity();

    // flag that drum is muted
    bool mute = 0;

    // flag to convert the drum sequence to a binary number
    int get_sequence();

};
#endif