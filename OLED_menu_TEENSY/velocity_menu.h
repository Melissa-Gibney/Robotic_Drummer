// OLED Velocity Menu Header File
// author: Hanna Berger
// modified: 2/26/24

#ifndef velocity_menu_h
#define velocity_menu_h

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class velocity_menu {
  private:
    Adafruit_SSD1306 display;

  public:
    velocity_menu();
    int velocity;
    void set_display(Adafruit_SSD1306 oled_screen);
    void initialize_menu();
    void update_velocity();
};

#endif