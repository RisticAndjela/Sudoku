#include "Sudoku9.h"
#include "HelpersSudoku9.h"

Sudoku9::Sudoku9() {
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			table[i][j] = 0;
		}
	}
	solvable = true;
};

Sudoku9::Sudoku9(int tableGiven[9][9]) : name("by already made table") {
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			table[i][j] = tableGiven[i][j];
		}
	}
	solvable = isUnsolvable(this);
};

Sudoku9::Sudoku9(Sudoku9* other) : name("by copy") {
	int(*old)[9] = other->getTable();
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			table[i][j] = old[i][j];
		}
	}
	solvable = other->solvable;
}

Sudoku9::~Sudoku9() {}

int(*Sudoku9::getTable())[9] {
	return table;
	};

int* Sudoku9::getCol(int colIndex) {
	int* column = new int[9];
	for (int i = 0; i < 9; ++i) {
		column[i] = getTable()[i][colIndex];
	}

	return column;
}

int* Sudoku9::getRow(int rowIndex) {
	int* row = new int[9];
	for (int i = 0; i < 9; ++i) {
		row[i] = getTable()[rowIndex][i];
	}
	return row;
}

int** Sudoku9::getBox(int colOfNum, int rowOfNum) {
	int** box = new int* [3];
	for (int i = 0; i < 3; ++i) {
		box[i] = new int[3];
	}

	short boxRow = (rowOfNum % 3);
	short boxCol = (colOfNum % 3);

	for (int rows = 0; rows < 3; ++rows) {
		for (int cols = 0; cols < 3; ++cols) {
			box[rows][cols] = getTable()[rows + 3 * boxRow][cols + 3 * boxCol];
		}
	}
	return box;
}




void Sudoku9::outputComplicated() {
	int(*table)[9] = getTable();
	std::cout << "    a b c   d e f   g h i" << std::endl;
	std::cout << "    ---------------------" << std::endl;
	for (int row = 0; row < 9; ++row) {
		std::cout << row + 1 << " | ";
		for (int col = 0; col < 9; ++col) {
			std::cout << table[row][col] << " ";

			if ((col + 1) % 3 == 0 && col < 8) {
				std::cout << "| ";
			}
		}

		std::cout << std::endl;

		if ((row + 1) % 3 == 0 && row < 8) {
			std::cout << "    ---------------------" << std::endl;
		}
	}
}

void Sudoku9::outputSimpled() {
	int(*table)[9] = getTable();
	for (int row = 0; row < 9; ++row) {
		for (int col = 0; col < 9; ++col) {
			std::cout << table[row][col] << " ";

			if ((col + 1) % 3 == 0 && col < 8) {
				std::cout << "| ";
			}
		}

		std::cout << std::endl;

		if ((row + 1) % 3 == 0 && row < 8) {
			std::cout << "---------------------" << std::endl;
		}
	}
}

bool Sudoku9::operator==(const Sudoku9& other) const {
	const int* thisData = &table[0][0];
	const int* otherData = &other.table[0][0];

	return std::equal(thisData, thisData + 9 * 9, otherData);
}
bool Sudoku9::operator!=(const Sudoku9& other) const {
	return !(*this == other);
}
