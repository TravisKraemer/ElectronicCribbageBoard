#include "BoardIO.h"
void BoardIO::shiftOutHigh()
{
	  P1OUT = SERIAL_HIGH; //Serial clock low and serial data high
	  P1OUT = SERIAL_HIGH_CLOCK; //Clock goes high
}

void BoardIO::pulseStorageClock()
{
  P1OUT = 0;
  P1OUT = 1 << STORAGE_CLOCK_PIN; //Set Storage clock to high
}

//Returns the row that is used to display the peg
//Row 1/2  -1 through 30
//Row 3/4  31 through 60
//Row 5/6  61 through 90
//Row 7/8  91 through 120
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
	sevenSegments[1] = SEVEN_SEG_NUMS[Disp2];
	// switch( buttonEnabled )
	// {
		// case 1:
			
			// break;
		// case 2:
		
			// break;
		// case 3:
		
			// break;
		// case 4:
			
			// break;
		// case 5:
		
			// break;
		// case 6:
		
			// break;
		// case 7:
			
			// break;
		// case 8:
		
			// break;
		// case 9:
		
			// break;
		// case 10:
			
			// break;
		// case 11:
			
			// break;
		// case 12:
		
			// break;
		// case 13:
		
			// break;
		// case 14:
			
			// break;
		// case 15:
		
			// break;
		// case 16:
		
			// break;
		// case 17:
			
			// break;
		// case 18:
		
			// break;
		// case 19:
		
			// break;
	// }
}