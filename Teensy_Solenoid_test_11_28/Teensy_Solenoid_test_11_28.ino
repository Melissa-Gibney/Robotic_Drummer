// Teensy Driving a Motor Test Code
// Started 11/28/23
// Last Updated 11/28/23

// Variable Declarations
// Assign PINS
int LEDPINB = 28;
int LEDPING = 29;
int LEDPINR = 30;
int BUTTON1 = 32;
int MOTORPIN = 33;

// Button State Flag
int button1_state;


void setup() {
  // put your setup code here, to run once:

  // Set Pinmodes
  pinMode(LEDPINB,OUTPUT);
  pinMode(LEDPING,OUTPUT);
  pinMode(LEDPINR,OUTPUT);
  pinMode(BUTTON1,INPUT);
  pinMode(MOTORPIN,OUTPUT);

  // Initialize the LEDS to start off
  digitalWrite(LEDPINB,LOW);
  digitalWrite(LEDPING,LOW);
  digitalWrite(LEDPINR,HIGH);
  digitalWrite(MOTORPIN,LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  // read in the button state
  

  // Uncomment this Section to Have the Solenoid Automatically Turn On and Off
  /*digitalWrite(LEDPINR,LOW);
  digitalWrite(LEDPING,HIGH);
  digitalWrite(MOTORPIN,HIGH);

  delay(100);

  digitalWrite(LEDPINR,HIGH);
  digitalWrite(LEDPING,LOW);
  digitalWrite(MOTORPIN,LOW);
  
  delay(1000);
  */
  
  // Uncomment this Section to Turn the Solenoid On and Off with a Button
  /*
  button1_state = digitalRead(BUTTON1);
  if (button1_state)
  {
    digitalWrite(LEDPINB,HIGH);

    digitalWrite(MOTORPIN,HIGH);


  }
  else
  {
    digitalWrite(LEDPINB,LOW);
    digitalWrite(MOTORPIN,LOW);


  } */


}
