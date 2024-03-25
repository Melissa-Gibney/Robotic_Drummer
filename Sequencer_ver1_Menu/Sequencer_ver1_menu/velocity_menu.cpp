// Velocity Menu CPP File
// author: Hanna Berger
// modified: 2/26/24

#include "velocity_menu.h"
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// constructor
velocity_menu::velocity_menu() {}

// function to set the displat to the OLED screen
void velocity_menu::set_display(Adafruit_SSD1306 oled_screen)
{
  display = oled_screen;
}

// function to initialize the velocity menu
void velocity_menu::initialize_menu()
{
  display.clearDisplay();
  display.setCursor(10,0);
  
  // Title
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.println(F("Velocity!\n"));

  // Print velocity
  display.setTextSize(1);
  display.setCursor(10, 30);
  display.println(F("Velocity (in MIDI):"));
  display.setCursor(10, 40);
  display.print(velocity);
  // display.display();
}

// function called when rotary encoder is changed
void velocity_menu::update_velocity()
{
  display.clearDisplay();
  display.setCursor(10,0);
  
  // Title
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.println(F("Velocity!\n"));

  // Print velocity
  display.setTextSize(1);
  display.setCursor(10, 30);
  display.println(F("Velocity (in MIDI):"));
  display.setCursor(10, 40);
  display.print(velocity);
  display.display();
}
