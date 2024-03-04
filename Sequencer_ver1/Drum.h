// Class to create a Drum Object
// author: Hanna Berger
// modified: 3/4/24


#ifndef drum_h
#define drum_h
#include <Arduino.h>

class Drum {
  private:
    int nsteps = 8;
    int sequence[8];
    int velocity[8];

  public:
    Drum();
    void set_nsteps(int idx);
    void reset_sequence();
    void reset_velocity();
    void update_sequence(const int *new_sequence);
    void update_velocity(const int *new_velocity);
    
    // For testing!
    void print_sequence();
    void print_velocity();

};

#endif