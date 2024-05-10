// Drum Class CPP File
// modified: 4/25/24

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
}


void Drum::setVel(int midiVel)
{
  if((midiVel < VELOCITY_MIN) || midiVel > VELOCITY_MAX) // If velocity is outside of the range don't save it!
    return;

  velocity = 63 + ((midiVel*192) / 127);
  pullTime = pullTimes[velocity-63];

}


void Drum::toggleMute()
{
  muted = !muted; // save mute state

  if(muted)
    digitalWrite(LED_PIN, HIGH); // if mute is turning on, turn on mute LED
  else
    digitalWrite(LED_PIN, LOW); // if mute is turning off, turn off mute LED
}



void Drum::resetSequence() // set the Drum's sequence to 0 within the Drum Class
{
  for (int i = 0; i < WIN_LEN; i++)
    sequence[i] = 0;
}

void Drum::updateSequence(int *newSequence) // Save a new sequence to be the Drum's sequence
{
  for (int i = 0; i < WIN_LEN; i++)
    sequence[i] = newSequence[i];
}

void Drum::play()
{
  playTimer = 0;
  on = true;

  if (sequence[beat] && (!muted))
    analogWrite(PIN, velocity);

}

void Drum::stop()
{
  // Release
  analogWrite(PIN, 0);
  on = false;
}

void Drum::loop()
{
  // Extend
  if ((!on) && (waitTimer >= beatDur-pullTime-HOLD_TIME)) // Extend after the wait timer is reached!
  {
    waitTimer = 0;
    play();
  }

  // Hold
  if ((on) && (playTimer >= pullTime))
    analogWrite(PIN, HOLD_VEL);

}

int Drum::getBinSequence() // convert a drum's sequence to binary bytes to be sent over I2C to the ATTinys
{
  int bin_sequence = 0;
  for(int i = 0; i < WIN_LEN; i++)
  {
    bin_sequence = bin_sequence | (sequence[WIN_LEN-1-i] << i);
  }
  return bin_sequence;
}
