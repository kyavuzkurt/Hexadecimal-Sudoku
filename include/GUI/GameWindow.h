#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SFML/Graphics.hpp>
#include <string>
#include "../SudokuBoard.h"

enum class GameState {
    Menu,
    Playing
};

class GameWindow {
public:
    GameWindow(unsigned int width, unsigned int height, const std::string& title);
    void run();

private:
    sf::RenderWindow window;
    SudokuBoard board;

    // Current state
    GameState currentState = GameState::Menu;

    // Selected cell coordinates (-1 if none)
    int selectedRow = -1;
    int selectedCol = -1;

    sf::Font font;

    // Dynamic sizing factors
    float padding = 50.0f;
    float gridSize = 700.0f;
    float cellSize = gridSize / SudokuBoard::SIZE;

    // Undo Button
    sf::RectangleShape undoButton;
    sf::Text undoButtonText;

    // Difficulty Buttons
    sf::RectangleShape easyButton;
    sf::Text easyButtonText;

    sf::RectangleShape mediumButton;
    sf::Text mediumButtonText;

    sf::RectangleShape hardButton;
    sf::Text hardButtonText;

    void processEvents();
    void render();
    void drawBoard();
    void drawCells();
    void drawUndoButton();
    void drawMenu(); 
    void initializeUndoButton();
    void initializeMenuButtons();
    void handleMouseClick(int x, int y);
    void handleKeyPress(sf::Keyboard::Key key);
    void handleResize(unsigned int newWidth, unsigned int newHeight);
    void startGame(Difficulty difficulty); 
};

#endif // GAMEWINDOW_H
