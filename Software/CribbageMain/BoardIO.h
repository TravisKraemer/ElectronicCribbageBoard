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
	static const int SHIFT_CLOCK_PIN = 2; // Pin 1_2
	static const int SERIAL_DATA_PIN = 0; // Pin 1_0
	static const int STORAGE_CLOCK_PIN = 1; // Pin 1_1
	static const int BUTTON_IN_PIN = 3; // Pin 1_3

	static const unsigned char SERIAL_HIGH = 0x01;
	static const unsigned char SERIAL_LOW = 0x00;
	static const unsigned char SERIAL_LOW_CLOCK = 0x04;
	static const unsigned char SERIAL_HIGH_CLOCK = 0x05;
	//---------------------------------------------------
	//Display Constants
	//---------------------------------------------------
	static const int NUM_BUTTONS = 24; //23 Buttons connected, 1 output unused
	static const int NUM_ROWS = 8; //8 Different rows of LEDs
	static const int NUM_DISPLAY_SEGMENTS = 8; //7 segment with dot
	static const int NUM_SEVEN_SEGS = 5; //5 7 segment displays
	static const int NUM_RGB_LINES = 3; //1 for each color
	static const int NUM_LEDS_PER_ROW = 32; //max 32 LEDs per row (some have 30)
	static const unsigned char SEVEN_SEG_NUMS[10];
    static const unsigned char SEVEN_SEG_A = 0b11101110;
	static const unsigned char SEVEN_SEG_T = 0b00011110;
	static const unsigned char SEVEN_SEG_J = 0b01111000;
	static const unsigned char SEVEN_SEG_Q = 0b11111101;
	static const unsigned char SEVEN_SEG_K = 0b01101110;
    static const unsigned char SEVEN_SEG_H = 0b01101110;
    static const unsigned char SEVEN_SEG_D = 0b11111100;
    static const unsigned char SEVEN_SEG_C = 0b10011100;
    static const unsigned char SEVEN_SEG_S = 0b10110110;
    static const unsigned char SEVEN_SEG_BLANK = 0b00000000;
	static const unsigned char BUTTON_DISABLE_TIME = 20;
    
    //---------------------------------------------------
	//Entry Constants
	//---------------------------------------------------
    static const unsigned char MANUAL_SCORE_ENTRY_MODE = 0;
    static const unsigned char HAND_ENTRY_MODE = 1;
    static const unsigned char NUM_MODES = 1;
    static const unsigned char MAX_HAND_SCORE = 29;
    static const unsigned char TEN = 9;
    static const unsigned char JACK = 10;
    static const unsigned char QUEEN = 11;
    static const unsigned char KING = 12;
    static const unsigned char SUIT_OFFSET = 13;
    static const unsigned char HEARTS = 0;
    static const unsigned char SPADES = 1;
    static const unsigned char DIAMONDS = 2;
    static const unsigned char CLUBS = 3;
    
	unsigned char displayState;
	unsigned char buttonEnabled;
    unsigned char buttonDisableDelay;
	unsigned char sevenSegments[NUM_SEVEN_SEGS];
    unsigned char entryMode;
    signed char enteredScore;
    unsigned char enteredCards[5];
    unsigned char enteredCardSelected;
    bool currentCardSuitEntered;
    
    CribbageGame game;
	
    //Helper methods for IO
	void shiftOutHigh();
	void pulseStorageClock();
	void shiftOutLow();
    bool buttonPressed();

    //Helper methods to calculate what to Shift out to enable the right pin
	int calcRow(bool player2, int peg);
	int calcLED(int peg);
    
    /**
	* This responds appropriately to the push of the enabled button
	*/
	void handleButton();
    
    /**
    *Initializes the data entered 
    */
    void initializeEntryData();
    
    /**
    * Uses the entered data to set the seven segment displays appropriately
    */
    void updateSevenSegData()
public:
    /**
    * This refreshes the display
    */
    void updateDisplay();
    
    /**
    * Initializes the data for the game
    */
    BoardIO();
};
#endif