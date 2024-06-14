#include "SudokuGenerator.h"

// Constructor for SudokuGenerator with given difficulty
SudokuGenerator::SudokuGenerator(int difficultyGiven) {
    // Create a new Sudoku9 object
    Sudoku9* sudoku = new Sudoku9();

    // Generate diagonal numbers in the Sudoku grid
    generateDiagonal(sudoku);


    // Set the Sudoku grid as filled
    setSudokuFilled(fill(sudoku));

    // Set the difficulty level
    setDifficulty(difficultyGiven);

    // Delete numbers based on the chosen difficulty level
    deleteBasedOnDifficulty();
}

// Constructor for SudokuGenerator with given difficulty and an existing Sudoku9 grid
SudokuGenerator::SudokuGenerator(int difficultyGiven, Sudoku9* unfinishedSudoku) {
    
    // Set the Sudoku grid as filled
    setSudokuFilled(fill(unfinishedSudoku));

    // Set the difficulty level
    setDifficulty(difficultyGiven);

    // Delete numbers based on the chosen difficulty level
    deleteBasedOnDifficulty();
}

// Get the filled Sudoku grid
Sudoku9* SudokuGenerator::getSudokuFilled() {
    return sudokuFilled;
}

// Get the Sudoku grid for the player
Sudoku9* SudokuGenerator::getSudokuForPlayer() {
    return sudokuForPlayer;
}

// Get the difficulty level
int SudokuGenerator::getDifficulty() {
    return difficulty;
}

// Set the Sudoku grid for the player
void SudokuGenerator::setSudokuForPlayer(Sudoku9* newSudokuForPlayer) {
    sudokuForPlayer = newSudokuForPlayer;
}

// Set the filled Sudoku grid
void SudokuGenerator::setSudokuFilled(Sudoku9* newSudokuFilled) {
    sudokuFilled = newSudokuFilled;
}

// Set the difficulty level
void SudokuGenerator::setDifficulty(int newDifficulty) {
    difficulty = newDifficulty;
}

// Generate diagonal numbers in the Sudoku grid
void SudokuGenerator::generateDiagonal(Sudoku9* sudoku) {
    for (int repeat = 0; repeat < 3; ++repeat) {
        std::vector<int> nums = shuffle(std::vector<int> {1, 2, 3, 4, 5, 6, 7, 8, 9});
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                sudoku->table[i + repeat * 3][j + repeat * 3] = nums[nums.size() - 1];
                nums.pop_back();
            }
        }
    }
}

// Fill the Sudoku grid
Sudoku9* SudokuGenerator::fill(Sudoku9* sudoku) {
    Sudoku9* sudokuUnsolved(sudoku);
    while (!isFull(sudokuUnsolved)) {
        int* field = returnEmptyFieldWithLeastPossibilities(sudokuUnsolved);
        for (int number : whatToPut(sudokuUnsolved, field[0], field[1])) {
            if (isAbleToPut(sudokuUnsolved, field[0], field[1], number)) {
                sudokuUnsolved->table[field[0]][field[1]] = number;
            }
        }
        if (isDone(sudokuUnsolved) && (!isFull(sudokuUnsolved))) {
            Sudoku9* sudokuNewGenerated = new Sudoku9();
            generateDiagonal(sudokuNewGenerated);
            return fill(sudokuNewGenerated);
        }
    }
    return sudokuUnsolved;
}

// Erase numbers in a Sudoku box to create the base Sudoku grid
void SudokuGenerator::eraseToBase(Sudoku9* sudoku) {
    for (int iBox = 0; iBox < 3; ++iBox) {
        for (int jBox = 0; jBox < 3; ++jBox) {
            int boxRow = 3 * iBox;
            int boxCol = 3 * jBox;
            for (int m = 0; m < 3; ++m) {
                int rand1 = genRandNum(3);
                int rand2 = genRandNum(3);

                if (sudoku->table[rand1 + boxRow][rand2 + boxCol] != 0) {
                    sudoku->table[rand1 + boxRow][rand2 + boxCol] = 0;
                }
                else if (sudoku->table[rand2 + boxRow][rand1 + boxCol] != 0) {
                    sudoku->table[rand2 + boxRow][rand1 + boxCol] = 0;
                }
                else if (sudoku->table[rand2 + boxRow][rand2 + boxCol] != 0) {
                    sudoku->table[rand2 + boxRow][rand2 + boxCol] = 0;
                }
                else if (sudoku->table[rand1 + boxRow][rand1 + boxCol] != 0) {
                    sudoku->table[rand1 + boxRow][rand1 + boxCol] = 0;
                }
            }
        }
    }
}

// Erase one number in the Sudoku grid
void SudokuGenerator::eraseOne(Sudoku9* sudoku) {
    while (true) {
        int rand1 = genRandNum(10);
        int rand2 = genRandNum(10);

        if (sudoku->table[rand1][rand2] != 0) {
            sudoku->table[rand1][rand2] = 0;
            //std::cout << "erased: " << rand1 << ' ' << rand2 << std::endl;
            return;
        }
        //std::cout << "already 0 here: " << rand1 << ' ' << rand2 << std::endl;
    }
}

// Count the number of zeros in the Sudoku grid
int numberOfZeros(Sudoku9* sudoku) {
    int counter = 0;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (sudoku->table[i][j] == 0) {
                ++counter;
            }
        }
    }
    return counter;
}

// Delete numbers in the Sudoku grid based on the difficulty level
void SudokuGenerator::deleteBasedOnDifficulty() {
    Sudoku9* sudokuCopy = new Sudoku9(getSudokuFilled());
    eraseToBase(sudokuCopy);
    while (numberOfZeros(sudokuCopy) < (getDifficulty() * 7) + 27) {
        eraseOne(sudokuCopy);
    }
    setSudokuForPlayer(sudokuCopy);
}
