#include "SudokuBoard.h"

int main() {
    SudokuBoard board;
    board.setCell(0, 0, 'A');
    board.setCell(1, 1, 'B');
    board.display();
    return 0;
}