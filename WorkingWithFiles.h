#pragma once
#ifndef WORKINGWITHFILES_H
#define WORKINGWITHFILES_H
#include"Sudoku9.h"

std::vector<Sudoku9*> readSudokuFromFile(std::string filename);
void saveSudokuToFile(Sudoku9* sudoku, std::string path);
std::string interpretTable(Sudoku9* sudoku);
#endif