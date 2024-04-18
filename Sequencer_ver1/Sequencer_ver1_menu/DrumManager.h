// modified: 4/12/24

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

    void setTempo(int ms);

    void play(int beat);
    void loop();

    void masterReset();
    void toggleStartStop();

    int startStop;

    //Clear Drums
    void clearKick();
    void clearSnare();
    void clearTom();
    void clearHiHat();

    // Mute Drums
    void muteKick();
    void muteSnare();
    void muteTom();
    void muteHiHat();

    // Select Preset
    void set_preset(int npreset);

};
#endif