#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <iostream>
#include <random>
#include <algorithm>
#include "board.h"
#include "templateExtractor.h"

using namespace std;

class GameManager
{
private:
    Board board;
    int CellsRemaining = 0;
    bool CheckWin();

public:
    void TrySetCell(int x, int y, int value);
    bool GenerateBoard(int row, int col, default_random_engine &seed);
    bool GenerateBoardFromTemplate();
    void AskInput();
    void DrawBoard() { board.DrawBoard(); }
    void EraseCells(int amount, default_random_engine &seed);
    void GameLoop();

    GameManager()
    {
        board = Board();
    }
};

#endif // GAMEMANAGER_H