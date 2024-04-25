// modified: 4/19/24

#include "util.h"
#include "DrumManager.h"

// Constructor
DrumManager::DrumManager(int kp, int klp, int sp, int slp, int tp, int tlp, int hp, int hlp) : kick(kp, klp), snare(sp, slp), tom(tp, tlp), hihat(hp, hlp) {}


// Set tempo in ms
void DrumManager::setTempo(int ms)
{
  kick.setBeatDur(ms);
  snare.setBeatDur(ms);
  tom.setBeatDur(ms);
  hihat.setBeatDur(ms);
}


// Play current beat
void DrumManager::play(int beat)
{
  kick.setVel(1);
  snare.setVel(1);
  tom.setVel(1);
  hihat.setVel(1);

  kick.startBeat(beat);
  snare.startBeat(beat);
  tom.startBeat(beat);
  hihat.startBeat(beat);
}

void DrumManager::endBeat()
{
  kick.stop();
  snare.stop();
  tom.stop();
  hihat.stop();
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


void DrumManager::setVelocityMode(int v)
{
  Wire.beginTransmission(TINY1);
  Wire.write(v);
  Wire.endTransmission();

  Wire.beginTransmission(TINY2);
  Wire.write(v);
  Wire.endTransmission();
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

  int data1 = 0, data2 = 0, data3 = 0, data4 = 0;


  Wire.requestFrom(TINY1, 3);

  data1 = Wire.read();
  data2 = Wire.read();
  lastT1 = Wire.read();

  // Kick
  for (int i = 0; i < WIN_LEN; i++)
    newKickSeq[i] = (data1 & (1<<i)) ? 1 : 0;

  kick.updateSequence(newKickSeq);

  // Snare
  for (int i = 0; i < WIN_LEN; i++)
    newSnareSeq[i] = (data2 & (1<<i)) ? 1 : 0;
  
  snare.updateSequence(newSnareSeq);

  delay(1);
  
  Wire.requestFrom(TINY2, 3);

  data3 = Wire.read();
  data4 = Wire.read();
  lastT2 = Wire.read();

  //Tom
  for (int i = 0; i < WIN_LEN; i++)
    newTomSeq[i] = (data3 & (1<<i)) ? 1 : 0;

  tom.updateSequence(newTomSeq);

  // HiHat
  for (int i = 0; i < WIN_LEN; i++)
    newHiHatSeq[i] = (data4 & (1<<i)) ? 1 : 0;

  hihat.updateSequence(newHiHatSeq);


  if((lastT1 != lastT1Prev))
  {
    flashingStep[0] = 0;
    flashingStep[1] = lastT1;
  }

  else if(lastT2 != lastT2Prev)
  {
    flashingStep[0] = 1;
    flashingStep[1] = lastT2;
  }

  lastT1Prev = lastT1;
  lastT2Prev = lastT2;

}

// void DrumManager::refresh()
// {
//   int data1 = kick.getBinSequence();
//   int data2 = snare.getBinSequence();
//   int data3 = tom.getBinSequence();
//   int data4 = hihat.getBinSequence();

//   Wire.beginTransmission(TINY1);
//   Wire.write(data1);
//   Wire.write(data2);
//   Wire.endTransmission();
//   delay(1);
//   Wire.beginTransmission(TINY2);
//   Wire.write(data3);
//   Wire.write(data4);
//   Wire.endTransmission();
// }

void DrumManager::refresh(int tiny, int row, int col, int level)
{
  int data1 = kick.getBinSequence();
  int data2 = snare.getBinSequence();
  int data3 = tom.getBinSequence();
  int data4 = hihat.getBinSequence();

  int flashMask = ~(1<<col);
  int flash = level<<col;

  if((tiny==0) && (row==0))
    data1 = (data1 & flashMask) | flash;

  else if((tiny==0) && (row==1))
    data2 = (data2 & flashMask) | flash;

  else if((tiny==1) && (row==0))
    data3 = (data3 & flashMask) | flash;

  else if((tiny==1) && (row==1))
    data4 = (data4 & flashMask) | flash;

  Wire.beginTransmission(TINY1);
  Wire.write(data1);
  Wire.write(data2);
  Wire.endTransmission();
  delay(1);
  Wire.beginTransmission(TINY2);
  Wire.write(data3);
  Wire.write(data4);
  Wire.endTransmission();
}