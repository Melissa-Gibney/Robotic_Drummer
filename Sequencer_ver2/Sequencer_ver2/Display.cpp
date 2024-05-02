// updated 5/2/24

#include "Display.h"
#include <Wire.h>

/********************************************************************************************************************************************************/

// Constuctor
DisplayManager::DisplayManager() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET, 400000UL, 400000UL)  // 100000UL
{
  pages[PRESETS] = new PresetPage(&display);
  pages[TEMPO] = new TempoPage(&display);
  pages[VELOCITY] = new VelocityPage(&display);
}


// Init display and draw first page
void DisplayManager::init()
{
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS, true, false)) {
    Serial.println(F("SSD1309 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.display();

  // "Loading" Screen
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 15);
  display.println(F("Welcome to the"));
  display.setTextSize(1);
  display.setCursor(15, 25);
  display.println(F("Beat Buddy 3000!"));
  display.display();
  delay(3000);

  display.clearDisplay();
  display.drawCircle(64, 32, 28, SSD1306_WHITE);
  display.drawLine(36, 32, 31, 55, SSD1306_WHITE);
  display.drawLine(92, 32, 97, 55, SSD1306_WHITE);
  display.fillCircle(31, 55, 2, SSD1306_WHITE);
  display.fillCircle(97, 55, 2, SSD1306_WHITE);
  display.drawRect(45, 26, 39, 16, SSD1306_WHITE);
  display.drawLine(64, 26, 64, 20, SSD1306_WHITE);
  display.drawLine(60, 20, 68, 20, SSD1306_WHITE);
  display.drawLine(54, 32, 57, 32, SSD1306_WHITE);
  display.drawLine(71, 32, 74, 32, SSD1306_WHITE);
  display.drawLine(62, 37, 66, 37, SSD1306_WHITE);
  display.display();
  delay(3000);

  pages[page]->drawPage();
}


// Change tempo
void DisplayManager::setTempo(int bpm)
{
  pages[TEMPO]->setVal(bpm);
  pages[TEMPO]->drawPage();
  page = TEMPO;
}


void DisplayManager::setVel(int v)
{ 
  pages[VELOCITY]->setVal(v); 
  pages[VELOCITY]->drawPage();
}

// Change pages
void DisplayManager::movePage(int dir)
{
  while(dir < 0)
    dir += nPages;

  page = (page + dir) % nPages;
  pages[page]->drawPage();
}


// Rotary encoder controls
void DisplayManager::rotaryCW() { pages[page]->rotaryCW(); }
void DisplayManager::rotaryCCW() { pages[page]->rotaryCCW(); }
void DisplayManager::rotaryPress() { pages[page]->rotaryPress(); }

/********************************************************************************************************************************************************/

// Draw page to display
void TempoPage::drawPage()
{
  display->clearDisplay();
  display->setCursor(10,0);
  
  // Header
  display->setTextSize(2);
  display->setTextColor(SSD1306_WHITE);
  display->println(F("Tempo\n"));

  // Print tempo
  display->setTextSize(1);
  display->setCursor(10, 30);
  display->println(F("Tempo (in BPM):"));
  display->setCursor(10, 40);
  display->print(tempo);
  display->display();
}

/********************************************************************************************************************************************************/

// CW turn, increment velocity
void VelocityPage::rotaryCW()
{
  if(velocity < VELOCITY_MAX)
  {
    velocity++;
    
  }
  if (velocity > VELOCITY_MAX)
    {
      velocity = VELOCITY_MAX;
    }
    drawPage();
}


// CCW turn, decrement velocity
void VelocityPage::rotaryCCW()
{
  if(velocity > VELOCITY_MIN)
  {
    velocity--;
   
  }
    if (velocity < VELOCITY_MIN)
    {
      velocity = VELOCITY_MIN;
    }
    drawPage();
}


// Button press, reset velocity
void VelocityPage::rotaryPress()
{
  velocity = VELOCITY_DEFAULT;
  drawPage();
}


// Draw page to display
void VelocityPage::drawPage()
{
  display->clearDisplay();
  display->setCursor(10,0);
  
  // Header
  display->setTextSize(2);
  display->setTextColor(SSD1306_WHITE);
  display->println(F("Velocity\n"));

  // Print velocity
  display->setTextSize(1);
  display->setCursor(10, 30);
  display->println(F("Velocity (in MIDI):"));
  display->setCursor(10, 40);
  display->print(velocity);
  display->display();
}

/********************************************************************************************************************************************************/

// CW turn, increment highlighted preset
void PresetPage::rotaryCW()
{
  preset = (preset + 1) % 4;
  drawPage();
}


// CCW turn, decrement highlighted preset
void PresetPage::rotaryCCW()
{
  preset = (preset + 3) % 4;
  drawPage();
}


// Button press, select highlighted preset
void PresetPage::rotaryPress()
{
  selectedPreset = preset;
  drawPage();
  
  // Flash Selected Preset on Display
  preset = -1;
  drawPage();
  preset = selectedPreset;
  drawPage();

  int data;
  int dataSnare;
  int dataTom;
  int dataHiHat;
  
  // Send presets to TINYs- Check sequence should then pick up on the changes
  if (selectedPreset == 0){
    //Preset 1
    data = 0b11000000;
    dataSnare = 0b00110000;
    dataTom = 0b00001100;
    dataHiHat = 0b00000011;

  }

  if (selectedPreset == 1){
    //Preset 2
    data = 0b10001000;
    dataSnare = 0b00100010;
    dataTom = 0b01010101;
    dataHiHat = 0b11011101;

  }

  if (selectedPreset == 2){
    //Preset 3
    data = 0b10101010;
    dataSnare = 0b01010101;
    dataTom = 0b11101100;
    dataHiHat = 0b11111111;

  }

  if (selectedPreset == 3){
    //Preset 4
    data = 0b10010100;
    dataSnare = 0b01001011;
    dataTom = 0b00101010;
    dataHiHat = 0b00110110;

  }
    
  Wire.beginTransmission(TINY2);
  Wire.write(dataSnare);
  Wire.write(data);
  Wire.endTransmission();

  Wire.beginTransmission(TINY1);
  Wire.write(dataHiHat);
  Wire.write(dataTom);
  Wire.endTransmission();

}


// Draw page to display
void PresetPage::drawPage()
{  
  int y1 = 25;
  int y2 = 28;
  char buf[15] = {'\0'};
  char preset_names[4][15]{"Drum Roll", "Basic Beat", "Rock Beat", "Funky Beat"};
  int preset_endpixel[4]{64,70,64,70};

  // Header
  display->clearDisplay();
  display->setCursor(10,0);
  display->setTextSize(2);
  display->setTextColor(SSD1306_WHITE);
  display->println(F("Presets\n"));

  display->setTextSize(1);  

  for (int i = 0; i < nPresets; i++)
  {
    // Set text highlight
    if (preset == i)
    {
      // Padding
      display->drawLine(10, y1-1, preset_endpixel[i], y1-1, SSD1306_WHITE); // pad row of pixels above inverted text
      display->drawLine(10, y1-1, 10, y1+7, SSD1306_WHITE); // pad column on pixels
      
      // Highlighted text
      display->setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    }
    else
      display->setTextColor(SSD1306_WHITE);

    // Print preset names
    display->setCursor(11, y1);
    
    //sprintf(buf, "Preset %d", i+1);
    sprintf(buf, "%s", preset_names[i]);
    display->println(buf);

    // Circle for selection
    if (selectedPreset == i)
      display->fillCircle(5, y2, 2, SSD1306_WHITE);

    y1 += 10;
    y2 += 10;
  }

  display->display();
}

/********************************************************************************************************************************************************/

