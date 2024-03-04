// Class to create a Drum Object
// author: Hanna Berger
// modified: 3/4/24


#ifndef drum_h
#define drum_h

#include <Arduino.h>
#include <Wire.h>
#include <vector>

class Drum {
  private:
    int nsteps = 8;
    int sequence[8];
    int velocity[8];

  public:
    Drum();
    void set_nsteps(int idx);
    void initialize_sequence();
    void initialize_velocity();
    void update_sequence(const int *new_sequence);
    void update_velocity(const int *new_velocity);

};

#endif