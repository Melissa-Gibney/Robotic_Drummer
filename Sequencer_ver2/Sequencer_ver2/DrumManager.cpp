// modified: 5/1/24

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
  kick.setVel(velocities[KICK][beat]);
  snare.setVel(velocities[SNARE][beat]);
  tom.setVel(velocities[TOM][beat]);
  hihat.setVel(velocities[HIHAT][beat]);

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
  Wire.beginTransmission(TINY2);
  Wire.write(0b00000000);
  Wire.write(0b00000000);
  Wire.endTransmission();

  Wire.beginTransmission(TINY1);
  Wire.write(0b00000000);
  Wire.write(0b00000000);
  Wire.endTransmission();

}

void DrumManager::toggleStartStop()
{
  startStop = !startStop;
}


void DrumManager::setVelocityMode(int v)
{
  Wire.beginTransmission(TINY2);
  Wire.write(v);
  Wire.endTransmission();

  Wire.beginTransmission(TINY1);
  Wire.write(v);
  Wire.endTransmission();

  // Top left corner
  flashingStep[0] = 1;
  flashingStep[1] = 1;
}

void DrumManager::clearDrum(DrumID id)
{
  int data;

  switch(id)
  {
    case KICK:
      data = snare.getBinSequence();
      Wire.beginTransmission(TINY2);
      Wire.write(data);
      Wire.write(0b00000000);
      Wire.endTransmission();
      kick.resetSequence();
      break;

    case SNARE:
      data = kick.getBinSequence();
      Wire.beginTransmission(TINY2);
      Wire.write(0b00000000);
      Wire.write(data);
      Wire.endTransmission();
      snare.resetSequence();
      break;

    case TOM:
      data = hihat.getBinSequence();
      Wire.beginTransmission(TINY1);
      Wire.write(data);
      Wire.write(0b00000000);
      Wire.endTransmission();
      tom.resetSequence();
      break;

    case HIHAT:
      data = tom.getBinSequence();
      Wire.beginTransmission(TINY1);
      Wire.write(0b00000000);
      Wire.write(data);
      Wire.endTransmission();
      hihat.resetSequence();
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


  Wire.requestFrom(TINY2, 3);

  data1 = Wire.read();    // snare
  data2 = Wire.read();    // kick
  lastT2 = Wire.read();

  // Kick
  for (int i = (WIN_LEN - 1); i >= 0; i--)
    newKickSeq[WIN_LEN-1-i] = (data2 & (1<<i)) ? 1 : 0;

  kick.updateSequence(newKickSeq);

  // Snare
  for (int i = (WIN_LEN - 1); i >= 0; i--)
    newSnareSeq[WIN_LEN-1-i] = (data1 & (1<<i)) ? 1 : 0;
  
  snare.updateSequence(newSnareSeq);

  delay(1);
  
  Wire.requestFrom(TINY1, 3);

  data3 = Wire.read();
  data4 = Wire.read();
  lastT1 = Wire.read();

  //Tom
  for (int i = (WIN_LEN - 1); i >= 0; i--)
    newTomSeq[WIN_LEN-1-i] = (data4 & (1<<i)) ? 1 : 0;

  tom.updateSequence(newTomSeq);

  // HiHat
  for (int i = (WIN_LEN - 1); i >= 0; i--)
    newHiHatSeq[WIN_LEN-1-i] = (data3 & (1<<i)) ? 1 : 0;

  hihat.updateSequence(newHiHatSeq);


  if((lastT1 != lastT1Prev) && (lastT1 > 0) && (lastT1 < 17))
  {
    flashingStep[0] = 0;
    flashingStep[1] = 17 - lastT1;
  }

  else if((lastT2 != lastT2Prev) && (lastT2 > 0) && (lastT2 < 17))
  {
    flashingStep[0] = 1;
    flashingStep[1] = 17 - lastT2;
  }

  lastT1Prev = lastT1;
  lastT2Prev = lastT2;

}


void DrumManager::flash(int level)    // changed data numbers & tiny1/tiny2
{
  int data2 = kick.getBinSequence();
  int data1 = snare.getBinSequence();
  int data4 = tom.getBinSequence();
  int data3 = hihat.getBinSequence();

  int col, row;

  if(flashingStep[1] <= 8)
  {
    row = 0;
    col = 8 - flashingStep[1];
  }
  else
  {
    row = 1;
    col = 16 - flashingStep[1];
  }


  int flashMask = ~(1<<col);
  int flash = level<<col;

  if((flashingStep[0]==1) && (row==0))      // row 1
    data2 = (data2 & flashMask) | flash;

  else if((flashingStep[0]==1) && (row==1)) // row 2
    data1 = (data1 & flashMask) | flash;

  else if((flashingStep[0]==0) && (row==0)) // row 3
    data4 = (data4 & flashMask) | flash;

  else if((flashingStep[0]==0) && (row==1)) // row 4
    data3 = (data3 & flashMask) | flash;


  Wire.beginTransmission(TINY2);
  Wire.write(data1);
  Wire.write(data2);
  Wire.endTransmission();
  delay(1);
  Wire.beginTransmission(TINY1);
  Wire.write(data3);
  Wire.write(data4);
  Wire.endTransmission();
}


void DrumManager::setStepVelocity(int v)  // no changes
{
  if(((flashingStep[0] != 0) && (flashingStep[0] != 1)) || ((flashingStep[1] < 1) || (flashingStep[1] > 16)))
    return;

  int tiny = (flashingStep[0]) ? 0 : 1;
  int row = (flashingStep[1]-1) / 8;
  int col = flashingStep[1] - 8*(row) - 1;

  velocities[2*tiny + row][col] = v;
}

int DrumManager::getStepVelocity()  // no changes
{
  if(((flashingStep[0] != 0) && (flashingStep[0] != 1)) || ((flashingStep[1] < 1) || (flashingStep[1] > 16)))
    return;

  int tiny = (flashingStep[0]) ? 0 : 1;
  int row = (flashingStep[1]-1) / 8;
  int col = flashingStep[1] - 8*(row) - 1;

  return velocities[2*tiny + row][col];
}


void DrumManager::resetVelocity()
{
  for(int i = 0; i < N_DRUMS; i++)
    for(int j = 0; j < WIN_LEN; j++)
      velocities[i][j] = VELOCITY_DEFAULT;
}


void DrumManager::resetVelocity(DrumID drum)
{
  for(int i = 0; i < WIN_LEN; i++)
    velocities[drum][i] = VELOCITY_DEFAULT;
}