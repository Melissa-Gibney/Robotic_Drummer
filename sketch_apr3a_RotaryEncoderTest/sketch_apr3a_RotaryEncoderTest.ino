// Rotary Encoder Circuit Test
// modified: 4/3/24

// #include <SPI.h>
// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
// #include "tempo_menu.h"
// #include "preset_menu.h"
// #include "velocity_menu.h"

// Tempo Rotary Encoder
#define ROT_tempo_a 31
#define  ROT_tempo_b 32
#define  ROT_tempo_button 33
int ROT_tempo_state_a = 1;
int ROT_tempo_state_b = 1;
int ROT_tempo_state_prev = 1;
int ROT_tempo_state_button;
int ROT_tempo_state_button_prev = 1;

// LED Pins
#define LED1 28
#define LED2 27
#define LED3 26

int tempo = 120;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  pinMode(ROT_tempo_a, INPUT);
  pinMode(ROT_tempo_b, INPUT);
  pinMode(ROT_tempo_button, INPUT_PULLUP);

  

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  ROT_tempo_state_a = digitalRead(ROT_tempo_a);
  ROT_tempo_state_b = digitalRead(ROT_tempo_b);

  ROT_tempo_state_button = digitalRead(ROT_tempo_button);

  if(ROT_tempo_state_a != ROT_tempo_state_prev && ROT_tempo_state_a == 1)
  {
    if(ROT_tempo_state_b == ROT_tempo_state_a) 
      {   //clockwise
        tempo++;
        if(tempo > 150)
        {
          tempo = 150;
        }
        //Serial.println(tempo);
        digitalWrite(LED1,HIGH);
        delay(10);
        digitalWrite(LED1,LOW);
      }
      else
      { // counterclockwise
        tempo--;
        if(tempo < 90)
        {
          tempo = 90;
        }
        //Serial.println(tempo);
        digitalWrite(LED3,HIGH);
        delay(10);
        digitalWrite(LED3,LOW);
      }
      Serial.print("B = ");
      Serial.println(ROT_tempo_state_b);

      Serial.print("A = ");
      Serial.println(ROT_tempo_state_a);

      Serial.println(tempo);
  }

  //Check for button press
  if(!ROT_tempo_state_button && ROT_tempo_state_button_prev){
    
    tempo = 120;
    digitalWrite(LED2,HIGH);
    delay(10);
    digitalWrite(LED2,LOW);
  
  }

  // update previous button and encoder states
  ROT_tempo_state_prev = ROT_tempo_state_a;
  ROT_tempo_state_button_prev = ROT_tempo_state_button;

  // Serial.println(tempo);
  // delay(10);
}
