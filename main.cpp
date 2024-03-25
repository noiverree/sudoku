#include <iostream>
#include <random>
#include "gameManager.cpp"

using namespace std;

int main() 
{
    GameManager gameManager = GameManager();

    //default_random_engine generator(212121);
    //gameManager.GenerateBoard(0, 0, generator);
    //gameManager.EraseCells(60, generator);

    gameManager.GenerateBoardFromTemplate();
    gameManager.GameLoop();
    return 0;
}