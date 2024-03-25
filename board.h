#ifndef BOARD_H
#define BOARD_H

#include "cell.h"
#include <iostream>

using namespace std;

class ValidationResult
{
public:
    bool IsValid;
    string Message;
};

class Board
{
public:
    ValidationResult SetCell(int x, int y, int value);
    bool GenerateCell(int x, int y, int value);
    void ClearCell(int x, int y);
    void DrawBoard();

    Board()
    {
        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                cells[i][j].Value = 0;
                cells[i][j].IsFilled = false;
                cells[i][j].IsGenerated = false;
            }
        }
    }

private:
    Cell cells[9][9];
    ValidationResult Validate(int x, int y, int value);
};

#endif // BOARD_H