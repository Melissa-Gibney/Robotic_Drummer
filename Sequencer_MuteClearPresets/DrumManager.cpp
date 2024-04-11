// Drum Manager Class CPP FIle
// author: Hanna Berger
// modified: 3/18/24

#include "DrumManager.h"
#include "Drum.h"
#include <Arduino.h>
#include <Wire.h>

// I2C addresses for the Tinys
#define TINY1 0x2A
#define TINY2 0x2B

// For Mute LEDS
#define MuteKickLED 41
#define MuteSnareLED 40
#define MuteTomLED 39
#define MuteHiHatLED 38

int preset1[4][8]{
 {1, 0, 1, 0, 1, 0, 1, 0},
 {0, 1, 0, 1, 0, 1, 0, 1},
 {0, 0, 0, 0, 0, 0, 1, 1},
 {1, 1, 0, 1, 1, 1, 0, 0}
};

DrumManager::DrumManager()
{

}

void DrumManager::assignDrums(Drum *kk, Drum *sn, Drum *tm, Drum *hh)
{
  kick = *kk;
  snare = *sn;
  tom = *tm;
  hihat = *hh;
}

void DrumManager::assignSolenoids(int kickPin, int tomPin, int snarePin, int hihatPin)
{
  kick.set_solenoid_pin(kickPin);
  tom.set_solenoid_pin(tomPin);
  snare.set_solenoid_pin(snarePin);
  hihat.set_solenoid_pin(hihatPin);
}

Drum DrumManager::getKick()
{
  return kick;
}

Drum DrumManager::getTom()
{
  return tom;
}

Drum DrumManager::getSnare()
{
  return snare;
}

Drum DrumManager::getHiHat()
{
  return hihat;
}

// Check for change in the sequence
void DrumManager::checkSequence(int flag)
{
  // Read in sequences from button matrix and parse them here!
  // Row 1 Address 0x2A - byte 1
  // Row 2 Address 0x2A - byte 2
  // Row 3 Address 0x2B - byte 1
  // Row 4 Address 0x2B - byte 2
  int kick_seq[8];
  int snare_seq[8];
  int tom_seq[8];
  int hihat_seq[8];

  if (flag == 3) {
    int data = 0b10101010;
    int dataSnare = 0b01010101;
    int dataTom = 0b01010101;
    int dataHiHat = 0b01010101;
  }

  // if (flag == 1) {

  //   //int data = 0b10101010;
  //   //int dataSnare = 0b01010101;
  //   Wire.requestFrom(TINY1, 2);
  //   int data = Wire.read(); // Read Kick and save to data
  //   int dataSnare = Wire.read();

  // }

  // if (flag == 2){
  //   Wire.requestFrom(TINY2, 2);
  //   int dataTom = Wire.read();
  //   int dataHiHat = Wire.read();


  // }

  // Request Kick and Snare Data from TINY 1
  //int data = 0b10101010;
  //int dataSnare = 0b01010101;
  // Wire.requestFrom(TINY1, 2);
  // data = Wire.read(); // Read Kick and save to data
  // dataSnare = Wire.read();

  // while (Wire.available()){
  //   Wire.read();
  // }
  // Now Request from TINY 2 to get Tom and HiHat Data
  //Wire.requestFrom(TINY2, 2);
  //int dataTom = Wire.read();
  //int dataHiHat = Wire.read();
  
  
  // Kick
  //int data = 0b10101010; // dummy for now will eventually be read from the tinys

  if (flag == 1) {
    Wire.requestFrom(TINY1, 2);
    int data, dataSnare;

    if(Wire.available()){
      data = Wire.read(); // Read Kick and save to data
      dataSnare = Wire.read();
    }
    // while (Wire.available())
    //   Wire.read();
  


    for (int i = 0; i < 8; i++)
    {
      if (data & (1<<i))
      {
        kick_seq[i] = 1;
        //Serial.print(1);
      }
      else
      {
        kick_seq[i] = 0;
        //Serial.print(0);
      }
    }
    // Assign the parsed sequence
    kick.update_sequence(kick_seq);
    //kick.print_sequence();

    // Snare
    for (int i = 0; i < 8; i++)
    {
      if (dataSnare & (1<<i))
      {
        snare_seq[i] = 1;
      }
      else
      {
        snare_seq[i] = 0;
      }
    }
    // Assign the parsed sequence
    snare.update_sequence(snare_seq);
  }
  
  
  // data = Wire.read(); // assign Tom sequence to data

  if (flag == 2 ) {

    Wire.requestFrom(TINY2, 2);
    int dataTom, dataHiHat;
    if(Wire.available()){
      dataTom = Wire.read();
      dataHiHat = Wire.read();
    }
    // while (Wire.available())
    //   Wire.read();
  


    
    

  //Tom
  //data = 0b00011001; // dummy for now will eventually be read from the tinys
  // Serial.print(dataTom);
  for (int i = 0; i < 8; i++)
  {
    if (dataTom & (1<<i))
    {
      tom_seq[i] = 1;
    }
    else
    {
      tom_seq[i] = 0;
    }
  }
  // Assign the parsed sequence
  tom.update_sequence(tom_seq);

  // HiHat
  //data = 0b01101101; // dummy for now will eventually be read from the tinys
  //data = Wire.read(); // read from TINY 2 byte 2 to get hihat sequence
  for (int i = 0; i < 8; i++)
  {
    if (dataHiHat & (1<<i))
    {
      hihat_seq[i] = 1;
    }
    else
    {
      hihat_seq[i] = 0;
    }
  }
  // Assign the parsed sequence
  hihat.update_sequence(hihat_seq);
  }
}



