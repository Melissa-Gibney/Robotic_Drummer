// updated 4/24/24

#ifndef DISPLAY_H
#define DISPLAY_H

#include "util.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Page
{
  protected:
    Adafruit_SSD1306 * display;

  public:
    Page(Adafruit_SSD1306 * d)
    {
      display = d;
    }

    virtual void setVal(int);
    virtual int getVal();

    virtual void drawPage();

    virtual void rotaryCW();
    virtual void rotaryCCW();
    virtual void rotaryPress();
};



class TempoPage : public Page 
{
  private:
    int tempo;

  public:
    TempoPage(Adafruit_SSD1306 * d) : Page(d), tempo(TEMPO_DEFAULT) {}

    void setVal(int t) { tempo = t; }
    int getVal() {}

    void drawPage();

    void rotaryCW(){};
    void rotaryCCW(){};
    void rotaryPress(){};

};



class VelocityPage : public Page 
{
  private:
    int velocity;

  public:
    VelocityPage(Adafruit_SSD1306 * d) : Page(d), velocity(VELOCITY_DEFAULT) {}

    void setVal(int v){ velocity = v; }
    int getVal() { return velocity; }

    void drawPage();

    void rotaryCW();
    void rotaryCCW();
    void rotaryPress();

};



class PresetPage : public Page 
{
  private:
    const int nPresets = 4;
    int selectedPreset = -1;
    int preset = 0;

  public:
    PresetPage(Adafruit_SSD1306 * d) : Page(d) {}

    void setVal(int){}
    int getVal() {}

    void drawPage();

    void rotaryCW();
    void rotaryCCW();
    void rotaryPress();

};



class DisplayManager 
{
  private:
    Adafruit_SSD1306 display;
    enum pageNames {PRESETS, TEMPO, VELOCITY};

    static const int nPages = 3;
    int page = 0;
    Page** pages = new Page* [nPages];
    

  public:
    DisplayManager();
    void init();

    void setTempo(int bpm);
    void setVel(int v);
    int getVel() { return pages[VELOCITY]->getVal(); }

    void movePage(int dir);
    void rotaryCW();
    void rotaryCCW();
    void rotaryPress();

    int getPage() { return page; }

};

#endif