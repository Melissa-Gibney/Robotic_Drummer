// OLED Screen Basic Menu Version 1
// Author: Hanna Berger
// Last Modified: 2/21/2024

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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

// Declarations
int page_counter = 0; // for moving between pages
int menu_choice = 0; // for highlighting text on page... should be inverted text

// Buttons
int BUTTON1 = 22;
int BUTTON2 = 23;
int b1state;
int b2state;
int prevb1state = 0;
int prevb2state = 0;

int LED1 = 32;
int LED2 = 33;

// //Roatary Encoder
int ROTARY_a = 30;
int ROTARY_b = 29;
int ROTARY_button = 28;
int ROTARY_state_a;
int ROTARY_state_b;
int ROTARY_state_prev;
int ROTARY_state_button;
int ROTARY_state_button_prev = 0;
int pos = 0;

// Functions
void print_page1();
void print_page2();
void print_page3();
void print_page(int counter);
void highlight_menu(int counter, int page_counter);


void setup(){
  // put your setup code here, to run once:

  // pinmode buttons and LEDs
  pinMode(BUTTON1,INPUT);
  pinMode(BUTTON2,INPUT);

  // pinmode for rotary encoder
  pinMode(ROTARY_a, INPUT);
  pinMode(ROTARY_b, INPUT);
  pinMode(ROTARY_button, INPUT_PULLUP);

  // LED Test
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.drawPixel(10, 10, SSD1306_WHITE);
  display.display();
  delay(500);
  display.clearDisplay();

  // initialize screen to page 1
  print_page(page_counter);
  //highlight_menu(menu_choice);


}

void loop(){
  // put your main code here, to run repeatedly:
  // read button states
  b1state = digitalRead(BUTTON1);
  b2state = digitalRead(BUTTON2);

  ROTARY_state_a = digitalRead(ROTARY_a);
  //ROTARY_state_b = digitalRead(ROTARY_b);
  ROTARY_state_button = digitalRead(ROTARY_button);

  // To turn pages
  if (b1state && !prevb1state){
    
    page_counter++;
    page_counter = page_counter % 3;
    print_page(page_counter);
    highlight_menu(0,page_counter);
    digitalWrite(LED1, HIGH);
    delay(10);
    digitalWrite(LED1, LOW);
  }

  if (b2state && !prevb2state){
    page_counter--;
    if (page_counter == -1)
    {
      page_counter = 2;
    }
    page_counter = page_counter % 3;
    print_page(page_counter);
    highlight_menu(0,page_counter);
    digitalWrite(LED2, HIGH);
    delay(10);
    digitalWrite(LED2, LOW);
  }

  //Check for button press
  if(!ROTARY_state_button && ROTARY_state_button_prev){
    pos = 0;
  }
  
  //Check for clock change
  if(ROTARY_state_a != ROTARY_state_prev && ROTARY_state_a == 1){
    if(digitalRead(ROTARY_b) == ROTARY_state_a) 
    {   //clockwise
      menu_choice++;
      menu_choice %= 4;
      highlight_menu(menu_choice, page_counter);
    }
    else
    { // counterclockwise
      menu_choice--;
      if (menu_choice == -1)
      {
        menu_choice = 3;
      }
      menu_choice %= 4;
      highlight_menu(menu_choice, page_counter);
    }
  }
  prevb1state = b1state;
  prevb2state = b2state;
  ROTARY_state_prev = ROTARY_state_a;
  ROTARY_state_button_prev = ROTARY_state_button;
}

// Function definitions
void print_page1(){
  display.clearDisplay();
  display.setCursor(0,0);
  
  // Title
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.println(F("PRESETS!!!\n"));

  display.setTextSize(1);
  display.println(F("Preset 1"));
  display.println(F("Preset 2"));
  display.println(F("Preset 3"));
  display.println(F("Preset 4"));
  display.display();
}

void print_page2(){
  display.clearDisplay();
  display.setCursor(0,0);
  
  // Title
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.println(F("Velocity!!!\n"));

  display.setTextSize(1);
  display.println(F("Velocity:"));
  display.println(F("2"));
  
  // display.println(F("Preset 5"));
  // display.println(F("Preset 6"));
  // display.println(F("Preset 7"));
  // display.println(F("Preset 8"));
  display.display();
}

void print_page3(){
  display.clearDisplay();
  display.setCursor(0,0);
  
  // Title
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.println(F("Tempo!!!\n"));

  display.setTextSize(1);
  display.println(F("Tempo (in BPM):"));
  display.println(F("120"));
  // display.println(F("Preset 9"));
  // display.println(F("Preset 10"));
  // display.println(F("Preset 11"));
  // display.println(F("Preset 12"));
  display.display();
  
}

void print_page(int counter){
  if (counter == 0){
    print_page1();
  }
  if (counter == 1){
    print_page2();
  }
  if (counter == 2){
    print_page3();
  }
}


void highlight_menu(int counter, int page_counter){
  if (counter == 0){
    
    if(page_counter == 0){
      // Title
      display.clearDisplay();
      display.setCursor(0,0);
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      display.println(F("PRESETS!!!\n"));

      display.setTextSize(1);
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
      display.println(F("Preset 1"));
      display.setTextColor(SSD1306_WHITE);
      display.println(F("Preset 2"));
      display.println(F("Preset 3"));
      display.println(F("Preset 4"));
      display.display();
    }

  }
  if (counter == 1){
    
    if(page_counter == 0){
      // Title
      display.clearDisplay();
      display.setCursor(0,0);
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      display.println(F("PRESETS!!!\n"));

      display.setTextSize(1);
      display.println(F("Preset 1"));
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text;
      display.println(F("Preset 2"));
      display.setTextColor(SSD1306_WHITE);
      display.println(F("Preset 3"));
      display.println(F("Preset 4"));
      display.display();
    }
    
  }
  if (counter == 2){
    if(page_counter == 0){
      // Title
      display.clearDisplay();
      display.setCursor(0,0);
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      display.println(F("PRESETS!!!\n"));

      display.setTextSize(1);
      display.println(F("Preset 1"));
      display.println(F("Preset 2"));
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
      display.println(F("Preset 3"));
      display.setTextColor(SSD1306_WHITE);
      display.println(F("Preset 4"));
      display.display();
    }

  }
  if (counter == 3){
    // Title
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.println(F("PRESETS!!!\n"));

    display.setTextSize(1);
    display.println(F("Preset 1"));
    display.println(F("Preset 2"));
    display.println(F("Preset 3"));
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    display.println(F("Preset 4"));
    display.display();
    
  }
}



