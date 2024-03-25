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

ValidationResult Board::SetCell(int x, int y, int value)
{
    ValidationResult validateResult;

    if (cells[x][y].IsGenerated)
    {
        validateResult.IsValid = false;
        validateResult.Message = "Cell is generated";
        return validateResult;
    }

    validateResult = Validate(x, y, value);

    if (validateResult.IsValid)
    {
        cells[x][y].Value = value;
        cells[x][y].IsFilled = true;
        return validateResult;
    }

    return validateResult;
}

void Board::ClearCell(int x, int y)
{
    cells[x][y].Value = 0;
    cells[x][y].IsFilled = false;
    cells[x][y].IsGenerated = false;
}

ValidationResult Board::Validate(int x, int y, int value)
{ 
    ValidationResult validateResult;

    for (int i = 0; i < 9; ++i) 
    {
        if (cells[x][i].Value == value)
        {
            validateResult.IsValid = false;
            validateResult.Message = "Invalid row";
            return validateResult;
        }
    }

    for (int i = 0; i < 9; ++i) 
    {
        if (cells[i][y].Value == value)
        {
            validateResult.IsValid = false;
            validateResult.Message = "Invalid column";
            return validateResult;
        }
    }

    int x0 = (x / 3) * 3;
    int y0 = (y / 3) * 3;

    for (int i = 0; i < 3; ++i) 
    {
        for (int j = 0; j < 3; ++j) 
        {
            if (cells[x0 + i][y0 + j].Value == value)
            {
                validateResult.IsValid = false;
                validateResult.Message = "Invalid square";
                return validateResult;
            }
        }
    }

    validateResult.IsValid = true;
    validateResult.Message = "Valid move";
    return validateResult;
}

void Board::DrawBoard()
{
    for (int i = 0; i < 9; ++i) 
    {
        for (int j = 0; j < 9; ++j) 
        {
            if (cells[i][j].IsFilled)
            {
                cout << cells[i][j].Value << " ";
            }
            
            else
            {
                cout << "- ";
            }

            if (j % 3 == 2)
            {
                cout << " ";
            }
        }

        if (i % 3 == 2)
        {
            cout << endl;
        }
        
        cout << endl;
    }
}

bool Board::GenerateCell(int x, int y, int value)
{
    if (Validate(x, y, value).IsValid)
    {
        cells[x][y].Value = value;
        cells[x][y].IsFilled = true;
        cells[x][y].IsGenerated = true;
        return true;
    }

    return false;
}