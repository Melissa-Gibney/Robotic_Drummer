#include <Wire.h>

#define I2CADDRESS 0x2A

#define BMASK 0b10111111  // PB6 inaccessible
#define CMASK 0b10000000  // only read C7
#define DMASK 0b11111010  // D0 and D2 reversed


int lights = 0, switchStates = 0, prevSwitchStates = 0;

int row = 0;  // row interator for light multiplexing



/************** SETUP **************/

void setupLights() {
  /*
  Set up 250Hz interrupt on Timer/Counter1
  */

  TCCR1A = 0<<WGM10;            // CTC mode (clear timer on compare)

  // CTC mode; Scale I/O clock to 31,250Hz (8MHz internal clock)
  TCCR1B = 1<<WGM12 | 4<<CS10;  // 8MHz / 256 = 31,250Hz
  
  // Scale timer rate to 250Hz
  OCR1A = 124;   // OCR1A = top value of the counter; 31,250Hz / 125 = 250Hz

  // Enable compare match interrupt               
  TIMSK1 = TIMSK1 | 1<<OCIE1A;  
 
  // Make LED rows and columns outputs
  DDRC = DDRC | 0x0F;
  DDRA = DDRA | 0x0F;

  // Initialize all LEDs to be off
  PORTC = 0x00;
}

void setupSwitches(){
  // Initialize all switches input pullup
  DDRD = ~DMASK; PORTD = 0xFF;                        // D
  DDRC = DDRC & (~CMASK); PORTC = PORTC | (1<<DDC7);  // C
  DDRB = ~BMASK; PORTB = 0xFF;                        // B

  // Enable input pins
  PCMSK2 = 0xFF;      // D
  PCMSK1 = ~CMASK;    // C
  PCMSK0 = ~BMASK;    // B

  // Clear interrupt flags (PCIF), and enable interrupts (PCIE)
  PCIFR = 1<<PCIF2 | 1<<PCIF1 | 1<<PCIF0;    // PCIF2 -> D, PCIF1 -> C, PCIF0 -> B
  PCICR = 1<<PCIE2 | 1<<PCIE1 | 1<<PCIE0;    // PCIE2 -> D, PCIE1 -> C, PCIE0 -> B
}

void setup(){
  // Power Reduction
  PRR = 1<<PRADC | 1<<PRSPI;  // shutdown ADC and SPI

  // Setup GPIO
  setupLights();
  setupSwitches();

  // Setup I2C
  Wire.begin(I2CADDRESS);
  Wire.onRequest(sendVect);
  Wire.onReceive(setLights)
}



/************ OPERATION ************/

void displayNextRow(){
  PORTC = PORTC & ~(0x0F);   // reset PC0~PC3 to 0
  row = (row+1) % 4;         // 0 <= row <= 3

  uint8_t bits = lights >> (row*4) & 0x0F;   // look at "lights" 4 bits at a time

  PORTA = ~bits;            // set column information
  PORTC = PORTC | 1<<row;   // enable row
}

int readSwitches(){
  int states, count = 0, lastRead = -1;

  int bStates = 0, cStates = 0;

  do {
    bStates = PINB & BMASK;  // PB0, PB1, PB2, PB3, PB4, PB5, PB7
    cStates = PINC & CMASK;  // PC7
    bStates = bStates | (cStates>>1);

    states = ~(bStates<<8 | PIND);  
    count++;

    if(lastRead != states)
      count = 0;

    lastRead = states;
  } while(count < 7);     // debouncing

  return states;
}

void updateVect(){
  // Update switch states
  prevSwitchStates = switchStates;
  switchStates = readSwitches();

  // Find all switches "just pressed"
  int toggle = ~prevSwitchStates & switchStates;  // 0 -> 1 = just pressed

  // Update lights
  lights = lights ^ toggle;
}



/************ INTERRUPTS ***********/

// 250Hz interrupt
ISR(TIMER1_COMPA_vect){ displayNextRow(); }

// PORTD switch interrupt
ISR(PCINT2_vect){ updateVect(); }

// PORTC switch interrupt
ISR(PCINT1_vect){ updateVect(); }

// PORTB switch interrupt
ISR(PCINT0_vect){ updateVect(); }



/********* ON I2C REQUEST **********/

void sendVect(){
  int sendData = lights;

  Wire.write(sendData & 0xFF);      // send first row (1 byte)
  Wire.write(sendData>>8 & 0xFF);   // send second row (1 byte)
}

void setLights(){
  uint8_t lowBits = Wire.read();
  uint8_t highBits = Wire.read();

  lights = highBits<<8 | lowBits;
}



/*************** LOOP **************/

void loop(){}

