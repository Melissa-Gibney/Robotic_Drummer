// OLED Tempo Menu Header File
// author: Hanna Berger
// modified: 2/26/24

#ifndef tempo_menu_h
#define tempo_menu_h

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class tempo_menu {
  private:
    Adafruit_SSD1306 display;

  public:
    tempo_menu();
    int tempo;
    void set_display(Adafruit_SSD1306 oled_screen);
    void initialize_menu();
    void update_tempo();
};

#endif