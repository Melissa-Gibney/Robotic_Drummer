// modified: 4/9/24

#ifndef DRUMMANAGER_H
#define DRUMMANAGER_H

#include "Drum.h"

class DrumManager
{
  private:
    Drum kick, snare, tom, hihat;


  public:
    DrumManager(int kp, int sp, int tp, int hp);

    void checkSequence(int flag);
    void play(int beat);
    void loop();

};
#endif