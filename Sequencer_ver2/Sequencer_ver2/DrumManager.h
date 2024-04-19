// modified: 4/12/24

#ifndef DRUMMANAGER_H
#define DRUMMANAGER_H

#include "Drum.h"

class DrumManager
{
  private:
    Drum kick, snare, tom, hihat;

    bool startStop = false;


  public:
    DrumManager(int kp, int klp, int sp, int slp, int tp, int tlp, int hp, int hlp);

    void checkSequence(int flag);

    void setTempo(int ms);

    void play(int beat);
    void loop();

    void masterReset();
    void toggleStartStop();

    bool isStopped() { return !startStop; }

    //Clear Drums
    void clearDrum(DrumID id);

    // Mute Drums
    void muteDrum(DrumID id);

    // Select Preset
    void set_preset(int npreset);

};
#endif