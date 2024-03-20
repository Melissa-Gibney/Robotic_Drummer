// OLED Screen Basic Menu Version 3-- Using Classes for Each Page with separate rotary encoders
// Author: Hanna Berger
// Last Modified: 3/1/2024

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "tempo_menu.h"
#include "preset_menu.h"
#include "velocity_menu.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);                                                

// Variable Declarations
// Preset Rotary Encoder
int ROTARY_a = 30;
int ROTARY_b = 29;
int ROTARY_button = 28;
int ROTARY_state_a = 1;
int ROTARY_state_b = 1;
int ROTARY_state_prev = 1;
int ROTARY_state_button;
int ROTARY_state_button_prev = 1;

// Tempo Rotary Encoder
int ROT_tempo_a = 34;
int ROT_tempo_b = 33;
int ROT_tempo_button = 32;
int ROT_tempo_state_a = 1;
int ROT_tempo_state_b = 1;
int ROT_tempo_state_prev = 1;
int ROT_tempo_state_button;
int ROT_tempo_state_button_prev = 1;

int page_counter = 0; // for moving between pages

// Buttons
int BUTTON1 = 50;
int BUTTON2 = 51;
int b1state;
int b2state;
int prevb1state = 0;
int prevb2state = 0;

// declare objects for the pages
tempo_menu tempo_display;
preset_menu preset_display;
velocity_menu velocity_display;

// Function
void print_page(int counter);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // pinmode buttons and LEDs
  pinMode(BUTTON1,INPUT);
  pinMode(BUTTON2,INPUT);

  // pinmodes for rotary encoders
  pinMode(ROTARY_a, INPUT);
  pinMode(ROTARY_b, INPUT);
  pinMode(ROTARY_button, INPUT_PULLUP);

  pinMode(ROT_tempo_a, INPUT);
  pinMode(ROT_tempo_b, INPUT);
  pinMode(ROT_tempo_button, INPUT_PULLUP);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  //display.drawPixel(10, 10, SSD1306_WHITE);
  //display.drawCircle(64, 32, 35, SSD1306_WHITE);
  display.fillCircle(64, 32, 30, SSD1306_WHITE);
  display.setTextSize(1);
  display.setTextColor(SSD1306_BLACK);
  display.setCursor(35, 30);
  display.println(F("Welcome...\n"));

  display.fillCircle(5, 5, 5, SSD1306_WHITE);
  display.drawCircle(122, 5, 5, SSD1306_WHITE);
  display.fillCircle(122, 58, 5, SSD1306_WHITE);
  display.drawCircle(5, 58, 5, SSD1306_WHITE);

  display.display();
  delay(3000);
  display.clearDisplay();


  tempo_display.set_display(display);
  preset_display.set_display(display);
  velocity_display.set_display(display);

  tempo_display.tempo = 120;
  velocity_display.velocity = 60;
  preset_display.preset_counter = 0;
  
  print_page(page_counter);

}

void loop() {
  // put your main code here, to run repeatedly:
  // read button states
  b1state = digitalRead(BUTTON1);
  b2state = digitalRead(BUTTON2);

  // To turn pages
  if (b1state && !prevb1state){
    page_counter++;
    page_counter = page_counter % 3;
    print_page(page_counter);
  }

  if (b2state && !prevb2state){
    page_counter--;
    if (page_counter == -1)
    {
      page_counter = 2;
    }
    page_counter = page_counter % 3;
    print_page(page_counter);
  }

  // read rotary encoder states
  ROTARY_state_a = digitalRead(ROTARY_a);
  ROTARY_state_b = digitalRead(ROTARY_b);
  ROTARY_state_button = digitalRead(ROTARY_button);
  ROT_tempo_state_a = digitalRead(ROT_tempo_a);
  ROT_tempo_state_b = digitalRead(ROT_tempo_b);
  ROT_tempo_state_button = digitalRead(ROT_tempo_button);

  
  //Check for button press
  if(!ROTARY_state_button && ROTARY_state_button_prev){
    
    // if(page_counter == 1) // tempo page
    // {
    //   tempo_display.tempo = 120;
    //   tempo_display.update_tempo();
    // }
    
    if(page_counter == 2) // velocity page
    {
      velocity_display.velocity = 60;
      velocity_display.update_velocity();
    }

    else if(page_counter == 0) // presets page
    {
      preset_display.select_preset(); // select preset
    }

  }

  //Check for button press
  if(!ROT_tempo_state_button && ROT_tempo_state_button_prev){
    
    tempo_display.tempo = 120;
    tempo_display.update_tempo();
  
  }


  //Check for clock change
  if(ROTARY_state_a != ROTARY_state_prev && ROTARY_state_a == 1){

    if(page_counter == 0) // Preset menu
    {
      if(ROTARY_state_b == ROTARY_state_a) 
      {   //clockwise
        preset_display.preset_counter++;
        preset_display.preset_counter %= 4;
        preset_display.highlight_preset();
      }
      else
      { // counterclockwise
        preset_display.preset_counter--;
        if (preset_display.preset_counter == -1)
        {
          preset_display.preset_counter = 3;
        }
        preset_display.preset_counter %= 4;
        preset_display.highlight_preset();
      }
    }

    // else if(page_counter == 1) // tempo menu
    // {
    //   if(ROTARY_state_b == ROTARY_state_a) 
    //   {   //clockwise
    //     tempo_display.tempo++;
    //     if(tempo_display.tempo > 150)
    //     {
    //       tempo_display.tempo = 150;
    //     }
    //     tempo_display.update_tempo();
    //   }
    //   else
    //   { // counterclockwise
    //     tempo_display.tempo--;
    //     if(tempo_display.tempo < 90)
    //     {
    //       tempo_display.tempo = 90;
    //     }
    //     tempo_display.update_tempo();
    //   }
    // }

    else if (page_counter == 2)// velocity menu
    {
      if(ROTARY_state_b == ROTARY_state_a) 
      {   //clockwise
        velocity_display.velocity++;
        if(velocity_display.velocity > 127)
        {
          velocity_display.velocity = 127;
        }
        velocity_display.update_velocity();
      }
      else
      { // counterclockwise
        velocity_display.velocity--;
        if(velocity_display.velocity < 0)
        {
          velocity_display.velocity = 0;
        }
        velocity_display.update_velocity();
      }

    }
  }

  if(ROT_tempo_state_a != ROT_tempo_state_prev && ROT_tempo_state_a == 1)
  {
    if(ROT_tempo_state_b == ROT_tempo_state_a) 
      {   //clockwise
        tempo_display.tempo++;
        if(tempo_display.tempo > 150)
        {
          tempo_display.tempo = 150;
        }
        tempo_display.update_tempo();
      }
      else
      { // counterclockwise
        tempo_display.tempo--;
        if(tempo_display.tempo < 90)
        {
          tempo_display.tempo = 90;
        }
        tempo_display.update_tempo();
      }

  }

  // update previous button and encoder states
  prevb1state = b1state;
  prevb2state = b2state;
  ROTARY_state_prev = ROTARY_state_a;
  ROTARY_state_button_prev = ROTARY_state_button;
  ROT_tempo_state_prev = ROT_tempo_state_a;
  ROT_tempo_state_button_prev = ROT_tempo_state_button;

}

void print_page(int counter){
  if (counter == 0)
  {
    preset_display.initialize_menu();
  }
  else if (counter == 1)
  {
    tempo_display.initialize_menu();
  }
  else
  {
    velocity_display.initialize_menu();
  }
}



