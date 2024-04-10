// modified: 4/9/24

/* UTIL LIBRARIES */
#include "util.h"
#include <Arduino.h>
#include <elapsedMillis.h>
#include <Wire.h>

/* DRUM LIBRARIES */
#include "Drum.h"
#include "DrumManager.h"

/* DISPLAY LIBRARIES */
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "tempo_menu.h"
#include "preset_menu.h"
#include "velocity_menu.h"

/********************************************************************* DISPLAY INIT ***********************************************************************************/

// TODO: make display manager

// Declare OLED display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET, 400000UL, 100000UL);  

// Declare display pages
tempo_menu tempo_display;
preset_menu preset_display;
velocity_menu velocity_display;

// Page marker
int page_counter = 0; 
void print_page(int counter);


/********************************************************************* SEQUENCER INIT *********************************************************************************/

// Declare Drums
DrumManager manager(SOL_PIN_KICK, SOL_PIN_SNARE, SOL_PIN_TOM, SOL_PIN_HIHAT);

// TINY Query Flag
Alt readFlag = DUMMY;

//Declare Tempo and Timing Vars
elapsedMillis msBeatCount;

int tempo = 60; // The tempo in bpm
int curBeatIndex = 0; // The current beat in the sequence

long unsigned int msPerBeat = 15000 / tempo;


/********************************************************************* CONTROLS INIT **********************************************************************************/

// Rotary Encoder
Encoder rotary1(ROT1_PIN_CLK, ROT1_PIN_DT, ROT1_PIN_SW);

// Buttons
Button button1(BUTTON1_PIN, true);
Button button2(BUTTON2_PIN, true);


/********************************************************************* SETUP ******************************************************************************************/

void setup() {
  Serial.begin(9600);   // for debug

  // Begin TWI
  Wire.begin();     
  Wire.setClock(100000UL);
  Wire.setWireTimeout(1500);    // When I2C bus locks, loop() does not lock

  // Disable Mega pull-up resistors
  digitalWrite(SDA, LOW);
  digitalWrite(SCL, LOW);



  // Begin display
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS, true, false)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Init display menus
  tempo_display.set_display(display);
  preset_display.set_display(display);
  velocity_display.set_display(display);
  tempo_display.tempo = 120;
  velocity_display.velocity = 60;
  preset_display.preset_counter = 0;

  display.clearDisplay();
  display.display();
  print_page(page_counter); // initialize screen to the first page

  

  // Set Pin Modes for LED Tempo Pins
  for(int i = 0; i < 8; i++)
  {
    pinMode(LED_TEMPO_PINS[i], OUTPUT);
    digitalWrite(LED_TEMPO_PINS[i], LOW);
  }



  // Init sequence using DUMMY sequence
  manager.checkSequence(readFlag);
  readFlag = T1;
}


/********************************************************************* LOOP *******************************************************************************************/

void loop() {

  // Update control states
  rotary1.loop();
  button1.loop();
  button2.loop();



  // Begin new beat
  if(msBeatCount >= msPerBeat)
  {
    curBeatIndex = (curBeatIndex + 1) % WIN_LEN;

    // Update BPM LED
    for(int i = 0; i < 8; i++)
      digitalWrite(LED_TEMPO_PINS[i], LOW);
    digitalWrite(LED_TEMPO_PINS[curBeatIndex], HIGH);

    // Update sequences
    manager.checkSequence(readFlag);
    readFlag = (readFlag == T1) ? T2 : T1;
    
    // Play drums
    manager.play(curBeatIndex);
    
    // Update beat timer
    msBeatCount -= msPerBeat;
  }

  // Update drums
  manager.loop();



  // Update display page
  if (button1.justPressed()){
    page_counter++;
    page_counter = page_counter % 3;
    print_page(page_counter);
  }

  if (button2.justPressed()){
    page_counter--;
    if (page_counter == -1)
    {
      page_counter = 2;
    }
    page_counter = page_counter % 3;
    print_page(page_counter);
  }


  //Check for rotary encoder button press
  if(rotary1.justPressed()){
    
    if(page_counter == 1) // tempo page
    {
      tempo_display.tempo = 120;
      tempo_display.update_tempo();
    }
    
    else if(page_counter == 2) // velocity page
    {
      velocity_display.velocity = 60;
      velocity_display.update_velocity();
    }

    else // presets page
    {
      preset_display.select_preset(); // select preset
    }
  }

  //Check for change in the rotary encoder
  if(rotary1.rotated() == 1)  // CW
  {
    switch(page_counter){
      case 0:   // presets
        preset_display.preset_counter++;
        preset_display.preset_counter %= 4;
        preset_display.highlight_preset();
        break;

      case 1:   // tempo
        tempo_display.tempo++;
        if(tempo_display.tempo > 150)
          tempo_display.tempo = 150;
        tempo_display.update_tempo();
        break;

      case 2:   // velocity
        velocity_display.velocity++;
        if(velocity_display.velocity > 127)
          velocity_display.velocity = 127;
        velocity_display.update_velocity();
        break;
    }
  }

  else if(rotary1.rotated() == 2) // CCW
  {
    switch(page_counter){
      case 0:   // presets
        preset_display.preset_counter--;
        if (preset_display.preset_counter == -1)
          preset_display.preset_counter = 3;
        preset_display.preset_counter %= 4;
        preset_display.highlight_preset();
        break;

      case 1:   // tempo
        tempo_display.tempo--;
        if(tempo_display.tempo < 90)
          tempo_display.tempo = 90;
        tempo_display.update_tempo();
        break;

      case 2:   // velocity
        velocity_display.velocity--;
        if(velocity_display.velocity < 0)
          velocity_display.velocity = 0;
        velocity_display.update_velocity();
        break;
    }
  }
}

// Function for cycling through pages!
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

// int sequenceToBitwise(int seqData[])
// {
//   int bitwiseNum = 0b00000000;
//   for(int i = 0; i < N_STEPS; i++)
//   {
//     bitwiseNum = bitwiseNum << 1;
//     bitwiseNum = bitwiseNum + (seqData[i] & 0b00000001);
//   }
//   return bitwiseNum;
// }