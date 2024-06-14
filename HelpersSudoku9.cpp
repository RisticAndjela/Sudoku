#include "HelpersSudoku9.h"

// Check if it's possible to put a number 'num' in the given position (row, col) of the Sudoku board
bool isAbleToPut(Sudoku9* sudoku, int row, int col, int num) {
    int(*table)[9] = sudoku->getTable();

    if (table[row][col] == 0) {
        // Check if the number is not already in the same column
        for (int rows = 0; rows < 9; ++rows) {
            if (table[rows][col] == num) {
                return false;
            }
        }

        // Check if the number is not already in the same row
        for (int cols = 0; cols < 9; ++cols) {
            if (table[row][cols] == num) {
                return false;
            }
        }

        // Check if the number is not already in the 3x3 box
        int boxRow = (row / 3);
        int boxCol = (col / 3);

        for (int rows = 0; rows < 3; ++rows) {
            for (int cols = 0; cols < 3; ++cols) {
                if (table[rows + 3 * boxRow][cols + 3 * boxCol] == num) {
                    return false;
                }
            }
        }

        return true;
    }
    else {
        // The position is already filled
        return false;
    }
}

// Determine which numbers can be placed in the given position (row, col) of the Sudoku board
std::vector<int> whatToPut(Sudoku9* sudoku, int row, int col) {
    std::vector<int> numbers;
    for (int i = 1; i <= 9; ++i) {
        if (isAbleToPut(sudoku, row, col, i)) {
            numbers.push_back(i);
        }
    }
    return numbers;
}

// Check if the Sudoku board is unsolvable (contains an empty field with no possible numbers to put)
bool isUnsolvable(Sudoku9* sudoku) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (sudoku->table[i][j] == 0) {
                if (whatToPut(sudoku, i, j).empty()) {
                    // There are no possible numbers to put in the empty field
                    return true;
                }
            }
        }
    }
    return false;
}

// Check if the Sudoku board is completely filled and valid
bool isDone(Sudoku9 sudoku) {
    if (isUnsolvable(&sudoku)) {
        // If the board is unsolvable, it's considered done
        return true;
    }
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (whatToPut(&sudoku, i, j).size() > 0) {
                // There are still empty fields with possible numbers to put
                return false;
            }
        }
    }
    // All fields are filled with valid numbers
    return true;
}

// Check if the Sudoku board is completely filled
bool isFull(Sudoku9* sudoku) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (sudoku->table[i][j] == 0) {
                // There is an empty field
                return false;
            }
        }
    }
    // All fields are filled
    return true;
}

// Return the coordinates of an empty field with the least possible numbers to put
int* returnEmptyFieldWithLeastPossibilities(Sudoku9* sudoku) {
    int* coordinates = new int[2];
    int leastSize = 9;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (whatToPut(sudoku, i, j).size() > 0) {
                if (whatToPut(sudoku, i, j).size() < leastSize) {
                    coordinates[0] = i;
                    coordinates[1] = j;
                    leastSize = whatToPut(sudoku, i, j).size();
                }
            }
        }
    }
    return coordinates;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
// Shuffle the order of elements in a vector
std::vector<int> shuffle(std::vector<int> numbers) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(numbers.begin(), numbers.end(), gen);

    return numbers;
}

// Generate a random number between 0 and 'max' (exclusive)
int genRandNum(int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(0, max - 1);
    return distribution(gen);
}
