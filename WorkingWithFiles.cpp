#include "WorkingWithFiles.h"
#include <iostream>
#include <fstream>
#include <sstream>





// Read Sudoku puzzles from a file
std::vector<Sudoku9*> readSudokuFromFile(std::string filename) {
    // Vector to store Sudoku puzzles read from the file
    std::vector<Sudoku9*> sudokuVector;

    // Open the file for reading
    std::ifstream inFile(filename);

    // Check if the file is opened successfully
    if (!inFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return sudokuVector;
    }

    // Temporary storage for each line of the file
    std::string line;

    // 2D array to store Sudoku table values
    int sudokuTable[9][9] = {};

    // Counter for the current row being processed
    int row = 0;

    // Read lines from the file
    while (std::getline(inFile, line)) {
        // Skip lines containing '-'
        if (line.find("-") != std::string::npos) {
            continue;
        }

        // Skip empty lines
        if (line.empty()) {
            continue;
        }

        // Extract numbers from the line and fill the Sudoku table
        std::vector<int> numbers;
        for (char i : line) {
            if (i != ' ' && i != '|') {
                numbers.push_back(static_cast<int>(i - '0'));
            }
        }
        for (int i = 0; i < 9; ++i) {
            sudokuTable[row][i] = numbers[i];
        }

        // Move to the next row
        ++row;

        // If a complete Sudoku grid is read, create a Sudoku9 object and add it to the vector
        if (row >= 9) {
            Sudoku9* sudokuNew = new Sudoku9(sudokuTable);
            sudokuVector.push_back(sudokuNew);
            row = 0;
        }
    }

    // Close the file
    inFile.close();

    // Return the vector of Sudoku puzzles
    return sudokuVector;
}

// Save a Sudoku puzzle to a file
void saveSudokuToFile(Sudoku9* sudoku, std::string filename) {
    // Open the file for writing, appending to the end of the file
    std::ofstream outFile(filename, std::ios::app);

    // Check if the file is opened successfully
    if (!outFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Write the interpreted Sudoku table to the file
    outFile << interpretTable(sudoku);

    // Add a newline character at the end
    outFile << '\n';

    // Close the file
    outFile.close();
}

// Convert a Sudoku table to a formatted string
std::string interpretTable(Sudoku9* sudoku) {
    std::string result;
    int(*table)[9] = sudoku->getTable();

    // Iterate over rows and columns of the Sudoku table
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            // Add the number to the result string
            result += std::to_string(table[row][col]);

            // Add formatting for Sudoku grid visualization
            if ((col + 1) % 3 == 0 && col < 8) {
                result += " | ";
            }
            else {
                result += " ";
            }
        }

        // Add a newline character after each row
        result += "\n";

        // Add a horizontal line for visual separation of Sudoku boxes
        if ((row + 1) % 3 == 0 && row < 8) {
            result += "---------------------\n";
        }
    }

    // Return the formatted result string
    return result;
}
