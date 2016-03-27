//---------------------------------------------------
//Display Constants
//---------------------------------------------------
const int NUM_BUTTONS = 24; //23 Buttons connected, 1 output unused
const int NUM_ROWS = 8; //8 Different rows of LEDs
const int NUM_DISPLAY_SEGMENTS = 8; //7 segment with dot
const int NUM_SEVEN_SEGS = 5; //5 7 segment displays
const int NUM_RGB_LINES = 3; //1 for each color
const int NUM_LEDS_PER_ROW = 32; //max 32 LEDs per row (some have 30)
//Seven Segment Characters          abcdefgh
const unsigned char SEVEN_SEG_1 = 0b01100000;
//---------------------------------------------------

//---------------------------------------------------
//PINS LIST
//---------------------------------------------------
const int SHIFT_CLOCK_PIN = 1; // Pin 1_0
const int SERIAL_DATA_PIN = 0; // Pin 1_1
const int STORAGE_CLOCK_PIN = 2; // Pin 1_2
const int BUTTON_IN_PIN = 3; // Pin 1_3

const int SERIAL_HIGH = 1 << SHIFT_CLOCK_PIN;
const int SERIAL_LOW = 0;
const int SERIAL_LOW_CLOCK = 1 << SHIFT_CLOCK_PIN;
const int SERIAL_HIGH_CLOCK = SERIAL_HIGH | SERIAL_LOW_CLOCK;
//---------------------------------------------------

//---------------------------------------------------
//Function Prototype Declarations
//---------------------------------------------------
int calcLED(int peg);
int calcRow(bool player2, int peg);
inline void shiftOutLow();
inline void shiftOutHigh();
inline void pulseStorageClock();
void updateDisplay(int button, unsigned char sevenChar, 
                    unsigned char sevenDispSelect, unsigned char rgb, bool player2, int peg);
//---------------------------------------------------
void setup()
{
  // put your setup code here, to run once:
  WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer
  P1DIR |= 1 << SHIFT_CLOCK_PIN | 1 << SERIAL_DATA_PIN | 1 << STORAGE_CLOCK_PIN; // Set pins to output direction
}

void loop()
{
  // put your main code here, to run repeatedly:
  int peg = -1;
  for(;;)
  {
    updateDisplay(0,SEVEN_SEG_1,0,255,false,peg);
    peg++;
    if(peg > 120)
    {
      peg = -1;
    }
    delay(100);
  }
}

//Updates the displays/LEDs with the data entered
//params(in,in,in,in)
//int button - number of button to be enabled
//unsigned char sevenChar - bits of the byte represent the segments to turn on MSB = a, LSB = h(dot)
//unsigned char sevenDispSelect - number of display to turn on (0, 1, 2, 3, or 4)
//unsigned char rgb - lowest three bits represent if color is on bit 0 - red, bit 1 - green, bit 2 - blue
//bool player2 - selects whether player 2 track is used
//int peg - position of peg (front starting position is 0, back is -1)
void updateDisplay(int button, unsigned char sevenChar, unsigned char sevenDispSelect, unsigned char rgb, bool player2, int peg)
{
  for(int i = 0; i < NUM_BUTTONS; i++)
  {
    if(i == button)
    {
      shiftOutHigh();//Set Serial out high and cycle clock
    }
    else
    {
      shiftOutLow();//Set Serial out low and cycle clock
    }
  }
  int rowOn = calcRow(player2, peg);
  for(int i = 0; i < NUM_ROWS; i++)
  {
    
    if(i == rowOn)
    {
      shiftOutLow();//Set Serial out low and cycle clock
    }
    else
    {
      shiftOutHigh();//Set Serial out high and cycle clock
    }
  }
  for(int i = 0; i < (1 << NUM_DISPLAY_SEGMENTS) ; i << 1)
  {
    if(sevenChar & i)
    {
      shiftOutLow();//Set Serial out low and cycle clock
    }
    else
    {
      shiftOutHigh();//Set Serial out high and cycle clock
    }
  }
  for(int i = 0; i < NUM_SEVEN_SEGS; i++)
  {
    if(i == sevenDispSelect)
    {
      shiftOutLow();//Set Serial out low and cycle clock
    }
    else
    {
      shiftOutHigh();//Set Serial out high and cycle clock
    }
  }
  for(int i = 0; i < (1 << NUM_RGB_LINES); i << 1)
  {
    if(i & rgb)
    {
      shiftOutLow();//Set Serial out low and cycle clock
    }
    else
    {
      shiftOutHigh();//Set Serial out high and cycle clock
    }
  }
  int rowPosition = calcLED(peg);
  for(int i = 0; i < NUM_LEDS_PER_ROW; i++)
  {
    if(rowPosition == i)
    {
      shiftOutHigh();//Set Serial out high and cycle clock
    }
    else
    {
      shiftOutLow();//Set Serial out low and cycle clock
    }
  }
  pulseStorageClock();
}

inline void shiftOutHigh()
{
  P1OUT = SERIAL_HIGH; //Serial clock low and serial data high
  P1OUT = SERIAL_HIGH_CLOCK; //Clock goes high
}

inline void pulseStorageClock()
{
  P1OUT |= 1 << STORAGE_CLOCK_PIN; //Set Storage clock to high
  P1OUT = 0; // set P1out to low
}

inline void shiftOutLow()
{
  P1OUT = SERIAL_LOW; //Serial clock and serial data low
  P1OUT = SERIAL_LOW_CLOCK; //Clock goes high
}

//Returns the row that is used to display the peg
//Row 1/2  -1 through 30
//Row 3/4  31 through 60
//Row 5/6  61 through 90
//Row 7/8  91 through 120
int calcRow(bool player2, int peg)
{
  if(peg < 1)
  {
    if(player2)
    {
      return 2;
    }
    else
    {
      return 1;
    }
  }
  else
  {
    int row = ((peg - 1) / 30) * 2 + 1;
    if(player2)
    {
      return row + 1;
    }
    else
    {
      return row;
    }
  }
}

//Returns the position of the peg 
int calcLED(int peg)
{
  //1st stretch 
  if(peg < 31)
  {
    return peg + 1;
  }
  //2nd Stretch reverses, 1st at 31
  else if (peg < 61)
  {
    return 62 - peg;
  }
  //3rd Stretch going same directino as 1st
  //61st peg at 2
  else if (peg < 91)
  {
    return peg - 59;
  }
  //4th stretch, same direction as 2nd
  //91st at 31, 120th at 2
  else
  {
    return 122 - peg;
  }
}

