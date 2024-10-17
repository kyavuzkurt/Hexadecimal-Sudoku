#include "SudokuBoard.h"
#include <iostream>
#include <cctype>
#include <ctime>

SudokuBoard::SudokuBoard(Difficulty difficulty) {
    initializeBoard();
    generateBoard();
}

void SudokuBoard::initializeBoard() {
    board = std::vector<std::vector<char>>(SIZE, std::vector<char>(SIZE, '.'));
    prefilled = std::vector<std::vector<bool>>(SIZE, std::vector<bool>(SIZE, false));
}
bool solveBoard(int row, int col, SudokuBoard& boardHelper) {
    if (row == SudokuBoard::SIZE - 1 && col == SudokuBoard::SIZE) {
        return true;
    }

    if (col == SudokuBoard::SIZE) {
        row++;
        col = 0;
    }

    if (boardHelper.getCell(row, col) != '.') { // Skip pre-filled cells
        return solveBoard(row, col + 1, boardHelper);
    }

    for (char value = '0'; value <= 'F'; value++) {
        if (value >= '0' && value <= '9') {
            // Valid hexadecimal characters
        }
        else if (value >= 'A' && value <= 'F') {
            // Valid hexadecimal characters
        }
        else {
            continue; // Skip invalid characters
        }

        if (boardHelper.isValidMove(row, col, value)) {
            boardHelper.setCell(row, col, value, false);

            if (solveBoard(row, col + 1, boardHelper)) {
                return true;
            }

            boardHelper.setCell(row, col, '.', false); // Backtrack
        }
    }

    return false; // Trigger backtracking
}

void SudokuBoard::generateBoard() {
    // Step 1: Generate a complete, valid board
    solveBoard(0, 0, *this);

    // Step 2: Remove cells based on difficulty to create the puzzle
    int numToRemove;

    switch (currentDifficulty) {
        case Difficulty::Easy:
            numToRemove =  (SIZE * SIZE) - 100; // Retain 100 cells
            break;
        case Difficulty::Medium:
            numToRemove =  (SIZE * SIZE) - 80; // Retain 80 cells
            break;
        case Difficulty::Hard:
            numToRemove =  (SIZE * SIZE) - 60; // Retain 60 cells
            break;
        default:
            numToRemove =  (SIZE * SIZE) - 80;
    }

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    while (numToRemove > 0) {
        int row = std::rand() % SIZE;
        int col = std::rand() % SIZE;

        if (board[row][col] != '.') {
            char backup = board[row][col];
            board[row][col] = '.';
            prefilled[row][col] = false;

            // TODO: Check if the board still has a unique solution
            
            numToRemove--;
        }
    }
}

void SudokuBoard::display() const {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            std::cout << (cell == '.' ? '.' : static_cast<char>(toupper(cell))) << ' ';
        }
        std::cout << std::endl;
    }
}

bool SudokuBoard::isValidMove(int row, int col, char value) {
    if (!std::isxdigit(static_cast<unsigned char>(value))) {
        return false; // Invalid character
    }

    char upperValue = std::toupper(static_cast<unsigned char>(value));

    // Check Row
    for (int i = 0; i < SIZE; ++i) {
        if (board[row][i] == upperValue) {
            return false;
        }
    }

    // Check Column
    for (int i = 0; i < SIZE; ++i) {
        if (board[i][col] == upperValue) {
            return false;
        }
    }

    // Check 4x4 Subgrid
    int startRow = row - row % 4;
    int startCol = col - col % 4;
    for (int i = startRow; i < startRow + 4; ++i) {
        for (int j = startCol; j < startCol + 4; ++j) {
            if (board[i][j] == upperValue) {
                return false;
            }
        }
    }

    return true;
}

bool SudokuBoard::setCell(int row, int col, char value, bool isPrefilled) {
    if (isPrefilled && prefilled[row][col]) {
        return false; // Cannot overwrite pre-filled cells
    }

    if (isValidMove(row, col, value)) {
        char previousValue = board[row][col];
        board[row][col] = std::toupper(static_cast<unsigned char>(value));
        prefilled[row][col] = isPrefilled;

        if (!isPrefilled) { // Only track user-inputted moves
            moveHistory.push(std::make_tuple(row, col, previousValue));
        }

        return true;
    }
    return false;
}

char SudokuBoard::getCell(int row, int col) const {
    return board[row][col];
}

bool SudokuBoard::isCellPrefilled(int row, int col) const {
    return prefilled[row][col];
}

bool SudokuBoard::undoMove() {
    if (moveHistory.empty()) {
        return false; // No moves to undo
    }

    auto lastMove = moveHistory.top();
    moveHistory.pop();

    int row = std::get<0>(lastMove);
    int col = std::get<1>(lastMove);
    char previousValue = std::get<2>(lastMove);

    board[row][col] = previousValue;
    // If previousValue was a prefilled value, it remains prefilled
    if (previousValue != '.') {
        // Assuming prefilled cells are never changed by user, no need to alter 'prefilled' status
    }

    return true;
}
