#include "SudokuSolver.h"

// Solve one step of Sudoku puzzle
Sudoku9* oneSolved(Sudoku9* sudoku) {
    // Create a copy of the original Sudoku grid
    Sudoku9* sudokuUnsolved(sudoku);

    // Continue solving until the Sudoku grid is complete
    while (!isDone(sudokuUnsolved)) {
        // Find an empty field with the least possibilities
        int* field = returnEmptyFieldWithLeastPossibilities(sudokuUnsolved);

        // Try putting numbers in the empty field based on possibilities
        for (int number : whatToPut(sudokuUnsolved, field[0], field[1])) {
            // Check if the number can be placed in the Sudoku grid
            if (isAbleToPut(sudokuUnsolved, field[0], field[1], number)) {
                // Place the number in the Sudoku grid
                sudokuUnsolved->table[field[0]][field[1]] = number;
            }
        }
    }
    // Return the solved Sudoku grid
    return sudokuUnsolved;
}

// Solve the entire Sudoku puzzle
Sudoku9* solver(Sudoku9* sudoku) {
    // Solve one step of the Sudoku puzzle
    Sudoku9* sudokuAfterSolving(oneSolved(sudoku));

    // Check if the solved Sudoku is unsolvable
    if (isUnsolvable(sudokuAfterSolving)) {
        std::cout << "We couldn't solve the Sudoku puzzle.";
        // Return the original Sudoku grid (not modified)
        return sudoku;
    }

    // Return null pointer to indicate successful solving
    return nullptr;
}
