#include <iostream>
#include <vector>

const int SIZE = 9; // Size of the Sudoku grid (9x9)

// Function to print the Sudoku grid
void printGrid(const std::vector<std::vector<int>> &grid)
{
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            std::cout << grid[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

// Function to check if a number can be placed in a given position
bool isSafe(const std::vector<std::vector<int>> &grid, int row, int col, int num)
{
    // Check if 'num' is not in the current row, column, or 3x3 subgrid
    for (int x = 0; x < SIZE; x++)
    {
        if (grid[row][x] == num || grid[x][col] == num ||
            grid[row - row % 3 + x / 3][col - col % 3 + x % 3] == num)
        {
            return false;
        }
    }
    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(std::vector<std::vector<int>> &grid)
{
    int row, col;
    bool emptyCellFound = false;

    // Find an empty cell
    for (row = 0; row < SIZE; row++)
    {
        for (col = 0; col < SIZE; col++)
        {
            if (grid[row][col] == 0)
            {
                emptyCellFound = true;
                break;
            }
        }
        if (emptyCellFound)
            break;
    }

    // If there are no empty cells left, the puzzle is solved
    if (!emptyCellFound)
        return true;

    // Try placing digits from 1 to 9
    for (int num = 1; num <= SIZE; num++)
    {
        if (isSafe(grid, row, col, num))
        {
            grid[row][col] = num;

            // Recursively try to solve the puzzle
            if (solveSudoku(grid))
            {
                return true;
            }

            // Backtrack
            grid[row][col] = 0;
        }
    }
    return false;
}

int main()
{
    std::vector<std::vector<int>> grid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    std::cout << "Original Sudoku Puzzle:" << std::endl;
    printGrid(grid);

    if (solveSudoku(grid))
    {
        std::cout << "\nSolved Sudoku Puzzle:" << std::endl;
        printGrid(grid);
    }
    else
    {
        std::cout << "\nNo solution exists for the given Sudoku puzzle." << std::endl;
    }

    return 0;
}