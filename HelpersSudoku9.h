#pragma once
#ifndef HELPERSSUDOKU_H
#define HELPERSSUDOKU_H
#include"Sudoku9.h"

bool isAbleToPut(Sudoku9* sudoku, int row, int col, int num);
std::vector<int> whatToPut(Sudoku9* sudoku, int row, int col);
bool isUnsolvable(Sudoku9* sudoku);
bool isDone(Sudoku9 sudoku);
bool isFull(Sudoku9* sudoku);
std::vector<int> shuffle(std::vector<int> numbers);
int genRandNum(int maxLimit);
int* returnEmptyFieldWithLeastPossibilities(Sudoku9* sudoku);


#endif
