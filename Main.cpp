#include <iostream>
#include "Sudoku9.h"
#include "HelpersSudoku9.h"
#include "SudokuGenerator.h"
#include "WorkingWithFiles.h"
#include "SudokuSolver.h"


// Static variables for  tracking used Sudoku instances and generators

static std::vector<Sudoku9*> usedSudokus;
static std::vector<SudokuGenerator*> usedGenerators;
static int numberOfPlays = 1;

// Function to continue with a solvable Sudoku
void continueWithSolvableSudoku(Sudoku9* chosenSudoku, bool madeByGenerator = false) {
    // User options
    std::cout << "Would you like to:\n";
    std::cout << "1. Go through puzzle step by step with us.\n";
    std::cout << "2. Just enter your result, when you're done. We won't let you make mistakes.\n";
    std::cout << "3. Just enter your result, when you're done. We will give you a number of your wrong answers.\n";
    std::cout << "4. See our result.\n";
    std::cout << "Enter your option here: ";

    int option;
    std::cin >> option;

    int table[9][9] = {};
    std::string row;
    int numberOfMistakes = 0;
    int numberOfGoodPuts = 0;
    bool done = true;
    bool again = true;
    Sudoku9* sudokuNew;

    switch (option) {
    case 1:
        // Step-by-step puzzle solving
        chosenSudoku->outputComplicated();
        while (true) {
            // User input for modifying Sudoku
            std::cout << "Enter the field you want to change: e.g. a1\n";
            std::string field;
            std::cin >> field;
            int row = field[1] - '1';
            int col = field[0] - 'a';

            // Validation for user input
            if (!(row >= 0 && row < 9 && col >= 0 && col < 9)) {
                std::cout << "Invalid field format. Try again!";
                continue;
            }

            if (chosenSudoku->table[row][col] != 0) {
                std::cout << "Field already taken. Try again!";
                continue;
            }

            std::cout << "Your number: ";
            int num;
            std::cin >> num;

            if (num > 9 || num < 0) {
                std::cout << "Choose a valid number. Try something else!";
                continue;
            }

            if (!isAbleToPut(chosenSudoku, row, col, num)) {
                std::cout << "You can't put that number here. Try something else!";
                continue;
            }

            chosenSudoku->table[row][col] = num;

            if (isUnsolvable(chosenSudoku)) {
                std::cout << "You made a lot of mistakes, and the puzzle is now unsolvable.";
                break;
            }

            if (isFull(chosenSudoku)) {
                std::cout << "Congrats! You are done!";
                break;
            }

            chosenSudoku->outputComplicated();
        }
        break;
    case 2:
        // User entering results without mistakes check
        while (again) {
            chosenSudoku->outputSimpled();
            std::cout << "When you are ready enter rows one by one. Please make sure that numbers are distanced apart from each other by exactly one space.";

            // User input for each row
            for (int i = 0; i < 9; ++i) {
                std::cout << "\nEnter " << i + 1 << ". row: ";
                std::cin >> row;
                int rowNum[9] = {};
                int counter = 0;
                for (char c : row) {
                    if (c != ' ') {
                        rowNum[counter] = c - '0';
                        ++counter;
                    }
                }

                if (counter != 9) {
                    std::cout << "You need to write all nine numbers.";
                    done = false;
                    break;
                }

                // Filling the table based on user input
                for (int j = 0; j < 9; ++j) {
                    if (rowNum[j] == 0) {
                        table[i][j] = 0;
                    }
                    else if (chosenSudoku->table[i][j] != 0) {
                        if (chosenSudoku->table[i][j] == rowNum[j]) {
                            table[i][j] = rowNum[j];
                        }
                        else {
                            std::cout << "You can't change rows of an already given sudoku puzzle.";
                            done = false;
                            break;
                        }
                    }
                    else if (chosenSudoku->table[i][j] == 0) {
                        if (isAbleToPut(chosenSudoku, i, j, rowNum[j])) {
                            table[i][j] = rowNum[j];
                        }
                        else {
                            std::cout << "You can't put number " << rowNum[j] << " in column number " << j + 1 << std::endl;
                            table[i

                            ][j] = 0;
                        }
                    }
                    else {
                        std::cout << "You can't change rows of an already given sudoku puzzle.";
                        done = false;
                        break;
                    }
                }
            }

            if (done) {
                // Create a new Sudoku instance
                Sudoku9* sudoku = new Sudoku9(table);
                sudoku->outputSimpled();

                if (isDone(sudoku)) {
                    std::cout << "Congrats. You are done.";
                    again = false;
                    break;
                }

                std::cout << "If you want to continue enter 1.\n";
                std::cout << "If you want to see the result and exit, enter any other number.";

                int continue1;
                std::cin >> continue1;

                if (continue1 != 1) {
                    again = false;
                    solver(chosenSudoku);
                    chosenSudoku->outputSimpled();
                }
            }
            else {
                again = false;
            }
        }
        break;
    case 3:
        // User entering results with mistakes check
        chosenSudoku->outputSimpled();
        std::cout << "When you are ready, enter rows one by one. You can separate them by ' ', or don't separate them at all.";

        for (int i = 0; i < 9; ++i) {
            std::cout << "\nEnter " << i + 1 << ". row: ";
            std::cin >> row;
            int rowNum[9] = {};
            int counter = 0;

            for (char c : row) {
                if (c != ' ') {
                    rowNum[counter] = c - '0';
                    ++counter;
                }
            }

            if (counter != 9) {
                std::cout << "You need to write all nine numbers.";
                break;
            }

            for (int j = 0; j < 9; ++j) {
                if (rowNum[j] == 0) {
                    table[i][j] = 0;
                }
                else if (chosenSudoku->table[i][j] != 0) {
                    if (chosenSudoku->table[i][j] == rowNum[j]) {
                        table[i][j] = rowNum[j];
                    }
                }
                else if (chosenSudoku->table[i][j] == 0) {
                    if (isAbleToPut(chosenSudoku, i, j, rowNum[j])) {
                        ++numberOfGoodPuts;
                        table[i][j] = rowNum[j];
                    }
                    else {
                        ++numberOfMistakes;
                        table[i][j] = rowNum[j];
                    }
                }
            }
        }

        sudokuNew = new Sudoku9(table);
        sudokuNew->outputSimpled();
        std::cout << "Number of mistakes you made: " << numberOfMistakes << "\nNumber of correct choices you made: " << numberOfGoodPuts << std::endl;
        break;
    default:
        // Display the result of a Sudoku generated by the computer
        for (SudokuGenerator* generator : usedGenerators) {
            if (generator->getSudokuForPlayer() == chosenSudoku) {
                generator->getSudokuFilled()->outputSimpled();
            }
        }
    };

    ++numberOfPlays;
}

