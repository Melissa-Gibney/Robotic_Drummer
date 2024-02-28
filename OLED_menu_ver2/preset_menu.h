// OLED Preset Menu Header File
// author: Hanna Berger
// modified: 2/26/24

#ifndef preset_menu_h
#define preset_menu_h

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class preset_menu {
  private:
    Adafruit_SSD1306 display;

  public:
    preset_menu();
    int preset_counter;
    void set_display(Adafruit_SSD1306 oled_screen);
    void initialize_menu();
    void highlight_preset();
};

#endif