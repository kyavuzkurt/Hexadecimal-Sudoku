#ifndef SUDOKUBOARD_H
#define SUDOKUBOARD_H

#include <vector>
#include <stack>
#include <tuple>
#include <string>

enum class Difficulty {
    Easy,
    Medium,
    Hard
};

class SudokuBoard {
public:
    static constexpr int SIZE = 16; // 16x16 for Hexadecimal Sudoku

    SudokuBoard(Difficulty difficulty = Difficulty::Easy);
    void display() const;
    bool isValidMove(int row, int col, char value);
    bool setCell(int row, int col, char value, bool isPrefilled = false);
    char getCell(int row, int col) const;
    bool isCellPrefilled(int row, int col) const;
    bool undoMove(); // Adds Undo functionality

    void generateBoard(); // Generates the board based on difficulty

private:
    std::vector<std::vector<char>> board;
    std::vector<std::vector<bool>> prefilled; // Tracks pre-filled cells
    std::stack<std::tuple<int, int, char>> moveHistory; // Stores move history
    Difficulty currentDifficulty;

    void initializeBoard();
    // Add more helper methods as needed for board generation
};

#endif // SUDOKUBOARD_H
