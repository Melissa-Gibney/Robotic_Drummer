// modified: 4/9/24

#include "Drum.h"

// Constructor
Drum::Drum(int pin)
{
  this->PIN = pin;

  // Init output pin
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN, LOW);

  // Init sequences
  reset_sequence();
  reset_velocity();
}


void Drum::reset_sequence()
{
  for (int i = 0; i < WIN_LEN; i++)
    sequence[i] = 0;
}

void Drum::reset_velocity()
{
  for (int i = 0; i < WIN_LEN; i++)
    velocity[i] = 60;
}

void Drum::update_sequence(int *new_sequence)
{
  for (int i = 0; i < WIN_LEN; i++)
    sequence[i] = new_sequence[i];
}

void Drum::update_velocity(int *new_velocity)
{
  for (int i = 0; i < WIN_LEN; i++)
    velocity[i] = new_velocity[i];
}

void Drum::play(int beat)
{
  playTimer = 0;

  if (sequence[beat])
    analogWrite(PIN, 255);

}

void Drum::loop()
{
  if (playTimer >= playDur)
  {
    analogWrite(PIN, 0);
    playTimer = 0;
  }
}
