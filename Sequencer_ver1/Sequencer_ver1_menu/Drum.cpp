// modified: 4/12/24

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

  if (sequence[beat] && (mute != 1))
    analogWrite(PIN, 255);

  else
    analogWrite(PIN, 0);

}

void Drum::loop()
{
  if (playTimer >= playDur)
  {
    analogWrite(PIN, 0);
    playTimer = 0;
  }
}

int Drum::get_sequence()
{
  int bin_sequence = 0;
  for(int i = 0; i < 8; i++)
  {
    bin_sequence = bin_sequence | (sequence[i] << i);
  }
  return bin_sequence;
}
