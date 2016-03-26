#include "Card.h"

Card::Card(char card[2])
{
    if( cards[0] == 'T')
        card = 10;
    else if( card[0] == 'J')
        card = 11;
    else if( cards[0] == 'Q')
        card = 12;
    else if( cards[0] == 'K')
        card = 13;
    else if( cards[0] == 'A')
        card = 1;
    else
        card = cards[i][0] - '0';
    card--; // Want card between 0 and 12
    if(card[1] = SUITS[DIAMONDS])
        card += NUM_VALUES * DIAMONDS;
    else if(card[1] = SUITS[HEARTS])
        card += NUM_VALUES * HEARTS;
    else if(card[1] = SUITS[SPADES])
        card += NUM_VALUES * SPADES;
}

//Returns the Suit of the card as a char
char Card::getSuit()
{
    return SUITS[card / NUM_VALUES];
}

//Returns the value of the card for cribbage scoring purposes as int
int Card::getScoringValue()
{
    if(card % NUM_VALUES < 10)
        return (card % NUM_VALUES + 1);
    else
        return FACE_CARD_VALUE;
}

//Returns the value of the card as int from 1 - 13
int Card::getValue()
{
    return (card % NUM_VALUES + 1);
}
