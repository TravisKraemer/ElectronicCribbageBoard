/*
This class stores the data for a cribbage game and has useful methods
for keeping track of scoring.
*/
#ifndef CRIBBAGEGAME_H
#define CRIBBAGEGAME_H
#include <msp430.h>
class CribbageGame
{
private:
    static const unsigned char ARRAY_SIZE = 4;
    static const unsigned char MAX_UNDOS = 4;
    signed char pegs[ARRAY_SIZE][MAX_UNDOS + 1];
    //Needs 4 Bytes of RAM per UNDO
    unsigned char currentPosition;
    unsigned char numUndoLeft;
public:
    static const unsigned char P1 = 0;
    static const unsigned char P2 = 1;
    static const unsigned char FRONT = 0;
    static const unsigned char BACK = 2;
    CribbageGame();
    signed char getPegLocation(unsigned char player, unsigned char peg);
    void addPoints(unsigned char player, signed char amount);
    bool undoLastChange();
};
#endif
