#include <iostream>
#include <vector>

#define UNASSIGNED 0
#define N 9

using namespace std;

// Function to check whether it will be legal to assign num to the given row, col
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check if we find the same num in the similar row , we return false
    for (int x = 0; x <= 8; x++)
        if (grid[row][x] == num)
            return false;

    // Check if we find the same num in the similar column , we return false
    for (int x = 0; x <= 8; x++)
        if (grid[x][col] == num)
            return false;

    // Check if we find the same num in the particular 3*3 matrix, we return false
    int startRow = row - row % 3, startCol = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Takes a partially filled-in grid and attempts to assign values to all unassigned locations in such a way to meet the requirements for Sudoku solution (non-duplication across rows, columns, and boxes)
bool solveSudoku(int grid[N][N]) {
    int row, col;
    bool isEmpty = true;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == UNASSIGNED) {
                isEmpty = false;
                break;
            }
        }
        if (!isEmpty) {
            break;
        }
    }

    // No unassigned position is found, puzzle solved
    if (isEmpty) {
        return true;
    }

    // Consider digits 1 to 9
    for (int num = 1; num <= N; num++) {
        // Check if looks promising
        if (isSafe(grid, row, col, num)) {
            // Make tentative assignment
            grid[row][col] = num;

            // Return, if success
            if (solveSudoku(grid))
                return true;

            // Failure, unmake & try again
            grid[row][col] = UNASSIGNED;
        }
    }
    // This triggers backtracking
    return false;
}

// Utility function to print grid
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            cout << grid[row][col] << " ";
        cout << endl;
    }
}

int main() {
    int grid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(grid) == true)
        printGrid(grid);
    else
        cout << "No solution exists";

    return 0;
}
