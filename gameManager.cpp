#include <iostream>
#include <random>
#include <algorithm>
#include "board.h"
#include "templateExtractor.h"
#include "gameManager.h"

using namespace std;

void GameManager::TrySetCell(int x, int y, int value)
{
    cout << endl << endl;

    ValidationResult validateResult = board.SetCell(x, y, value);

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

bool GameManager::GenerateBoardFromTemplate()
{
    string path = "Templates/template1.txt";

    TemplateExtractor templateExtractor = TemplateExtractor();

    vector<vector<int>> cellData = templateExtractor.ExtractTemplate(path);

    for (int i = 0; i < 9; ++i) 
    {
        for (int j = 0; j < 9; ++j) 
        {
            if (cellData[i][j] == 0)
            {
                board.ClearCell(i, j);
                ++CellsRemaining;
                continue;
            }
            
            board.GenerateCell(i, j, cellData[i][j]);
            --CellsRemaining;
        }
    }

    return true;
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