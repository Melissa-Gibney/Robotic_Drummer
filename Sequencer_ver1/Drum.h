// Drum Object Class Header File
// author: Hanna Berger
// modified: 3/4/24


#ifndef drum_h
#define drum_h
#include <Arduino.h>

class Drum {
  private:
    int nsteps = 8;
    int sequence[8]; // array of states (on/off) for the sequence
    int velocity[8]; // array of velocities for the sequence

  public:
    Drum();
    void set_nsteps(int idx); // set the number of steps in the sequence
    void reset_sequence(); // reset the sequence array to 0
    void reset_velocity(); // reset the velocity to the default (1 for now)
    void update_sequence(const int *new_sequence);
    void update_velocity(const int *new_velocity);
    
    // For testing!
    void print_sequence();
    void print_velocity();

};

#endif