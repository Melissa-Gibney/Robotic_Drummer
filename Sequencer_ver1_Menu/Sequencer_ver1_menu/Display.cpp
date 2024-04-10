// updated 4/10/24

#include "Display.h"
#include <Wire.h>

/********************************************************************************************************************************************************/

DisplayManager::DisplayManager() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET, 100000UL, 100000UL) 
{
  pages[0] = new PresetPage(display);
  pages[1] = new TempoPage(display);
  pages[2] = new VelocityPage(display);
}

void DisplayManager::init()
{
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS, true, false)) {
    Serial.println(F("SSD1309 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  pages[page]->drawPage();
}

void DisplayManager::movePage(int dir)
{
  page = (page + dir) % nPages;
  pages[page]->drawPage();
}

void DisplayManager::rotaryCW() { pages[page]->rotaryCW(); }
void DisplayManager::rotaryCCW() { pages[page]->rotaryCCW(); }
void DisplayManager::rotaryPress() { pages[page]->rotaryPress(); }

/********************************************************************************************************************************************************/

void TempoPage::rotaryCW()
{
  if(tempo < TEMPO_MAX)
  {
    tempo++;
    drawPage();
  }
}

void TempoPage::rotaryCCW()
{
  if(tempo > TEMPO_MIN)
  {
    tempo--;
    drawPage();
  }
}

void TempoPage::rotaryPress()
{
  tempo = tempoDefault;
  drawPage();
}


void TempoPage::drawPage()
{
  display.clearDisplay();
  display.setCursor(10,0);
  
  // Title
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.println(F("Tempo!!!\n"));

  // Print Tempo
  display.setTextSize(1);
  display.setCursor(10, 30);
  display.println(F("Tempo (in BPM):"));
  display.setCursor(10, 40);
  display.print(tempo);
  display.display();
}

/********************************************************************************************************************************************************/

void VelocityPage::rotaryCW()
{
  if(velocity < VELOCITY_MAX)
  {
    velocity++;
    drawPage();
  }
}

void VelocityPage::rotaryCCW()
{
  if(velocity > VELOCITY_MIN)
  {
    velocity--;
    drawPage();
  }
}

void VelocityPage::rotaryPress()
{
  velocity = velocityDefault;
  drawPage();
}


void VelocityPage::drawPage()
{
  display.clearDisplay();
  display.setCursor(10,0);
  
  // Title
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.println(F("Velocity!\n"));

  // Print velocity
  display.setTextSize(1);
  display.setCursor(10, 30);
  display.println(F("Velocity (in MIDI):"));
  display.setCursor(10, 40);
  display.print(velocity);
  display.display();
}

/********************************************************************************************************************************************************/

void PresetPage::rotaryCW()
{
  preset = (preset + 1) % 4;
  drawPage();
}

void PresetPage::rotaryCCW()
{
  preset = (preset - 1) % 4;
  drawPage();
}

void PresetPage::rotaryPress()
{
  selectedPreset = preset;
  drawPage();
}


void PresetPage::drawPage()
{
  int y1 = 25;
  int y2 = 28;

  display.clearDisplay();
  display.setCursor(5,0);
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.println(F("PRESETS!!!\n"));

  display.setTextSize(1);
  display.drawLine(10, 24, 58, 24, SSD1306_WHITE); // pad row of pixels above inverted text
  display.drawLine(10, 24, 10, 32, SSD1306_WHITE); // pad column on pixels

  for (int i = 0; i < nPresets; i++)
  {
    // Set text highlight
    if (preset == i)
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    else
      display.setTextColor(SSD1306_WHITE);

    display.setCursor(11, y1);
    char buf[10];
    sprintf(buf, "Preset %d", i+1);
    display.println(buf);

    if (selectedPreset == i)
      display.fillCircle(5, y2, 2, SSD1306_WHITE);

    y1 += 10;
    y2 += 10;
  }
}

/********************************************************************************************************************************************************/

