#ifndef BOARDIO_H
#define BOARDIO_H
#include "CribbageGame.h"
#include <msp430.h>
class BoardIO
{
private:
	/****************************************************
	******************PINS LIST**************************
	****************************************************/
	const int SHIFT_CLOCK_PIN = 2; // Pin 1_2
	const int SERIAL_DATA_PIN = 0; // Pin 1_0
	const int STORAGE_CLOCK_PIN = 1; // Pin 1_1
	const int BUTTON_IN_PIN = 3; // Pin 1_3

	const unsigned char SERIAL_HIGH = 0x01;
	const unsigned char SERIAL_LOW = 0x00;
	const unsigned char SERIAL_LOW_CLOCK = 0x04;
	const unsigned char SERIAL_HIGH_CLOCK = 0x05;
	//---------------------------------------------------
	//Display Constants
	//---------------------------------------------------
	const int NUM_BUTTONS = 24; //23 Buttons connected, 1 output unused
	const int NUM_ROWS = 8; //8 Different rows of LEDs
	const int NUM_DISPLAY_SEGMENTS = 8; //7 segment with dot
	const int NUM_SEVEN_SEGS = 5; //5 7 segment displays
	const int NUM_RGB_LINES = 3; //1 for each color
	const int NUM_LEDS_PER_ROW = 32; //max 32 LEDs per row (some have 30)
	
	static const unsigned char SEVEN_SEG_NUMS[10] = {0b11111100, 0b01100000, 0b11011010,
									0b11110010, 0b01100110, 0b10110110, 0b10111110, 
									0b11100000,0b11111110, 0b11110110};
	static const unsigned char SEVEN_SEG_T = 0b00011110;
	static const unsigned char SEVEN_SEG_J = 0b01111000;
	static const unsigned char SEVEN_SEG_Q = 0b11111101;
	static const unsigned char SEVEN_SEG_K = 0b01101110;
	
	unsigned char displayState;
	unsigned char buttonEnabled;
	unsigned char sevenSegments[NUM_SEVEN_SEGS];
	
	void shiftOutHigh();
	void pulseStorageClock();
	void shiftOutLow();


	/**Returns the row that is used to display the peg
	*Row 1/2  -1 through 30
	*Row 3/4  31 through 60
	*Row 5/6  61 through 90
	*Row 7/8  91 through 120
	*/
	int calcRow(bool player2, int peg);

	//Returns the position of the peg 
	int calcLED(int peg);

		
public:

	/**
	* This responds appropriately to the push of the enabled button
	*/
	void handleButton();
}
#endif