// Function to play a pre-made Sudoku
void playPreMadeSudoku(std::string path) {
    std::cout << "\t\tWelcome to a pre-made sudoku game.\n";
    std::cout << "What difficulty are you ready to try?\n";
    std::cout << "1. easy\n2. medium\n3. hard\n4. really hard\n5. expert\n";

    int difficulty;
    std::cin >> difficulty;

    std::vector<Sudoku9*> sudokuVector = readSudokuFromFile(path);
    std::cout << "We got " << sudokuVector.size() << " options.\n ";
    int counter = 0;
    Sudoku9* chosenSudoku = nullptr;

    // Loop through available Sudoku options
    for (Sudoku9* sudokuPicked : sudokuVector) {
        SudokuGenerator* generator = new SudokuGenerator(difficulty - 1, sudokuPicked);
        usedGenerators.push_back(generator);
        generator->getSudokuForPlayer()->outputSimpled();
        std::cout << "Sudoku number " << ++counter << std::endl;
        std::cout << std::endl;
        std::cout << "If you like this option, enter 1. If you would like something else, enter 2:\n";

        int value;
        std::cin >> value;

        if (value == 1) {
            chosenSudoku = generator->getSudokuForPlayer(); // Store the chosen Sudoku
            break;
        }
    }

    if (chosenSudoku != nullptr) {
        std::cout << "Great choice!";
    }
    else {
        std::cout << "No Sudoku was chosen. We will give you number 1.\n";
        SudokuGenerator* generator = new SudokuGenerator(difficulty - 1, sudokuVector[0]);
        chosenSudoku = generator->getSudokuForPlayer();
    }

    usedSudokus.push_back(chosenSudoku);
    continueWithSolvableSudoku(chosenSudoku);
}

// Function to play a new-generated Sudoku
void playNewGeneratedSudoku() {
    std::cout << "\t\tWelcome to a new-generated sudoku game.\n";
    std::cout << "What difficulty are you ready to try?\n";
    std::cout << "1. easy\n2. medium\n3. hard\n4. really hard\n5. expert\n";

    int difficulty;
    std::cin >> difficulty;

    SudokuGenerator* generator = new SudokuGenerator(difficulty);
    usedGenerators.push_back(generator);
    usedSudokus.push_back(generator->getSudokuFilled());
    std::cout << std::endl;
    generator->getSudokuForPlayer()->outputSimpled();
    continueWithSolvableSudoku(generator->getSudokuForPlayer(), true);
}

// Main function
int main1(int argc, char* argv) {
    std::string path = argv; //using puthere.txt
    std::cout << "\t\tWelcome to a sudoku game.\n";

    while (true) {
        std::cout << "This is round: " << numberOfPlays << "\n";
        std::cout << "If you would like to play a pre-made sudoku enter number 1\n";
        std::cout << "If you would like to play a new-generated sudoku enter number 2\n";
        std::cout << "If you would like to save the previous Sudoku table in a file enter number 3\n";
        std::cout << "If you would like to exit enter number 4\n";

        int choice;
        std::cin >> choice;

        if (choice == 4) {
            std::cout << "Goodbye!";
            return 1;
        }

        switch (choice) {
        case 1:
            std::cout << "You successfully chose pre-made sudoku game.\n";
            playPreMadeSudoku(path);
            break;
        case 2:
            std::cout << "You successfully chose new generated sudoku game.\n";
            playNewGeneratedSudoku();
            break;
        case 3:
            // Save the Sudoku to a file
            if (numberOfPlays > 1) {
                saveSudokuToFile(usedSudokus[usedSudokus.size() - 1], path);
            }
            else if (numberOfPlays == 1) {
                std::cout << "You still haven't played game";
            }
            break;
        case 4:
            return 1;
            break;
        default:
            std::cout << "You didn't choose valid option.Please try again.\n";
            continue;
            return 1;
        }

    }
    return 0;
}
