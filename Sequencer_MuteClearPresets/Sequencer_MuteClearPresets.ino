// Drum Sequencer Adding in Mute, Clear, and Presets
// authors: Hanna Berger, Melissa Gibney
// modified: 4/9/24

/* UTIL LIBRARIES */
#include <Arduino.h>
#include <ezButton.h>
#include <elapsedMillis.h>
#include <Wire.h>
#include "util.h"

/* DRUM LIBRARIES */
#include "Drum.h"
#include "DrumManager.h"

/* DISPLAY LIBRARIES */
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "tempo_menu.h"
#include "preset_menu.h"
#include "velocity_menu.h"



// #define N_STEPS 8

// Declare Drums
Drum kick;
Drum snare;
Drum tom;
Drum hihat;
DrumManager manager;

int alternate = 3;

bool drumsArePlaying = false; // Keep track of whether the drums are actuating/holding

const int sequencerLength = 8; // Amount of buttons on one row of the sequencer
int sequenceLength = 8; // Amount of steps in the sequence

//Declare Tempo and Timing Vars
elapsedMillis msBeatCount;
elapsedMillis msDrumReleaseCount;

int tempo = 60; // The tempo in bpm
int curBeatIndex = 0; // The current beat in the sequence
long unsigned int msPerBeat = 15000 / tempo;
long unsigned int msPullTimeKick = 30; // Time that the kick needs to actuate on the beat
long unsigned int msPullTimeTom = 30; // Time that the tom needs to actuate on the beat
long unsigned int msPullTimeSnare = 30; // Time that the snare needs to actuate on the beat
long unsigned int msPullTimeHiHat = 30; // Time that the hihat needs to actuate on the beat
long unsigned int msHoldTime = 10; // Time to hold the solenoid after the articulation and before the release
long unsigned int timeToRetractSolenoid = msHoldTime + msPerBeat; // Time to hold the solenoid after the articulation and before the release

// Dummy Sequence
// int sequence[N_STEPS] = {1,0,0,1,1,1,0,1};
// int sequence2[N_STEPS] = {1,0,1,0,1,0,1,0};
// int sequence3[N_STEPS] = {1,0,1,0,1,0,1,0};
// int sequence4[N_STEPS] = {0,1,1,0,0,1,1,0};

// OLED Screen Stuff
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels. 
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET, 100000UL);     

// Variable Declarations
// Rotary Encoder
int ROTARY_a = 30;
int ROTARY_b = 29;
int ROTARY_button = 28;
int ROTARY_state_a = 1;
int ROTARY_state_b = 1;
int ROTARY_state_prev = 1;
int ROTARY_state_button;
int ROTARY_state_button_prev = 1;
int pos = 0;

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

// for moving between pages
int page_counter = 0; 
void print_page(int counter);

// Dummy Velocity
int velocity[WIN_LEN] = {60, 75, 83, 75, 60, 52, 60, 60};


// DEBUG
Button debugButton(52, true);

void debug(){
  Serial.println("PRESS");
  Wire.beginTransmission(0x3C);

  /********************************************************/

  int bytes = 4;

  for(int i = 0; i < bytes; i++){
    // Wire.beginTransmission(SCREEN_ADDRESS);
    Wire.write(0b01010101);  
    // Wire.endTransmission(false);
  }

  /********************************************************/
  int err = Wire.endTransmission();

  switch(err){
    case 0:
      Serial.println("Success");
      break;
    case 1:
      Serial.println("Data too long, buffer overflow");
      break;
    case 2:
      Serial.println("NACK on trasmit of address");
      break;
    case 3:
      Serial.println("NACK on transmit of data");
      break;
    case 4:
      Serial.println("Other error");
      break;
    case 5:
      Serial.println("Timeout");
      break;
    default:
      break;
  }

  delay(1);
}


