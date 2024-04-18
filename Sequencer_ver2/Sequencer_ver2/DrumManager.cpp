// modified: 4/12/24

#include "util.h"
#include "DrumManager.h"

// Constructor
DrumManager::DrumManager(int kp, int klp, int sp, int slp, int tp, int tlp, int hp, int hlp) : kick(kp, klp), snare(sp, slp), tom(tp, tlp), hihat(hp, hlp) {}


// Set tempo in ms
void DrumManager::setTempo(int ms)
{
  kick.setPlayDur(ms/2);
  snare.setPlayDur(ms/2);
  tom.setPlayDur(ms/2);
  hihat.setPlayDur(ms/2);
}


// Play current beat
void DrumManager::play(int beat)
{
  kick.play(beat);
  snare.play(beat);
  tom.play(beat);
  hihat.play(beat);
}

// Update state, stop if needed
void DrumManager::loop()
{
  kick.loop();
  snare.loop();
  tom.loop();
  hihat.loop();
}

void DrumManager::masterReset()
{
  Wire.beginTransmission(TINY1);
  Wire.write(0b00000000);
  Wire.write(0b00000000);
  Wire.endTransmission();

  Wire.beginTransmission(TINY2);
  Wire.write(0b00000000);
  Wire.write(0b00000000);
  Wire.endTransmission();


  // ****** TODO!!! ******
  // Anything else we want to include on the reset button?? Reset tempo and velocity too??
}

void DrumManager::toggleStartStop()
{
  startStop = !startStop;
}


void DrumManager::clearDrum(DrumID id)
{
  int data;

  switch(id)
  {
    case KICK:
      data = snare.getBinSequence();
      Wire.beginTransmission(TINY1);
      Wire.write(0b00000000);
      Wire.write(data);
      Wire.endTransmission();
      break;

    case SNARE:
      data = kick.getBinSequence();
      Wire.beginTransmission(TINY1);
      Wire.write(data);
      Wire.write(0b00000000);
      Wire.endTransmission();
      break;

    case TOM:
      data = hihat.getBinSequence();
      Wire.beginTransmission(TINY2);
      Wire.write(0b00000000);
      Wire.write(data);
      Wire.endTransmission();
      break;

    case HIHAT:
      data = tom.getBinSequence();
      Wire.beginTransmission(TINY2);
      Wire.write(data);
      Wire.write(0b00000000);
      Wire.endTransmission();
      break;
  }
}


void DrumManager::muteDrum(DrumID id)
{
  switch(id)
  {
    case KICK:
      kick.toggleMute();
      break;
    case SNARE:
      snare.toggleMute();
      break;
    case TOM:
      tom.toggleMute();
      break;
    case HIHAT:
      hihat.toggleMute();
      break;
  }
}


// Query TINYs for change in pattern
void DrumManager::checkSequence(int flag)
{
  // Temp sequences
  int newKickSeq[WIN_LEN]   = {0};
  int newSnareSeq[WIN_LEN]  = {0};
  int newTomSeq[WIN_LEN]    = {0};
  int newHiHatSeq[WIN_LEN]  = {0};

  int data1 = 0, data2 = 0;

  if (flag == DUMMY) 
  {
    data1 = 0b10101010;
    data2 = 0b01010101;
  }

  else if (flag == T1) 
  {
    Wire.requestFrom(TINY1, 2);

    data1 = Wire.read();
    data2 = Wire.read();

    // Kick
    for (int i = 0; i < WIN_LEN; i++)
      newKickSeq[i] = (data1 & (1<<i)) ? 1 : 0;

    kick.updateSequence(newKickSeq);

    // Snare
    for (int i = 0; i < WIN_LEN; i++)
      newSnareSeq[i] = (data2 & (1<<i)) ? 1 : 0;
    
    snare.updateSequence(newSnareSeq);
  }
  

  else if (flag == T2 ) 
  {
    Wire.requestFrom(TINY2, 2);

    data1 = Wire.read();
    data2 = Wire.read();


    //Tom
    for (int i = 0; i < WIN_LEN; i++)
      newTomSeq[i] = (data1 & (1<<i)) ? 1 : 0;

    tom.updateSequence(newTomSeq);

    // HiHat
    for (int i = 0; i < WIN_LEN; i++)
      newHiHatSeq[i] = (data2 & (1<<i)) ? 1 : 0;

    hihat.updateSequence(newHiHatSeq);
  }
}