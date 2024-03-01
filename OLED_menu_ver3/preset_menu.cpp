// Preset Menu CPP File
// author: Hanna Berger
// last modified: 3/1/24

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
  display.drawLine(10, 24, 58, 24, SSD1306_WHITE); // pad row of pixels above inverted text
  display.drawLine(10, 24, 10, 32, SSD1306_WHITE); // pad column on pixels
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  display.setCursor(11,25);
  display.println(F("Preset 1"));
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(11,35);
  display.println(F("Preset 2"));
  display.setCursor(11,45);
  display.println(F("Preset 3"));
  display.setCursor(11,55);
  display.println(F("Preset 4"));

  if (selected_preset > 0) // If a preset is selected
  {
    if (selected_preset == 1)
    {
      display.fillCircle(5, 28, 2, SSD1306_WHITE);
      display.fillCircle(5, 38, 2, SSD1306_BLACK);
      display.fillCircle(5, 48, 2, SSD1306_BLACK);
      display.fillCircle(5, 58, 2, SSD1306_BLACK);
    }
    else if (selected_preset == 2)
    {
      display.fillCircle(5, 28, 2, SSD1306_BLACK);
      display.fillCircle(5, 38, 2, SSD1306_WHITE);
      display.fillCircle(5, 48, 2, SSD1306_BLACK);
      display.fillCircle(5, 58, 2, SSD1306_BLACK);
    }
    else if (selected_preset == 3)
    {
      display.fillCircle(5, 28, 2, SSD1306_BLACK);
      display.fillCircle(5, 38, 2, SSD1306_BLACK);
      display.fillCircle(5, 48, 2, SSD1306_WHITE);
      display.fillCircle(5, 58, 2, SSD1306_BLACK);
    }
    else
    {
      display.fillCircle(5, 28, 2, SSD1306_BLACK);
      display.fillCircle(5, 38, 2, SSD1306_BLACK);
      display.fillCircle(5, 48, 2, SSD1306_BLACK);
      display.fillCircle(5, 58, 2, SSD1306_WHITE);
    }

  }

  display.display();

}

void preset_menu::highlight_preset() // highlights preset based off preset counter
{
  if (preset_counter == 0){

    // Title
    display.clearDisplay();
    display.setCursor(5,0);
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.println(F("PRESETS!!!\n"));

    display.setTextSize(1);
    display.drawLine(10, 24, 58, 24, SSD1306_WHITE); // pad row of pixels above inverted text
    display.drawLine(10, 24, 10, 32, SSD1306_WHITE); // pad column on pixels
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    display.setCursor(11,25);
    display.println(F("Preset 1"));
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(11,35);
    display.println(F("Preset 2"));
    display.setCursor(11,45);
    display.println(F("Preset 3"));
    display.setCursor(11,55);
    display.println(F("Preset 4"));

  }

  if (preset_counter == 1){
    
    // Title
    display.clearDisplay();
    display.setCursor(5,0);
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.println(F("PRESETS!!!\n"));

    display.setTextSize(1);
    display.setCursor(11,25);
    display.println(F("Preset 1"));
    display.drawLine(10, 34, 58, 34, SSD1306_WHITE); // pad row of pixels above inverted text
    display.drawLine(10, 34, 10, 42, SSD1306_WHITE); // pad column on pixels
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text;
    display.setCursor(11,35);
    display.println(F("Preset 2"));
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(11,45);
    display.println(F("Preset 3"));
    display.setCursor(11,55);
    display.println(F("Preset 4"));
    
  }
  if (preset_counter == 2){
    // Title
    display.clearDisplay();
    display.setCursor(5,0);
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.println(F("PRESETS!!!\n"));

    display.setTextSize(1);
    display.setCursor(11,25);
    display.println(F("Preset 1"));
    display.setCursor(11,35);
    display.println(F("Preset 2"));
    display.drawLine(10, 44, 58, 44, SSD1306_WHITE); // pad row of pixels above inverted text
    display.drawLine(10, 44, 10, 52, SSD1306_WHITE); // pad column on pixels
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    display.setCursor(11,45);
    display.println(F("Preset 3"));
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(11,55);
    display.println(F("Preset 4"));

  }
  if (preset_counter == 3){
    // Title
    display.clearDisplay();
    display.setCursor(5,0);
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.println(F("PRESETS!!!\n"));

    display.setTextSize(1);
    display.setCursor(11,25);
    display.println(F("Preset 1"));
    display.setCursor(11,35);
    display.println(F("Preset 2"));
    display.setCursor(11,45);
    display.println(F("Preset 3"));
    display.drawLine(10, 54, 58, 54, SSD1306_WHITE); // pad row of pixels above inverted text
    display.drawLine(10, 54, 10, 62, SSD1306_WHITE); // pad column on pixels
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    display.setCursor(11,55);
    display.println(F("Preset 4"));
    
  }

  if (selected_preset > 0) // If a preset is selected
  {
    if (selected_preset == 1)
    {
      display.fillCircle(5, 28, 2, SSD1306_WHITE);
      display.fillCircle(5, 38, 2, SSD1306_BLACK);
      display.fillCircle(5, 48, 2, SSD1306_BLACK);
      display.fillCircle(5, 58, 2, SSD1306_BLACK);
    }
    else if (selected_preset == 2)
    {
      display.fillCircle(5, 28, 2, SSD1306_BLACK);
      display.fillCircle(5, 38, 2, SSD1306_WHITE);
      display.fillCircle(5, 48, 2, SSD1306_BLACK);
      display.fillCircle(5, 58, 2, SSD1306_BLACK);
    }
    else if (selected_preset == 3)
    {
      display.fillCircle(5, 28, 2, SSD1306_BLACK);
      display.fillCircle(5, 38, 2, SSD1306_BLACK);
      display.fillCircle(5, 48, 2, SSD1306_WHITE);
      display.fillCircle(5, 58, 2, SSD1306_BLACK);
    }
    else
    {
      display.fillCircle(5, 28, 2, SSD1306_BLACK);
      display.fillCircle(5, 38, 2, SSD1306_BLACK);
      display.fillCircle(5, 48, 2, SSD1306_BLACK);
      display.fillCircle(5, 58, 2, SSD1306_WHITE);
    }

  }

  display.display();

}

