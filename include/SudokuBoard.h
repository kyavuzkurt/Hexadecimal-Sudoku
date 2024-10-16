#ifndef SUDOKUBOARD_H
#define SUDOKUBOARD_H

#include <vector>

class SudokuBoard {
public:
    static constexpr int SIZE = 16; // 16x16 for Hexadecimal Sudoku

    SudokuBoard();
    void display() const;
    bool isValidMove(int row, int col, char value);
    bool setCell(int row, int col, char value);
    char getCell(int row, int col) const;

    // Additional methods as needed

private:
    std::vector<std::vector<char>> board;
    void initializeBoard();
};

#endif // SUDOKUBOARD_H
