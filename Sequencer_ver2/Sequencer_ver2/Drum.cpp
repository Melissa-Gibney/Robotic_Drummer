// modified: 4/12/24

#include "Drum.h"

// Constructor
Drum::Drum(int pin, int ledPin)
{
  this->PIN = pin;
  this->LED_PIN = ledPin;

  // Init output pin
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN, LOW);

  // Init LED pin
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Init sequences
  resetSequence();
  resetVelocity();
}



void Drum::toggleMute()
{
  muted = !muted;

  if(muted)
    digitalWrite(LED_PIN, HIGH);
  else
    digitalWrite(LED_PIN, LOW);
}



void Drum::resetSequence()
{
  for (int i = 0; i < WIN_LEN; i++)
    sequence[i] = 0;
}

void Drum::resetVelocity()
{
  for (int i = 0; i < WIN_LEN; i++)
    velocity[i] = VELOCITY_DEFAULT;
}

void Drum::updateSequence(int *newSequence)
{
  for (int i = 0; i < WIN_LEN; i++)
    sequence[i] = newSequence[i];
}

void Drum::updateVelocity(int *newVelocity)
{
  for (int i = 0; i < WIN_LEN; i++)
    velocity[i] = newVelocity[i];
}

void Drum::play(int beat)
{
  playTimer = 0;

  if (sequence[beat] && (!muted))
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

int Drum::getBinSequence()
{
  int bin_sequence = 0;
  for(int i = 0; i < 8; i++)
  {
    bin_sequence = bin_sequence | (sequence[i] << i);
  }
  return bin_sequence;
}
