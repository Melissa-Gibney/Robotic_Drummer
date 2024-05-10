// Drum Manager Class Header File
// modified: 5/2/24

#ifndef DRUMMANAGER_H
#define DRUMMANAGER_H

#include "Drum.h"

class DrumManager
{
  private:
    Drum kick, snare, tom, hihat; // 4 Instances of Drum Class, 1 for each port

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

    void clearDrum(DrumID id); //Clear Drums

    void muteDrum(DrumID id);  // Mute Drums

    void set_vel_preset(int npreset); // Run when selecting preset (for assigning velocities)

    void flash(int level);

};
#endif