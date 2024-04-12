// Drum Object Class CPP FIle
// author: Hanna Berger
// modified: 3/18/24

#include "Drum.h"
#include <Arduino.h>
#include <Wire.h>

// constructor
Drum::Drum()
{
  reset_sequence();
  reset_velocity();
}

void Drum::set_nsteps(int n)
{
  nsteps = n;
}

void Drum::set_solenoid_pin(int n)
{
  solenoidPin = n;
}

elapsedMillis Drum::get_drum_timer()
{
  return drumTimer;
}

void Drum::set_drum_timer(unsigned long n)
{
  drumTimer = n;
}

void Drum::reset_sequence()
{
  for (int i = 0; i < 8; i++){
    sequence[i] = 0;
  }
}

void Drum::reset_velocity()
{
  for (int i = 0; i < 8; i++){
    velocity[i] = 1;
  }
}

void Drum::update_sequence(int *new_sequence)
{
  for (int i = 0; i < 8; i++){
    sequence[i] = new_sequence[i];
  }
}

void Drum::update_velocity(int *new_velocity)
{
  for (int i = 0; i < 8; i++){
    velocity[i] = new_velocity[i];
  }
}

void Drum::play(int beat_idx/*, unsigned long holdTime, unsigned long beatTime*/)
{
  if (sequence[beat_idx] == 1)
  {
    // unsigned long timeBeforeBeat = beatTime - holdTime;
    // unsigned long timeAfterBeat = beatTime + holdTime;

    /*
    Set the drum timer for each drum in the main loop to equal the hold time whenever it reaches the hold time
    In this method, actuate the drum when the timer equals the beatTime
    Set solenoid to low when drumTimer = timeAfterBeat;
    */
    
    // Write Pin high!

    analogWrite(solenoidPin, 63 + ((velocity[beat_idx]*192) / 127 ));
  }
}

void Drum::stop()
{
  analogWrite(solenoidPin, 0);
}

// For testing!
void Drum::print_sequence()
{
  for (int i = 0; i < 8; i++){
    Serial.println(sequence[i]);
  }
}

