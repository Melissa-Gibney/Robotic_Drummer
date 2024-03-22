#ifndef UTIL_H
#define UTIL_H

#define DEBOUNCE 5

#define MAX_LEN 32
#define WIN_LEN 8

// I2C addresses for the Tinys
#define TINY1 0x2A
#define TINY2 0x2B

#include <ezButton.h>

class Button : public ezButton{
  public:
    Button(uint8_t pin) : ezButton(pin){
      pinMode(pin, INPUT_PULLUP);
      this->setDebounceTime(DEBOUNCE);
    }

    int justPressed(){
      state = this->getState();

      if(!state && prevState){
        prevState = state;
        return 1;
      }

      else{
        prevState = state;
        return 0;
      }
    }

  private:
    bool state = false;
    bool prevState = false;

};

#endif