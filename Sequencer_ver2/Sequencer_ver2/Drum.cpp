// modified: 4/19/24

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
  // resetVelocity();
}



void Drum::setVel(int midiVel)
{
  if((midiVel < VELOCITY_MIN) || midiVel > VELOCITY_MAX)
    return;

  velocity = 63 + ((midiVel*192) / 127);
  pullTime = pullTimes[velocity-63];

  velocity = 200; // DEBUG
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

// void Drum::resetVelocity()
// {
//   for (int i = 0; i < WIN_LEN; i++)
//     velocity[i] = VELOCITY_DEFAULT;
// }

void Drum::updateSequence(int *newSequence)
{
  for (int i = 0; i < WIN_LEN; i++)
    sequence[i] = newSequence[i];
}

// void Drum::updateVelocity(int *newVelocity)
// {
//   for (int i = 0; i < WIN_LEN; i++)
//     velocity[i] = newVelocity[i];
// }

void Drum::play()
{
  playTimer = 0;
  on = true;

  if (sequence[beat] && (!muted))
    analogWrite(PIN, velocity);

  // else
  //   analogWrite(PIN, 0);

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
  if ((!on) && (waitTimer >= beatDur-pullTime-HOLD_TIME))
  {
    waitTimer = 0;
    play();
  }

  // Hold
  if ((on) && (playTimer >= pullTime))
    analogWrite(PIN, HOLD_VEL);

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
