// OLED Preset Menu Header File
// author: Hanna Berger
// modified: 2/28/24

#ifndef preset_menu_h
#define preset_menu_h

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class preset_menu {
  private:
    Adafruit_SSD1306 display; // OLED Screen
    int selected_preset = -1; // Variable to save the selected preset

  public:
    preset_menu();
    int preset_counter; // counter to keep track of highlighted preset
    void set_display(Adafruit_SSD1306 oled_screen); // assign screen to the menu class
    void initialize_menu(); // initialize menu with the default 
    void highlight_preset();
    void select_preset();
};

#endif