void DrumManager::playKick(int beat_idx)
{
  if (kick.mute != 1)
  {
    kick.play(beat_idx);
  }
}
void DrumManager::playSnare(int beat_idx)
{
  if (snare.mute != 1)
  {
    snare.play(beat_idx);
  }
}
void DrumManager::playTom(int beat_idx)
{
  if (tom.mute != 1)
  {
    tom.play(beat_idx);
  }
}
void DrumManager::playHiHat(int beat_idx)
{
  if (hihat.mute != 1)
  {
    hihat.play(beat_idx);
  }
}

void DrumManager::stopKick()
{
  kick.stop();
}
void DrumManager::stopSnare()
{
  snare.stop();
}
void DrumManager::stopTom()
{
  tom.stop();
}
void DrumManager::stopHiHat()
{
  hihat.stop();
}

void DrumManager::clearKick()
{
  // reset kick sequence in the manager -- will be called when clear button pressed
  //kick.reset_sequence();
  int snare_seq = snare.get_sequence();
  // TODO reset sequence on matrix through Tinys-- do we even need to run reset sequence then??? Since check sequence will read it?
  Wire.beginTransmission(TINY1);
  Wire.write(0b00000000);
  Wire.write(snare_seq);
  Wire.endTransmission();

}
void DrumManager::clearSnare()
{
  // reset snare sequence in the manager -- will be called when clear button pressed
  //snare.reset_sequence();
  int kick_seq = kick.get_sequence();
  // TODO reset sequence on matrix through Tinys
  Wire.beginTransmission(TINY1);
  Wire.write(kick_seq);
  Wire.write(0b00000000);
  Wire.endTransmission();
}
void DrumManager::clearTom()
{
  // reset tom sequence in the manager -- will be called when clear button pressed
  //tom.reset_sequence();
  int hihat_seq = hihat.get_sequence();
  // TODO reset sequence on matrix through Tinys
  Wire.beginTransmission(TINY2);
  Wire.write(0b00000000);
  Wire.write(hihat_seq);
  Wire.endTransmission();
}
void DrumManager::clearHiHat()
{
  // reset hihat sequence in the manager -- will be called when clear button pressed
  //hihat.reset_sequence();
  int tom_seq = tom.get_sequence();
  // TODO reset sequence on matrix through Tinys
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
    digitalWrite(MuteKickLED, HIGH);
  }
  else
  {
    kick.mute = 0;
    digitalWrite(MuteKickLED, LOW);
  }
}
void DrumManager::muteSnare()
{
  // Toggle Mute -- this function will be called when button pressed
  if (snare.mute == 0)
  {
    snare.mute = 1;
    //digitalWrite(MuteSnareLED, HIGH);
  }
  else
  {
    snare.mute = 0;
    //digitalWrite(MuteSnareLED, LOW);
  }
}
void DrumManager::muteTom()
{
  // Toggle Mute -- this function will be called when button pressed
  if (tom.mute == 0)
  {
    tom.mute = 1;
    //digitalWrite(MuteTomLED, HIGH);
  }
  else
  {
    tom.mute = 0;
    //digitalWrite(MuteTomLED, LOW);
  }
}
void DrumManager::muteHiHat()
{
  // Toggle Mute -- this function will be called when button pressed
  if (hihat.mute == 0)
  {
    hihat.mute = 1;
    digitalWrite(MuteHiHatLED, HIGH);
  }
  else
  {
    hihat.mute = 0;
    //digitalWrite(MuteHiHatLED, LOW);
  }
}

