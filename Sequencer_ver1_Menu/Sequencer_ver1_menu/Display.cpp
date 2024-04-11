// updated 4/11/24

#include "Display.h"
#include <Wire.h>

/********************************************************************************************************************************************************/

// Constuctor
DisplayManager::DisplayManager() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET, 100000UL, 100000UL)
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

  pages[page]->drawPage();
}


// Change tempo
void DisplayManager::setTempo(int bpm)
{
  pages[TEMPO]->setVal(bpm);
  pages[TEMPO]->drawPage();
  page = TEMPO;
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

// CW turn, increment tempo
void TempoPage::rotaryCW()
{
  if(tempo < TEMPO_MAX)
  {
    tempo++;
    drawPage();
  }
}


// CCW turn, decrement tempo
void TempoPage::rotaryCCW()
{
  if(tempo > TEMPO_MIN)
  {
    tempo--;
    drawPage();
  }
}


// Button press, reset tempo
void TempoPage::rotaryPress()
{
  tempo = tempoDefault;
  drawPage();
}


// Draw page to display
void TempoPage::drawPage()
{
  display->clearDisplay();
  display->setCursor(10,0);
  
  // Header
  display->setTextSize(2);
  display->setTextColor(SSD1306_WHITE);
  display->println(F("Tempo!!!\n"));

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
    drawPage();
  }
}


// CCW turn, decrement velocity
void VelocityPage::rotaryCCW()
{
  if(velocity > VELOCITY_MIN)
  {
    velocity--;
    drawPage();
  }
}


// Button press, reset velocity
void VelocityPage::rotaryPress()
{
  velocity = velocityDefault;
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
  display->println(F("Velocity!\n"));

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
}


// Draw page to display
void PresetPage::drawPage()
{
  int y1 = 25;
  int y2 = 28;
  char buf[10] = {'\0'};

  // Header
  display->clearDisplay();
  display->setCursor(5,0);
  display->setTextSize(2);
  display->setTextColor(SSD1306_WHITE);
  display->println(F("PRESETS!!!\n"));

  display->setTextSize(1);  

  for (int i = 0; i < nPresets; i++)
  {
    // Set text highlight
    if (preset == i)
    {
      // Padding
      display->drawLine(10, y1-1, 58, y1-1, SSD1306_WHITE); // pad row of pixels above inverted text
      display->drawLine(10, y1-1, 10, y1+7, SSD1306_WHITE); // pad column on pixels
      
      // Highlighted text
      display->setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    }
    else
      display->setTextColor(SSD1306_WHITE);

    // Print preset names
    display->setCursor(11, y1);
    
    sprintf(buf, "Preset %d", i+1);
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

