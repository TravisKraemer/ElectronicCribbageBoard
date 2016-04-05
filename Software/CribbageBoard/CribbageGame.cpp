/**
Default Constructor, initializes the peg locations and undo history data
*/
CribbageGame::CribbageGame();
{
    currentPosition = 0;
    numUndoLeft = 0;
    pegs[P1 + FRONT][currentPosition] = 0;
    pegs[P2 + FRONT][currentPosition] = 0;
    pegs[P1 + BACK][currentPosition] = -1;
    pegs[P2 + BACK][currentPosition] = -1;
}
/**
Returns the location of the peg specified as a signed char
params(in, in)
unsigned char player - Use the class constants to specify which player
unsigned char peg - Use the class constants to specify front or back peg
*/
signed char CribbageGame::getPegLocation(unsigned char player, unsigned char peg)
{
    return pegs[player + peg][currentPosition];
}
/**
Moves the pegs by the amount entered. Can be positive or negative.
Both the front and back pegs for the player are updated.
params(in, in)
unsigned char player - Use the class constants to specify which player
signed char amount - the number of points to move the player
*/
void CribbageGame::addPoints(unsigned char player, signed char amount)
{
    unsigned char prevPosition = currentPosition;
    currentPosition = (currentPosition + 1) % (MAX_UNDOS + 1);
    numUndoLeft++;
    if(numUndoLeft > MAX_UNDOS)
    {
        numUndoLeft = MAX_UNDOS;
    }
    if(amount > 0)
    {
        pegs[player + BACK][currentPosition] = pegs[player + FRONT][prevPosition];
        //This cannot be moved before previous statement in case MAX_UNDOS is 0
        //In that case, prevPosition == currentPosition and the two pegs would be equal
        pegs[player + FRONT][currentPosition] = amount + pegs[player + FRONT][prevPosition];
    }
    else
    {
        pegs[player + FRONT][currentPosition] = amount + pegs[player + FRONT][prevPosition];
        //Ensure back peg never is ahead of front peg
        if(pegs[player + BACK][currentPosition] >= pegs[player + FRONT][currentPosition])
        {
            pegs[player + BACK][currentPosition] = pegs[player + FRONT][currentPosition] - 1;
        }
    }
}

/**
Reverts the current scores back to the previous score
Return - true if possible, false if not
*/
bool CribbageGame::undoLastChange()
{
    if(numUndoLeft > 0)
    {
        //If currentPosition = 2, MAX_UNDOS = 4
        //(2+4)%(4+1) = 6%5 = 1, same as subtracting 1
        //This way ensures that it works if currentPosition = 0
        currentPosition = (currentPosition + MAX_UNDOS) % (MAX_UNDOS + 1);
        numUndoLeft--;
        return true;
    }
    else
    {
        return false;
    }
}
