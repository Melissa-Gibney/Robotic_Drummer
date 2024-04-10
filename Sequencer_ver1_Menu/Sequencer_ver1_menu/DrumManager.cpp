// modified: 4/9/24

#include "util.h"
#include "DrumManager.h"

// Constructor
DrumManager::DrumManager(int kp, int sp, int tp, int hp) : kick(kp), snare(sp), tom(tp), hihat(hp) {}

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

    kick.update_sequence(newKickSeq);

    // Snare
    for (int i = 0; i < WIN_LEN; i++)
      newSnareSeq[i] = (data2 & (1<<i)) ? 1 : 0;
    
    snare.update_sequence(newSnareSeq);
  }
  

  else if (flag == T2 ) 
  {
    Wire.requestFrom(TINY2, 2);

    data1 = Wire.read();
    data2 = Wire.read();


    //Tom
    for (int i = 0; i < WIN_LEN; i++)
      newTomSeq[i] = (data1 & (1<<i)) ? 1 : 0;

    tom.update_sequence(newTomSeq);

    // HiHat
    for (int i = 0; i < WIN_LEN; i++)
      newHiHatSeq[i] = (data2 & (1<<i)) ? 1 : 0;

    hihat.update_sequence(newHiHatSeq);
  }
}