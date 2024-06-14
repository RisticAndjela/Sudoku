#pragma once
#ifndef SUDOKUGENERATOR_H
#define SUDOKUGENERATOR_H
#include "Sudoku9.h"
#include "HelpersSudoku9.h"

class SudokuGenerator {
    Sudoku9* sudokuFilled;
    Sudoku9* sudokuForPlayer;
    int difficulty;
public:
    Sudoku9* getSudokuFilled();
    Sudoku9* getSudokuForPlayer();
    int getDifficulty();

    void setSudokuForPlayer(Sudoku9* newSudokuForPlayer);
    void setSudokuFilled(Sudoku9* newSudokuFilled);
    void setDifficulty(int newDifficulty);

    SudokuGenerator(int difficultyGiven, Sudoku9* unfinishedSudoku);
    SudokuGenerator(int difficultyGiven);

    void generateDiagonal(Sudoku9* sudoku);
    Sudoku9* fill(Sudoku9* sudoku);
    void deleteBasedOnDifficulty();
    void eraseToBase(Sudoku9* sudoku);
    void eraseOne(Sudoku9* sudoku);
};
int numberOfZeros(Sudoku9* sudoku);
#endif