void setup() {

  Wire.begin();     
  Serial.begin(9600);

  // DEBUG
  digitalWrite(SDA, LOW);
  digitalWrite(SCL, LOW);

  // Set Pin Modes for LED Tempo Pins
  for(int i = 0; i < 8; i++)
  {
    pinMode(LED_TEMPO_PINS[i], OUTPUT);
    digitalWrite(LED_TEMPO_PINS[i], LOW);
  }

  // Set Pin Modes for Solenoid Pins
  pinMode(SOL_PIN_KICK, OUTPUT);
  pinMode(SOL_PIN_TOM, OUTPUT);
  pinMode(SOL_PIN_SNARE, OUTPUT);
  pinMode(SOL_PIN_HIHAT, OUTPUT);

  // Set Solenoid Pins to Low
  digitalWrite(SOL_PIN_KICK, LOW);
  digitalWrite(SOL_PIN_TOM, LOW);
  digitalWrite(SOL_PIN_SNARE, LOW);
  digitalWrite(SOL_PIN_HIHAT, LOW);

  //Assign Solenoid Pins to Drums
  manager.assignSolenoids(SOL_PIN_KICK, SOL_PIN_TOM, SOL_PIN_SNARE, SOL_PIN_HIHAT);

  // Serial.println("Intialized Sequence");
  // manager.printHiHatSequence();
  
  // delay(10);
  // manager.checkSequence();
  // Serial.println("Updated Sequence");
  // manager.printHiHatSequence();
  
  manager.checkSequence(alternate);
  alternate = 1;

  // delay(1);
  // Serial.println("Kick Sequence");
  // manager.printKickSequence();
  // Serial.println("Snare Sequence");
  // manager.printSnareSequence();
  // Serial.println("Tom Sequence");
  // manager.printTomSequence();
  // Serial.println("Hi-Hat Sequence");
  // manager.printHiHatSequence();

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS, false, false)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // pinmode buttons
  pinMode(BUTTON1,INPUT);
  pinMode(BUTTON2,INPUT);

  // pinmode for rotary encoder
  pinMode(ROTARY_a, INPUT);
  pinMode(ROTARY_b, INPUT);
  pinMode(ROTARY_button, INPUT_PULLUP);

  // // Welcome Screen displays for 3 seconds
  display.clearDisplay();
  // display.fillCircle(64, 32, 30, SSD1306_WHITE);
  // display.setTextSize(1);
  // display.setTextColor(SSD1306_BLACK);
  // display.setCursor(35, 30);
  // display.println(F("Welcome...\n"));
  // display.fillCircle(5, 5, 5, SSD1306_WHITE);
  // display.drawCircle(122, 5, 5, SSD1306_WHITE);
  // display.fillCircle(122, 58, 5, SSD1306_WHITE);
  // display.drawCircle(5, 58, 5, SSD1306_WHITE);
  display.display();
  // delay(3000);
  // display.clearDisplay();

  // // set menus to the OLED display and initialize them
  // tempo_display.set_display(display);
  // preset_display.set_display(display);
  // velocity_display.set_display(display);
  // tempo_display.tempo = 120;
  // velocity_display.velocity = 60;
  // preset_display.preset_counter = 0;
  
  // print_page(page_counter); // initialize screen to the first page
}

