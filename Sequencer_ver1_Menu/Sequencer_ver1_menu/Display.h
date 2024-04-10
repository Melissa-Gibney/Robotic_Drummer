// updated 4/10/24

#ifndef DISPLAY_H
#define DISPLAY_H

#include "util.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Page
{
  protected:
    Adafruit_SSD1306 display;

  public:
    Page(Adafruit_SSD1306 & d)
    {
      this->display = d;
    }

    virtual void drawPage();

    virtual void rotaryCW();
    virtual void rotaryCCW();
    virtual void rotaryPress();
};



class TempoPage : public Page 
{
  private:
    const int tempoDefault = 120;
    int tempo;

  public:
    TempoPage(Adafruit_SSD1306 & d) : Page(d)
    {
      tempo = tempoDefault;
    }

    void drawPage();

    void rotaryCW();
    void rotaryCCW();
    void rotaryPress();

};



class VelocityPage : public Page 
{
  private:
    const int velocityDefault = 60;
    int velocity;

  public:
    VelocityPage(Adafruit_SSD1306 & d) : Page(d)
    {
      velocity = velocityDefault;
    }

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
    PresetPage(Adafruit_SSD1306 & d) : Page(d) {}

    void drawPage();

    void rotaryCW();
    void rotaryCCW();
    void rotaryPress();

};



class DisplayManager 
{
  private:
    Adafruit_SSD1306 display;

    static const int nPages = 3;
    int page = 0;
    Page * pages[nPages];
    

  public:
    DisplayManager();
    void init();

    void movePage(int dir);

    void rotaryCW();
    void rotaryCCW();
    void rotaryPress();

};

#endif