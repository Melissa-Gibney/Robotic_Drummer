// updated 4/12/24

#ifndef UTIL_H
#define UTIL_H

// Libraries
#include <ezButton.h>


// Macros
#define DEBOUNCE 10   // ms

#define MAX_LEN 32    // steps
#define WIN_LEN 8     // steps

#define SCREEN_WIDTH  128   // pixels
#define SCREEN_HEIGHT 64    // pixels 
#define OLED_RESET    -1    // share Arduino reset pin

enum Alt {T1, T2, DUMMY};   // TINY query flags
enum DrumID {KICK, SNARE, TOM, HIHAT};

#define TEMPO_MIN     10    // BPM
#define TEMPO_MAX     200   // BPM
#define TEMPO_DEFAULT 120   // BPM

#define VELOCITY_MIN      0  
#define VELOCITY_MAX      127
#define VELOCITY_DEFAULT  60


// Pins
#define SOL_PIN_KICK  54    // A0
#define SOL_PIN_SNARE 55    // A1
#define SOL_PIN_TOM   56    // A2
#define SOL_PIN_HIHAT 57    // A3

#define ROT1_PIN_CLK  30    // display encoder
#define ROT1_PIN_DT   29
#define ROT1_PIN_SW   28      

#define ROT2_PIN_CLK  27    // tempo encoder
#define ROT2_PIN_DT   26
#define ROT2_PIN_SW   25  

#define BUTTON1_PIN   50
#define BUTTON2_PIN   51

#define CLEAR_KICK    49    // individual clear buttons
#define CLEAR_SNARE   48
#define CLEAR_TOM     47
#define CLEAR_HIHAT   46

#define MUTE_KICK     45    // individual mute buttons
#define MUTE_SNARE    44
#define MUTE_TOM      43
#define MUTE_HIHAT    42

#define MUTE_KICK_LED   41  // individual mute LEDs
#define MUTE_SNARE_LED  40
#define MUTE_TOM_LED    39
#define MUTE_HIHAT_LED  38

#define MASTER_RESET  53    // Master reset all drums
#define START_STOP    52    // Start Stop Sequence

const int LED_TEMPO_PINS[] = {2, 3, 4, 5, 6, 7, 8, 9};    // WIN_LEN steps


// I2C addresses
#define TINY1 0x2A
#define TINY2 0x2B
#define SCREEN_ADDRESS 0x3C


/********************************************************************************************/

class Button : public ezButton {
  public:
    /*!
    Constructor for a button. Sets pinModes, sets debounce, manages button states.
    .
    pin     ->  Button input pin.
    pullUp  ->  True for INPUT_PULLUP, False for INPUT.
    */
    Button(uint8_t pin, bool pullUp) : ezButton(pin){
      if(pullUp)
        pinMode(pin, INPUT_PULLUP);
      else
        pinMode(pin, INPUT);

      this->setDebounceTime(DEBOUNCE);
    }


    /*!
    Return true  ->  button just pressed.
    Return false ->  otherwise.
    */
    bool justPressed(){
      state = this->getState();

      if(!state && prevState){
        prevState = state;
        return true;
      }

      else{
        prevState = state;
        return false;
      }
    }

  private:
    bool state = false;
    bool prevState = false;
};

/********************************************************************************************/

class Encoder {
  private:
    uint8_t CLK, DT;
    Button button;

    bool prevState;
    bool stateCLK;
    bool stateDT;


  public:
    /*!
    Constructor for a rotary encoder. Sets pinModes, sets button debounce,
    manages all states.
    .
    pinCLK    ->  CLK input pin.
    pinDT     ->  DT input pin.
    pinSW     ->  SW input pin.
    */
    Encoder(uint8_t pinCLK, uint8_t pinDT, uint8_t pinSW) : button(pinSW, true){
      pinMode(pinCLK, INPUT);
      pinMode(pinDT, INPUT);

      prevState = stateCLK = digitalRead(pinCLK);
      stateDT = digitalRead(pinDT);

      CLK = pinCLK; DT = pinDT;
    }

    /*!
    Call this in loop().
    */
    void loop(){
      int count = 0, lastRead = -1;

      prevState = stateCLK;

      do{
      stateCLK = digitalRead(CLK);
      stateDT = digitalRead(DT);

      count++;

      if(lastRead != stateCLK)
        count = 0;

      lastRead = stateCLK;

      } while(count < DEBOUNCE);

      button.loop();
    }

    /*!
    Return 0   ->  Not rotated.
    Return 1   ->  Rotated clockwise.
    Return 2   ->  Rotated counter clockwise.
    */
    int rotated(){
      if (stateCLK && !prevState){
        if (stateCLK == stateDT)
          return 1;   // CLOCKWISE
        
        else
          return 2;   // COUNTER CLOCKWISE
      }

      else
        return 0;     // NOT ROTATED
    }

    /*!
    Return true  ->  button just pressed.
    Return false ->  otherwise.
    */
    bool justPressed(){ return button.justPressed(); }

  
};

/********************************************************************************************/

#endif