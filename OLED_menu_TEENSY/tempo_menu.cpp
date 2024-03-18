// Tempo Menu CPP File
// author: Hanna Berger
// modified: 2/26/24

#include "tempo_menu.h"
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// constructor
tempo_menu::tempo_menu() {}

// function to set the displat to the OLED screen
void tempo_menu::set_display(Adafruit_SSD1306 oled_screen)
{
  display = oled_screen;
}

// function to initialize the tempo menu
void tempo_menu::initialize_menu()
{
  display.clearDisplay();
  display.setCursor(10,0);
  
  // Title
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.println(F("Tempo!!!\n"));

  // Print Tempo
  display.setTextSize(1);
  display.setCursor(10, 30);
  display.println(F("Tempo (in BPM):"));
  display.setCursor(10, 40);
  display.print(tempo);
  display.display();
}

// function called when rotary encoder is changed
void tempo_menu::update_tempo()
{
  display.clearDisplay();
  display.setCursor(10,0);
  
  // Title
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.println(F("Tempo!!!\n"));

  // Print Tempo
  display.setTextSize(1);
  display.setCursor(10, 30);
  display.println(F("Tempo (in BPM):"));
  display.setCursor(10, 40);
  display.print(tempo);
  display.display();
}
