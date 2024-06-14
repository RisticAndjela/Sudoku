/*#include "gtest/gtest.h"
#include "WorkingWithFiles.h"

// Test case for readSudokuFromFile function
TEST(SudokuFileIO, ReadSudokuFromFile) {
    std::string filename = "test_sudoku.txt";

    std::ofstream testFile(filename);
    testFile << "5 3 0 | 0 7 0 | 0 0 0\n";
    // Add more lines as needed
    testFile.close();

    std::vector<Sudoku9*> sudokuVector = readSudokuFromFile(filename);

    ASSERT_EQ(sudokuVector.size(), 1);

    int expectedRow[9] = { 5, 3, 0, 0, 7, 0, 0, 0, 0 };
    int(*table)[9] = sudokuVector[0]->getTable();
    for (int i = 0; i < 9; ++i) {
        ASSERT_EQ(table[0][i], expectedRow[i]);
    }

    for (Sudoku9* sudoku : sudokuVector) {
        delete sudoku;
    }
    remove(filename.c_str());
}*/

