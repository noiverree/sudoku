#include <iostream>
#include <random>
#include <algorithm>
#include "board.cpp"

using namespace std;

class GameManager
{
    private:
        Board board;
        int CellsRemaining = 0;
        bool CheckWin();

    public:
        void TrySetCell(int x, int y, int value);
        bool GenerateBoard(int row, int col, default_random_engine& seed);
        void AskInput();
        void DrawBoard() { board.DrawBoard(); }
        void EraseCells(int amount, default_random_engine& seed);
        void GameLoop();

        GameManager()
        {
            board = Board();
        }
};

void GameManager::TrySetCell(int x, int y, int value)
{
    cout << endl << endl;

    ValidationResult validateResult = board.SetCell(x, y, value);

    board.DrawBoard();

    if (!validateResult.IsValid)
    {
        cout << "Cell set failed: " << validateResult.Message << endl;
    }

    else 
    {
        --CellsRemaining;
        cout << "Cells remaining: " << CellsRemaining << endl;
    }
}

bool GameManager::CheckWin()
{
    if (CellsRemaining == 0)
    {
        return true;
    }

    return false;
}

bool GameManager::GenerateBoard(int row, int col, default_random_engine& seed)
{
    if (row == 9)
    {
        return true;
    }

    int nextRow = col == 8 ? row + 1 : row;
    int nextCol = (col + 1) % 9;

    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    shuffle(nums.begin(), nums.end(), seed);

    for (int num : nums)
    {
        if (board.GenerateCell(row, col, num))
        {
            if (GenerateBoard(nextRow, nextCol, seed))
            {
                return true;
            }

            board.ClearCell(row, col);
        }
    }

    return false;
}

void GameManager::EraseCells(int amount, default_random_engine& seed)
{
    for (int i = 0; i < amount; ++i)
    {
        int x = seed() % 9;
        int y = seed() % 9;

        board.ClearCell(x, y);
        ++CellsRemaining;
    }
}

void GameManager::AskInput()
{
        int x, y, value;
        char comma;
        
        cout << "Input (x, y, value): ";

        if (!(cin >> x >> comma >> y >> comma >> value) || 
            x < 0 || x >= 9 || y < 0 || y >= 9 || value < 1 || value > 9 || comma != ',')
        {
            cout << "Invalid input. Please enter valid input in the format: x, y, value (0 <= x,y <= 8, 1 <= value <= 9)" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        TrySetCell(x, y, value);
        return;
}

void GameManager::GameLoop()
{
    while (true)
    {
        DrawBoard();
        AskInput();

        if (CheckWin())
        {
            break;
        }
    }

    cout << "You win!" << endl;
}