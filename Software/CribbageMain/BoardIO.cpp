#include "BoardIO.h"
#define BOARDIO_BUTTON_0 6
#define BOARDIO_BUTTON_1 9
#define BOARDIO_BUTTON_2 10
#define BOARDIO_BUTTON_3 11
#define BOARDIO_BUTTON_4 13
#define BOARDIO_BUTTON_5 14
#define BOARDIO_BUTTON_6 15
#define BOARDIO_BUTTON_7 1
#define BOARDIO_BUTTON_8 2
#define BOARDIO_BUTTON_9 3
#define BOARDIO_BUTTON_T 12
#define BOARDIO_BUTTON_J 16
#define BOARDIO_BUTTON_Q 4
#define BOARDIO_BUTTON_K 18
#define BOARDIO_BUTTON_P1 22
#define BOARDIO_BUTTON_P2 21
#define BOARDIO_BUTTON_UNDO 05
#define BOARDIO_BUTTON_UP 23
#define BOARDIO_BUTTON_UP_FAR 19
#define BOARDIO_BUTTON_DOWN 20
#define BOARDIO_BUTTON_DOWN_FAR 18
#define BOARDIO_BUTTON_P2_FAR 17
#define BOARDIO_BUTTON_SCORE 7

const unsigned char BoardIO::SEVEN_SEG_NUMS[10] = {0b11111100, 0b01100000, 0b11011010,
                                                0b11110010, 0b01100110, 0b10110110, 0b10111110, 
                                                0b11100000,0b11111110, 0b11110110};
/**
* Initializes the data for the game
*/
BoardIO::BoardIO()
{
    P1DIR = (1 << SHIFT_CLOCK_PIN) | (1 << SERIAL_DATA_PIN) | (1 << STORAGE_CLOCK_PIN);
    game = CribbageGame();
    for(int i = 0; i < NUM_SEVEN_SEGS; i++)
    {
        sevenSegments[i] = SEVEN_SEG_BLANK;
    }
    displayState = 0;
    buttonEnabled = 0;
    buttonDisableDelay = 0;
}

/**
* This refreshes the display
*/
void BoardIO::updateDisplay()
{
    //5 Seven Segments, 4 Pegs, LCM = 20
    displayState = (displayState + 1) % 20;
    int peg, rowPosition, rowOn, rgb;
    bool player2;
    if(buttonDisableDelay == 0)
    {
        if(buttonPressed())
        {
            handleButton();
            buttonDisableDelay = BUTTON_DISABLE_TIME;
        }
    }
    else
    {
        buttonDisableDelay--;
    }
    if((displayState % 4) == 0)
    {
        player2 = false;
        peg = game.getPegLocation(CribbageGame::P1, CribbageGame::FRONT);
    }
    else if((displayState % 4) == 1)
    {
        player2 = false;
        peg = game.getPegLocation(CribbageGame::P1, CribbageGame::BACK);
    }
    else if((displayState % 4) == 2)
    {
        player2 = true;
        peg = game.getPegLocation(CribbageGame::P2, CribbageGame::FRONT);
    }
    else
    {
        player2 = true;
        peg = game.getPegLocation(CribbageGame::P2, CribbageGame::BACK);
    }
    if(peg == 121)
    {
        rowPosition = 10; // Don't display anything on board
        if(player2)
        {
            rgb = 4; //Blue
        }
        else
        {
            rgb = 3; //Red + Green
        }
    }
    else
    {
        rgb = 0;
        rowOn = calcRow(player2, peg);
        rowPosition = calcLED(peg);
    }
    unsigned char sevenDispSelect = displayState % 5;
    buttonEnabled = (buttonEnabled + 1) % NUM_BUTTONS;
    for(int i = 1; i <= NUM_BUTTONS; i++)
    {
        if(i == buttonEnabled)
        {
            shiftOutHigh();//Set Serial out high and cycle clock
        }
        else
        {
            shiftOutLow();//Set Serial out low and cycle clock
        }
    }
    for(int i = 1; i <= NUM_ROWS; i++)
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
    for(int i = 0; i < NUM_DISPLAY_SEGMENTS; i++)
    {
        if(sevenSegments[sevenDispSelect] & (1 << i))
        {
            shiftOutHigh();//Set Serial out low and cycle clock
        }
        else
        {
            shiftOutLow();//Set Serial out high and cycle clock
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
    for(int i = 0; i < NUM_RGB_LINES; i++)
    {
        if((1 << i) & rgb)
        {
            shiftOutLow();//Set Serial out low and cycle clock
        }
        else
        {
            shiftOutHigh();//Set Serial out high and cycle clock
        }
    }
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

void BoardIO::shiftOutHigh()
{
    P1OUT = SERIAL_HIGH; //Serial clock low and serial data high
    P1OUT = SERIAL_HIGH_CLOCK; //Clock goes high
}

void BoardIO::shiftOutLow()
{
    P1OUT = SERIAL_LOW; //Serial clock and serial data low
    P1OUT = SERIAL_LOW_CLOCK; //Clock goes high
}

void BoardIO::pulseStorageClock()
{
    P1OUT = 0;
    P1OUT = 1 << STORAGE_CLOCK_PIN; //Set Storage clock to high
}

bool BoardIO::buttonPressed()
{
    return ((P1IN & (1 << BUTTON_IN_PIN)));
}

/**Returns the row that is used to display the peg
*Row 1/2  -1 through 30
*Row 3/4  31 through 60
*Row 5/6  61 through 90
*Row 7/8  91 through 120
*/
int BoardIO::calcRow(bool player2, int peg)
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
int BoardIO::calcLED(int peg)
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

/**
* This responds appropriately to the push of the enabled button
*/
void BoardIO::handleButton()
{
	unsigned char disp1 = buttonEnabled % 10;
	unsigned char disp2 = buttonEnabled / 10;
	sevenSegments[0] = SEVEN_SEG_NUMS[disp1];
	sevenSegments[1] = SEVEN_SEG_NUMS[disp2];
	// switch( buttonEnabled )
	// {
		// case BOARDIO_BUTTON_0:
			
			// break;
		// case BOARDIO_BUTTON_1:
		
			// break;
		// case BOARDIO_BUTTON_2:
		
			// break;
		// case BOARDIO_BUTTON_3:
			
			// break;
		// case BOARDIO_BUTTON_4:
		
			// break;
		// case BOARDIO_BUTTON_5:
		
			// break;
		// case BOARDIO_BUTTON_6:
			
			// break;
		// case BOARDIO_BUTTON_7:
		
			// break;
		// case BOARDIO_BUTTON_8:
		
			// break;
		// case BOARDIO_BUTTON_8:
			
			// break;
		// case BOARDIO_BUTTON_9:
			
			// break;
		// case BOARDIO_BUTTON_T:
		
			// break;
		// case BOARDIO_BUTTON_J:
		
			// break;
		// case BOARDIO_BUTTON_Q:
			
			// break;
		// case BOARDIO_BUTTON_K:
		
			// break;
		// case BOARDIO_BUTTON_UP:
		
			// break;
		// case BOARDIO_BUTTON_UP_FAR:
			
			// break;
		// case BOARDIO_BUTTON_DOWN:
		
			// break;
		// case BOARDIO_BUTTON_DOWN_FAR:
		
			// break;
        // case BOARDIO_BUTTON_P1:
		
			// break;
        // case BOARDIO_BUTTON_P2:
		
			// break;
        // case BOARDIO_BUTTON_P2_FAR:
		
			// break;
        // case BOARDIO_BUTTON_UNDO:
		
			// break;
        // case BOARDIO_BUTTON_SCORE:
		
			// break;
	// }
}