void loop() {
  // put your main code here, to run repeatedly:
  // Keep track of elapsed milliseconds and update every set amount of milliseconds based on the tempo
  // if(msBeatCount >= msPerBeat-msPullTimeKick && !drumsArePlaying)
  // {
  //   //Set drum timers to current time
  //   manager.setDrumTimers(msPullTimeKick, msPullTimeTom, msPullTimeSnare, msPullTimeHiHat);
  //   //Play drum at index
  //   manager.playKick(curBeatIndex);
  //   manager.playTom(curBeatIndex);
  //   manager.playSnare(curBeatIndex);
  //   manager.playHiHat(curBeatIndex);
  //   drumsArePlaying = true;

  //   //Set the amount of time the solenoid should be extended
  //   timeToRetractSolenoid = msHoldTime + msPerBeat;
  // }

  // if(msBeatCount >= msPerBeat-msPullTimeKick && !drumsArePlaying)
  // {
  //   curBeatIndex = (curBeatIndex + 1) % N_STEPS;
  //   manager.checkSequence();
  //   //kick.print_sequence();
  //   manager.setDrumTimers(msPerBeat-msPullTimeKick, msPullTimeTom, msPullTimeSnare, msPullTimeHiHat);
  //   manager.playKick(curBeatIndex);
  //   //manager.playTom(curBeatIndex);
  //   drumsArePlaying = true;
  // }

  //Check if there is a new beat
  if(msBeatCount >= msPerBeat)
  {
    curBeatIndex = (curBeatIndex + 1) % WIN_LEN;
    manager.checkSequence(alternate);
    // debug();
    alternate = (alternate == 1) ? 2 : 1;
    
    //kick.print_sequence();
    manager.setDrumTimers(msPerBeat-msPullTimeKick, msPerBeat - msPullTimeTom, msPerBeat-msPullTimeSnare, msPerBeat - msPullTimeHiHat);
    manager.playKick(curBeatIndex);
    manager.playSnare(curBeatIndex);
    manager.playTom(curBeatIndex);
    manager.playHiHat(curBeatIndex);

    //Serial.println("Kick Sequence");
    //manager.printKickSequence();
    //Serial.println("Snare Sequence");
    // manager.printSnareSequence();
    //Serial.println("Tom Sequence");
    // manager.printTomSequence();
    //Serial.println("Hi-Hat Sequence");
    // manager.printHiHatSequence();
    //Reset count
    //msBeatCount -= msPerBeat;
    drumsArePlaying = false;

    // Light up LED for that index
    for(int i = 0; i < 8; i++)
    {
      digitalWrite(LED_TEMPO_PINS[i], LOW);
    }
    digitalWrite(LED_TEMPO_PINS[curBeatIndex], HIGH);

    msBeatCount = 0;
  }

  //Check if each drum timer has reached the retraction time
  if(manager.getKick().get_drum_timer() >= timeToRetractSolenoid)
  {
    //Retract the kick
    manager.stopKick();
  }
  if(manager.getTom().get_drum_timer() >= timeToRetractSolenoid)
  {
    //Retract the tom
    manager.stopTom();
  }
  if(manager.getSnare().get_drum_timer() >= timeToRetractSolenoid)
  {
    //Retract the snare
    manager.stopSnare();
  }
  if(manager.getHiHat().get_drum_timer() >= timeToRetractSolenoid)
  {
    //Retract the hihat
    manager.stopHiHat();
  }


  // OLED SCREEN STUFF (from OLED_Menu_ver2)
  debugButton.loop();

  if(debugButton.justPressed())
    debug();

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

  //Check for rotary encoder button press
  if(!ROTARY_state_button && ROTARY_state_button_prev){
    
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
      manager.set_preset(preset_display.get_preset());
    }
  }

  //Check for change in the rotary encoder
  if(ROTARY_state_a != ROTARY_state_prev && ROTARY_state_a == 1){

    if(page_counter == 0) // Preset menu
    {
      if(ROTARY_state_b == ROTARY_state_a)
      {   // if rotated clockwise highlight next preset down
        preset_display.preset_counter++;
        preset_display.preset_counter %= 4;
        preset_display.highlight_preset();
      }
      else
      { // if rotated counterclockwise highlight next preset up
        preset_display.preset_counter--;
        if (preset_display.preset_counter == -1)
        {
          preset_display.preset_counter = 3;
        }
        preset_display.preset_counter %= 4;
        preset_display.highlight_preset();
      }
    }

    else if(page_counter == 1) // tempo menu
    {
      if(ROTARY_state_b == ROTARY_state_a) 
      {   //if clockwise increase tempo by 1
        tempo_display.tempo++;
        if(tempo_display.tempo > 150)
        {
          tempo_display.tempo = 150;
        }
        tempo_display.update_tempo();
      }
      else
      { // if counterclockwise decrease tempo by 1
        tempo_display.tempo--;
        if(tempo_display.tempo < 90)
        {
          tempo_display.tempo = 90;
        }
        tempo_display.update_tempo();
      }
    }

    else // velocity menu
    {
      if(ROTARY_state_b == ROTARY_state_a) 
      {   //if clockwise increase velocity by 1
        velocity_display.velocity++;
        if(velocity_display.velocity > 127)
        {
          velocity_display.velocity = 127;
        }
        velocity_display.update_velocity();
      }
      else
      { //if counterclockwise decrease velocity by 1
        velocity_display.velocity--;
        if(velocity_display.velocity < 0)
        {
          velocity_display.velocity = 0;
        }
        velocity_display.update_velocity();
      }
    }
  }

  // update previous button and encoder states
  prevb1state = b1state;
  prevb2state = b2state;
  ROTARY_state_prev = ROTARY_state_a;
  ROTARY_state_button_prev = ROTARY_state_button;

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