void preset_menu::select_preset() // Flashes the highlighted preset!
{
  if (preset_counter == 0)
  {
    display.setTextSize(1);
    display.drawLine(10, 24, 58, 24, SSD1306_BLACK); // pad row of pixels above inverted text
    display.drawLine(10, 24, 10, 32, SSD1306_BLACK); // pad column on pixels
    display.setTextColor(SSD1306_WHITE, SSD1306_BLACK); // Draw regular text
    display.setCursor(11,25);
    display.println(F("Preset 1"));
    display.display();
    delay(15);
    display.setTextSize(1);
    display.drawLine(10, 24, 58, 24, SSD1306_WHITE); // pad row of pixels above inverted text
    display.drawLine(10, 24, 10, 32, SSD1306_WHITE); // pad column on pixels
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    display.setCursor(11,25);
    display.println(F("Preset 1"));
    
    display.fillCircle(5, 28, 2, SSD1306_WHITE);
    display.fillCircle(5, 38, 2, SSD1306_BLACK);
    display.fillCircle(5, 48, 2, SSD1306_BLACK);
    display.fillCircle(5, 58, 2, SSD1306_BLACK);

    selected_preset = 1;

  }
  else if (preset_counter == 1)
  {
    display.setTextSize(1);
    display.drawLine(10, 34, 58, 34, SSD1306_BLACK); // pad row of pixels above inverted text
    display.drawLine(10, 34, 10, 42, SSD1306_BLACK); // pad column on pixels
    display.setTextColor(SSD1306_WHITE, SSD1306_BLACK); // Draw regular text
    display.setCursor(11,35);
    display.println(F("Preset 2"));
    display.display();
    delay(15);
    display.setTextSize(1);
    display.drawLine(10, 34, 58, 34, SSD1306_WHITE); // pad row of pixels above inverted text
    display.drawLine(10, 34, 10, 42, SSD1306_WHITE); // pad column on pixels
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    display.setCursor(11,35);
    display.println(F("Preset 2"));

    display.fillCircle(5, 28, 2, SSD1306_BLACK);
    display.fillCircle(5, 38, 2, SSD1306_WHITE);
    display.fillCircle(5, 48, 2, SSD1306_BLACK);
    display.fillCircle(5, 58, 2, SSD1306_BLACK);

    selected_preset = 2;
  }
  else if (preset_counter == 2)
  {
    display.setTextSize(1);
    display.drawLine(10, 44, 58, 44, SSD1306_BLACK); // pad row of pixels above inverted text
    display.drawLine(10, 44, 10, 52, SSD1306_BLACK); // pad column on pixels
    display.setTextColor(SSD1306_WHITE, SSD1306_BLACK); // Draw regular text
    display.setCursor(11,45);
    display.println(F("Preset 3"));
    display.display();
    delay(15);
    display.setTextSize(1);
    display.drawLine(10, 44, 58, 44, SSD1306_WHITE); // pad row of pixels above inverted text
    display.drawLine(10, 44, 10, 52, SSD1306_WHITE); // pad column on pixels
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    display.setCursor(11,45);
    display.println(F("Preset 3"));

    display.fillCircle(5, 28, 2, SSD1306_BLACK);
    display.fillCircle(5, 38, 2, SSD1306_BLACK);
    display.fillCircle(5, 48, 2, SSD1306_WHITE);
    display.fillCircle(5, 58, 2, SSD1306_BLACK);

    selected_preset = 3;
  }
  else
  {
    display.setTextSize(1);
    display.drawLine(10, 54, 58, 54, SSD1306_BLACK); // pad row of pixels above inverted text
    display.drawLine(10, 54, 10, 62, SSD1306_BLACK); // pad column on pixels
    display.setTextColor(SSD1306_WHITE, SSD1306_BLACK); // Draw regular text
    display.setCursor(11,55);
    display.println(F("Preset 4"));
    display.display();
    delay(15);
    display.setTextSize(1);
    display.drawLine(10, 54, 58, 54, SSD1306_WHITE); // pad row of pixels above inverted text
    display.drawLine(10, 54, 10, 62, SSD1306_WHITE); // pad column on pixels
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    display.setCursor(11,55);
    display.println(F("Preset 4"));
    display.fillCircle(5, 28, 2, SSD1306_BLACK);
    display.fillCircle(5, 38, 2, SSD1306_BLACK);
    display.fillCircle(5, 48, 2, SSD1306_BLACK);
    display.fillCircle(5, 58, 2, SSD1306_WHITE);


    selected_preset = 4;
  }

  display.display();

}

