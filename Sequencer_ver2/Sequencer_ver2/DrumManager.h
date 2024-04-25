// modified: 4/19/24

#ifndef DRUMMANAGER_H
#define DRUMMANAGER_H

#include "Drum.h"

class DrumManager
{
  private:
    Drum kick, snare, tom, hihat;

    int lastT1 = -1, lastT2 = -1, lastT1Prev = -1, lastT2Prev = -1;
    int flashingStep[2] = {0,0};

    bool startStop = true;

  public:
    DrumManager(int kp, int klp, int sp, int slp, int tp, int tlp, int hp, int hlp);

    void checkSequence(int flag);
    int * getFlashingStep() { return flashingStep; }

    void setTempo(int ms);

    void play(int beat);
    void endBeat();
    void loop();

    void masterReset();
    void toggleStartStop();
    void setVelocityMode(int v);

    bool isStopped() { return !startStop; }

    //Clear Drums
    void clearDrum(DrumID id);

    // Mute Drums
    void muteDrum(DrumID id);

    // Select Preset
    void set_preset(int npreset);

    // void refresh();
    void refresh(int tiny, int row, int col, int level);

};
#endif