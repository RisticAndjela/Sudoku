#pragma once

#ifndef SUDOKU9_H
#define SUDOKU9_H

#include<iostream>
#include<ostream>
#include<string>
#include<vector>

class Sudoku9
{

public:
	int table[9][9];
	std::string name = "regular";
	bool solvable;

	Sudoku9();
	Sudoku9(int tableGiven[9][9]);
	~Sudoku9();
	Sudoku9(Sudoku9* other);

	int(*getTable())[9];


	void outputComplicated();
	void outputSimpled();

	int* getCol(int colIndex);
	int* getRow(int rowIndex);
	int** getBox(int colOfNum, int rowOfNum);

	bool operator==(const Sudoku9& other) const;
	bool operator!=(const Sudoku9& other) const;


};


#endif // SUDOKU9_H

