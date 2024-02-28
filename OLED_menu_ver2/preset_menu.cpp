// Preset Menu CPP File
// author: Hanna Berger
// modified: 2/26/24

#include "preset_menu.h"
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// constructor
preset_menu::preset_menu() {}

void preset_menu::set_display(Adafruit_SSD1306 oled_screen)
{
  display = oled_screen;
}
void preset_menu::initialize_menu()
{
  
  preset_counter = 0;
  
  display.clearDisplay();
  display.setCursor(5,0);
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.println(F("PRESETS!!!\n"));

  display.setTextSize(1);
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  display.setCursor(5,25);
  display.println(F("Preset 1"));
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(5,35);
  display.println(F("Preset 2"));
  display.setCursor(5,45);
  display.println(F("Preset 3"));
  display.setCursor(5,55);
  display.println(F("Preset 4"));
  display.display();
}

void preset_menu::highlight_preset()
{
  if (preset_counter == 0){

    // Title
    display.clearDisplay();
    display.setCursor(5,0);
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.println(F("PRESETS!!!\n"));

    display.setTextSize(1);
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    display.setCursor(5,25);
    display.println(F("Preset 1"));
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(5,35);
    display.println(F("Preset 2"));
    display.setCursor(5,45);
    display.println(F("Preset 3"));
    display.setCursor(5,55);
    display.println(F("Preset 4"));
    display.display();

  }

  if (preset_counter == 1){
    
    // Title
    display.clearDisplay();
    display.setCursor(5,0);
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.println(F("PRESETS!!!\n"));

    display.setTextSize(1);
    display.setCursor(5,25);
    display.println(F("Preset 1"));
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text;
    display.setCursor(5,35);
    display.println(F("Preset 2"));
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(5,45);
    display.println(F("Preset 3"));
    display.setCursor(5,55);
    display.println(F("Preset 4"));
    display.display();
    
  }
  if (preset_counter == 2){
    // Title
    display.clearDisplay();
    display.setCursor(5,0);
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.println(F("PRESETS!!!\n"));

    display.setTextSize(1);
    display.setCursor(5,25);
    display.println(F("Preset 1"));
    display.setCursor(5,35);
    display.println(F("Preset 2"));
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    display.setCursor(5,45);
    display.println(F("Preset 3"));
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(5,55);
    display.println(F("Preset 4"));
    display.display();

  }
  if (preset_counter == 3){
    // Title
    display.clearDisplay();
    display.setCursor(5,0);
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.println(F("PRESETS!!!\n"));

    display.setTextSize(1);
    display.setCursor(5,25);
    display.println(F("Preset 1"));
    display.setCursor(5,35);
    display.println(F("Preset 2"));
    display.setCursor(5,45);
    display.println(F("Preset 3"));
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    display.setCursor(5,55);
    display.println(F("Preset 4"));
    display.display();
    
  }
}

