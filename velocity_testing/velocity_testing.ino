#include <ezButton.h>

#define SWITCH_PIN 1
#define SOL_PIN 0

#define HIGH_OUT_PIN 2

ezButton button = SWITCH_PIN;
uint8_t buttonState = 1;
uint8_t tempState;

void setup() {
  // put your setup code here, to run once:
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  pinMode(SOL_PIN, OUTPUT);
  pinMode(HIGH_OUT_PIN, OUTPUT);

  button.setDebounceTime(15);

  digitalWrite(SOL_PIN, LOW);
  digitalWrite(HIGH_OUT_PIN, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  button.loop();

  tempState = button.getState();

  if(!tempState && buttonState){
    buttonState = tempState;
    throwSol();
  }

  else if(tempState && !buttonState){
    buttonState = tempState;
  }

}


void throwSol(){
  analogWrite(SOL_PIN, 63);
  // digitalWrite(SOL_PIN, HIGH);
  delay(25);
  analogWrite(SOL_PIN, 0);
  // digitalWrite(SOL_PIN, LOW);
}
