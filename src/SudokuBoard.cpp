#include "SudokuBoard.h"
#include <iostream>

SudokuBoard::SudokuBoard() {
    initializeBoard();
}

void SudokuBoard::initializeBoard() {
    // Initialize a 16x16 board with '.' indicating empty cells
    board = std::vector<std::vector<char>>(SIZE, std::vector<char>(SIZE, '.'));
    // Optionally, populate with initial values
}

void SudokuBoard::display() const {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << std::endl;
    }
}

bool SudokuBoard::isValidMove(int row, int col, char value) {
    // Implement validation logic (row, column, and 4x4 grid)
    // Placeholder implementation
    return true;
}

bool SudokuBoard::setCell(int row, int col, char value) {
    if (isValidMove(row, col, value)) {
        board[row][col] = value;
        return true;
    }
    return false;
}

char SudokuBoard::getCell(int row, int col) const {
    return board[row][col];
}