void DrumManager::setDrumTimers(unsigned long kickTime, unsigned long tomTime, unsigned long snareTime, unsigned long hihatTime)
{
  kick.set_drum_timer(kickTime);
  tom.set_drum_timer(tomTime);
  snare.set_drum_timer(snareTime);
  hihat.set_drum_timer(hihatTime);
}

void DrumManager::set_preset(int npreset)
{
  // Do we want presets stored as global arrays???
  // Or do we want them read in from a text file???
  
  //TODO send the presets to the Tinys
  //Check sequence should then pick up on the changes
  if (npreset == 1){
    //Dummy Preset
    int data = 0b10101010;
    int dataSnare = 0b01010101;
    int dataTom = 0b01010101;
    int dataHiHat = 0b01010101;

    Wire.beginTransmission(TINY1);
    Wire.write(data);
    Wire.write(dataSnare);
    Wire.endTransmission(TINY1);

    Wire.beginTransmission(TINY2);
    Wire.write(dataTom);
    Wire.write(dataHiHat);
    Wire.endTransmission(TINY2);

  }

  if (npreset == 2){
    //Dummy Preset
    int data = 0b00111100;
    int dataSnare = 0b11001101;
    int dataTom = 0b11011101;
    int dataHiHat = 0b10010011;

    Wire.beginTransmission(TINY1);
    Wire.write(data);
    Wire.write(dataSnare);
    Wire.endTransmission(TINY1);

    Wire.beginTransmission(TINY2);
    Wire.write(dataTom);
    Wire.write(dataHiHat);
    Wire.endTransmission(TINY2);

  }

}
// // Check for change in the sequence
// void DrumManager::checkFullSequence(int kickData, int tomData, int snareData, int hihatData)
// {
//   // Read in sequences from button matrix and parse them here!
//   // Row 1 Address 0x2A - byte 1
//   // Row 2 Address 0x2A - byte 2
//   // Row 3 Address 0x2B - byte 1
//   // Row 4 Address 0x2B - byte 2

//   int kick_seq[8];
//   int snare_seq[8];
//   int tom_seq[8];
//   int hihat_seq[8];

//   // Kick
//   int data = kickData; // dummy for now will eventually be read from the tinys
//   for (int i = 0; i < 8; i++)
//   {
//     if ((1<<i) & (data & (1<<i)))
//     {
//       kick_seq[i] = 1;
//     }
//     else
//     {
//       kick_seq[i] = 0;
//     }
//   }
//   // Assign the parsed sequence
//   kick.update_sequence(kick_seq);

//   // Snare
//   data = snareData; // dummy for now will eventually be read from the tinys
//   for (int i = 0; i < 8; i++)
//   {
//     if ((1<<i) & (data & (1<<i)))
//     {
//       snare_seq[i] = 1;
//     }
//     else
//     {
//       snare_seq[i] = 0;
//     }
//   }
//   // Assign the parsed sequence
//   snare.update_sequence(snare_seq);

//   // Tom
//   data = tomData; // dummy for now will eventually be read from the tinys
//   for (int i = 0; i < 8; i++)
//   {
//     if ((1<<i) & (data & (1<<i)))
//     {
//       tom_seq[i] = 1;
//     }
//     else
//     {
//       tom_seq[i] = 0;
//     }
//   }
//   // Assign the parsed sequence
//   tom.update_sequence(tom_seq);

//   // HiHat
//   data = hihatData; // dummy for now will eventually be read from the tinys
//   for (int i = 0; i < 8; i++)
//   {
//     if ((1<<i) & (data & (1<<i)))
//     {
//       hihat_seq[i] = 1;
//     }
//     else
//     {
//       hihat_seq[i] = 0;
//     }
//   }
//   // Assign the parsed sequence
//   hihat.update_sequence(hihat_seq);
// }

// // Check for change in one drum's sequence
// void DrumManager::checkSingleSequence(int newData, int drumIndex)
// {
//   int new_seq[8];

//   int data = newData; // dummy for now will eventually be read from the tinys
//   for (int i = 0; i < 8; i++)
//   {
//     if ((1<<i) & (data & (1<<i)))
//     {
//       new_seq[i] = 1;
//     }
//     else
//     {
//       new_seq[i] = 0;
//     }
//   }

