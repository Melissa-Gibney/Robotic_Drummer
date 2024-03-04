// Drum Object Class CPP FIle
// author: Hanna Berger
// modified: 3/4/24

#include "Drum.h"
#include <Arduino.h>

// constructor
Drum::Drum() {}

void Drum::set_nsteps(int n)
{
  nsteps = n;
}

void Drum::initialize_sequence()
{
  for (int i = 0; i < 8; i++){
    sequence[i] = 0;
  }
}

void Drum::initialize_velocity()
{
  for (int i = 0; i < 8; i++){
    velocity[i] = 1;
  }
}

void Drum::update_sequence(const int *new_sequence)
{
  for (int i = 0; i < 8; i++){
    sequence[i] = new_sequence[i];
  }
}

void Drum::update_velocity(const int *new_velocity)
{
  for (int i = 0; i < 8; i++){
    velocity[i] = new_velocity[i];
  }
}



