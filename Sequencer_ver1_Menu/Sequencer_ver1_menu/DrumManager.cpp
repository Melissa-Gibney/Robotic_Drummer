// modified: 4/12/24

#include "util.h"
#include "DrumManager.h"

// Constructor
DrumManager::DrumManager(int kp, int sp, int tp, int hp) : kick(kp), snare(sp), tom(tp), hihat(hp) {}


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

// ****** TODO!!! ******
void DrumManager::toggleStartStop()
{
  if (startStop == 0)
  {
    startStop = 1;
  }
  else
  {
    startStop = 0;
  }
}

void DrumManager::clearKick()
{
  int snare_seq = snare.get_sequence();
  Wire.beginTransmission(TINY1);
  Wire.write(0b00000000);
  Wire.write(snare_seq);
  Wire.endTransmission();

}
void DrumManager::clearSnare()
{
  int kick_seq = kick.get_sequence();
  Wire.beginTransmission(TINY1);
  Wire.write(kick_seq);
  Wire.write(0b00000000);
  Wire.endTransmission();
}
void DrumManager::clearTom()
{
  int hihat_seq = hihat.get_sequence();
  Wire.beginTransmission(TINY2);
  Wire.write(0b00000000);
  Wire.write(hihat_seq);
  Wire.endTransmission();
}
void DrumManager::clearHiHat()
{
  int tom_seq = tom.get_sequence();
  Wire.beginTransmission(TINY2);
  Wire.write(tom_seq);
  Wire.write(0b00000000);
  Wire.endTransmission();
}

void DrumManager::muteKick()
{
  // Toggle Mute -- this function will be called when button pressed
  if (kick.mute == 0)
  {
    kick.mute = 1;
    digitalWrite(MUTE_KICK_LED, HIGH);
  }
  else
  {
    kick.mute = 0;
    digitalWrite(MUTE_KICK_LED, LOW);
  }
}
void DrumManager::muteSnare()
{
  // Toggle Mute -- this function will be called when button pressed
  if (snare.mute == 0)
  {
    snare.mute = 1;
    digitalWrite(MUTE_SNARE_LED, HIGH);
  }
  else
  {
    snare.mute = 0;
    digitalWrite(MUTE_SNARE_LED, LOW);
  }
}
void DrumManager::muteTom()
{
  // Toggle Mute -- this function will be called when button pressed
  if (tom.mute == 0)
  {
    tom.mute = 1;
    digitalWrite(MUTE_TOM_LED, HIGH);
  }
  else
  {
    tom.mute = 0;
    digitalWrite(MUTE_TOM_LED, LOW);
  }
}
void DrumManager::muteHiHat()
{
  // Toggle Mute -- this function will be called when button pressed
  if (hihat.mute == 0)
  {
    hihat.mute = 1;
    digitalWrite(MUTE_HIHAT_LED, HIGH);
  }
  else
  {
    hihat.mute = 0;
    digitalWrite(MUTE_HIHAT_LED, LOW);
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