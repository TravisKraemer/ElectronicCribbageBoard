#include"../CribbageBoard/CribbageGame.h"
#include <iostream>

void checkPegs(CribbageGame game, int p1f, int p1b, int p2f, int p2b);

int main()
{
    CribbageGame game = CribbageGame();
    checkPegs(game, 0, 0, -1, -1);
    game.addPoints(CribbageGame::P1, 5);
    checkPegs(game, 5, 0, 0, -1);
    return 0;
}

void checkPegs(CribbageGame game, int p1f, int p2f, int p1b, int p2b)
{
    if(game.getPegLocation(CribbageGame::P1,CribbageGame::FRONT) != p1f)
    {
        std::cout << "P1 FRONT incorrect: expected " << p1f << " got "
                 << (int) game.getPegLocation(CribbageGame::P1,CribbageGame::FRONT)
                 << std::endl;
    }
    if(game.getPegLocation(CribbageGame::P2,CribbageGame::FRONT) != p2f)
    {
        std::cout<< "P2 FRONT incorrect: expected " << p2f << " got "
                 << (int) game.getPegLocation(CribbageGame::P2,CribbageGame::FRONT)
                 << std::endl;
    }
    if(game.getPegLocation(CribbageGame::P1,CribbageGame::BACK) != p1b)
    {
        std::cout<< "P1 BACK incorrect: expected " << p1b << " got "
                 << (int) game.getPegLocation(CribbageGame::P1,CribbageGame::BACK)
                 << std::endl;
    }
    if(game.getPegLocation(CribbageGame::P2,CribbageGame::BACK) != p2b)
    {
        std::cout<< "P2 BACK incorrect: expected " << p2b << " got "
                 << (int) game.getPegLocation(CribbageGame::P2,CribbageGame::BACK)
                 << std::endl;
    }
}
