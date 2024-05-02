// modified: 5/2/24

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

    int velocities[N_DRUMS][WIN_LEN];

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
    void setStepVelocity(int v);
    int getStepVelocity();

    void resetVelocity();
    void resetVelocity(DrumID drum);

    bool isStopped() { return !startStop; }

    //Clear Drums
    void clearDrum(DrumID id);

    // Mute Drums
    void muteDrum(DrumID id);

    // Select Preset
    void set_vel_preset(int npreset);

    void flash(int level);

};
#endif