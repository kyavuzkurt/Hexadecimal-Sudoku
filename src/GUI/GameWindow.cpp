#include "GUI/GameWindow.h"
#include <iostream>
#include <algorithm> // For std::min

GameWindow::GameWindow(unsigned int width, unsigned int height, const std::string& title)
    : window(sf::VideoMode(width, height), title), board()
{
    window.setFramerateLimit(60);
    // Load a font for rendering text
    if (!font.loadFromFile("resources/assets/arial.ttf")) {
        std::cerr << "Error loading font\n";
    }
    initializeUndoButton();
    initializeMenuButtons();    
    handleResize(width, height);
}

void GameWindow::initializeMenuButtons() {
    // Define button properties
    float buttonWidth = 200.0f;
    float buttonHeight = 50.0f;
    float buttonSpacing = 20.0f;

    // Easy Button
    easyButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    easyButton.setFillColor(sf::Color(100, 250, 100)); // Light green
    easyButton.setOutlineColor(sf::Color::Black);
    easyButton.setOutlineThickness(2.0f);
    easyButton.setPosition(
        (window.getSize().x - buttonWidth) / 2.0f,
        (window.getSize().y - (3 * buttonHeight + 2 * buttonSpacing)) / 2.0f
    );

    easyButtonText.setFont(font);
    easyButtonText.setString("Easy");
    easyButtonText.setCharacterSize(24);
    easyButtonText.setFillColor(sf::Color::Black);

    // Center text
    sf::FloatRect easyTextRect = easyButtonText.getLocalBounds();
    easyButtonText.setOrigin(easyTextRect.left + easyTextRect.width / 2.0f,
                             easyTextRect.top + easyTextRect.height / 2.0f);
    easyButtonText.setPosition(
        easyButton.getPosition().x + buttonWidth / 2.0f,
        easyButton.getPosition().y + buttonHeight / 2.0f
    );

    // Medium Button
    mediumButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    mediumButton.setFillColor(sf::Color(250, 250, 100)); // Light yellow
    mediumButton.setOutlineColor(sf::Color::Black);
    mediumButton.setOutlineThickness(2.0f);
    mediumButton.setPosition(
        easyButton.getPosition().x,
        easyButton.getPosition().y + buttonHeight + buttonSpacing
    );

    mediumButtonText.setFont(font);
    mediumButtonText.setString("Medium");
    mediumButtonText.setCharacterSize(24);
    mediumButtonText.setFillColor(sf::Color::Black);

    sf::FloatRect mediumTextRect = mediumButtonText.getLocalBounds();
    mediumButtonText.setOrigin(mediumTextRect.left + mediumTextRect.width / 2.0f,
                               mediumTextRect.top + mediumTextRect.height / 2.0f);
    mediumButtonText.setPosition(
        mediumButton.getPosition().x + buttonWidth / 2.0f,
        mediumButton.getPosition().y + buttonHeight / 2.0f
    );

    // Hard Button
    hardButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    hardButton.setFillColor(sf::Color(250, 100, 100)); // Light red
    hardButton.setOutlineColor(sf::Color::Black);
    hardButton.setOutlineThickness(2.0f);
    hardButton.setPosition(
        mediumButton.getPosition().x,
        mediumButton.getPosition().y + buttonHeight + buttonSpacing
    );

    hardButtonText.setFont(font);
    hardButtonText.setString("Hard");
    hardButtonText.setCharacterSize(24);
    hardButtonText.setFillColor(sf::Color::Black);

    sf::FloatRect hardTextRect = hardButtonText.getLocalBounds();
    hardButtonText.setOrigin(hardTextRect.left + hardTextRect.width / 2.0f,
                             hardTextRect.top + hardTextRect.height / 2.0f);
    hardButtonText.setPosition(
        hardButton.getPosition().x + buttonWidth / 2.0f,
        hardButton.getPosition().y + buttonHeight / 2.0f
    );
}
void GameWindow::initializeUndoButton() {
    // Set size and position based on current window size
    float buttonWidth = 100.0f;
    float buttonHeight = 50.0f;
    float buttonPadding = 20.0f;

    undoButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    undoButton.setFillColor(sf::Color(200, 200, 200)); // Light gray
    undoButton.setOutlineColor(sf::Color::Black);
    undoButton.setOutlineThickness(2.0f);
    undoButton.setPosition(padding, padding + gridSize + buttonPadding);

    // Set button text
    undoButtonText.setFont(font);
    undoButtonText.setString("Undo");
    undoButtonText.setCharacterSize(20);
    undoButtonText.setFillColor(sf::Color::Black);

    // Center the text within the button
    sf::FloatRect textRect = undoButtonText.getLocalBounds();
    undoButtonText.setOrigin(textRect.left + textRect.width / 2.0f,
                             textRect.top + textRect.height / 2.0f);
    undoButtonText.setPosition(
        undoButton.getPosition().x + undoButton.getSize().x / 2.0f,
        undoButton.getPosition().y + undoButton.getSize().y / 2.0f
    );
}

void GameWindow::run()
{
    while (window.isOpen())
    {
        processEvents();
        render();
    }
}

void GameWindow::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Check if Undo button was clicked
                    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                    if (undoButton.getGlobalBounds().contains(mousePos)) {
                        if (board.undoMove()) {
                            // Successful undo (optional: provide feedback)
                        } else {
                            // No moves to undo (optional: provide feedback)
                        }
                    } else {
                        handleMouseClick(event.mouseButton.x, event.mouseButton.y);
                    }
                }
                break;
            case sf::Event::KeyPressed:
                handleKeyPress(event.key.code);
                break;

            case sf::Event::Resized:
                handleResize(event.size.width, event.size.height);
                break;

            default:
                break;
        }
    }
}

void GameWindow::handleResize(unsigned int newWidth, unsigned int newHeight)
{

    unsigned int minSize = 600;
    if (newWidth < minSize) newWidth = minSize;
    if (newHeight < minSize) newHeight = minSize;

    window.setSize(sf::Vector2u(newWidth, newHeight));

    // Update the view to the new size of the window
    sf::FloatRect visibleArea(0, 0, static_cast<float>(newWidth), static_cast<float>(newHeight));
    window.setView(sf::View(visibleArea));

    // Recalculate grid size and cell size based on the new window dimensions
    // Maintain aspect ratio for the grid (square)
    float newGridSize = std::min(static_cast<float>(newWidth), static_cast<float>(newHeight)) * 0.6f; // 60% to accommodate buttons
    gridSize = newGridSize;
    cellSize = gridSize / SudokuBoard::SIZE;

    // Recalculate padding to center the grid within the available space
    padding = (std::min(static_cast<float>(newWidth), static_cast<float>(newHeight)) - gridSize) / 2.0f;

    // Reposition Undo button based on new gridSize and padding
    undoButton.setPosition(padding, padding + gridSize + 20.0f);
    undoButtonText.setPosition(
        undoButton.getPosition().x + undoButton.getSize().x / 2.0f,
        undoButton.getPosition().y + undoButton.getSize().y / 2.0f
    );

    // Reposition Menu buttons if in Menu state
    if (currentState == GameState::Menu) {
        float buttonWidth = 200.0f;
        float buttonHeight = 50.0f;
        float buttonSpacing = 20.0f;

        easyButton.setPosition(
            (newWidth - buttonWidth) / 2.0f,
            (newHeight - (3 * buttonHeight + 2 * buttonSpacing)) / 2.0f
        );
        easyButtonText.setPosition(
            easyButton.getPosition().x + buttonWidth / 2.0f,
            easyButton.getPosition().y + buttonHeight / 2.0f
        );

        mediumButton.setPosition(
            easyButton.getPosition().x,
            easyButton.getPosition().y + buttonHeight + buttonSpacing
        );
        mediumButtonText.setPosition(
            mediumButton.getPosition().x + buttonWidth / 2.0f,
            mediumButton.getPosition().y + buttonHeight / 2.0f
        );

        hardButton.setPosition(
            mediumButton.getPosition().x,
            mediumButton.getPosition().y + buttonHeight + buttonSpacing
        );
        hardButtonText.setPosition(
            hardButton.getPosition().x + buttonWidth / 2.0f,
            hardButton.getPosition().y + buttonHeight / 2.0f
        );
    }
}

void GameWindow::handleMouseClick(int x, int y)
{
    float gridAreaHeight = padding + gridSize;
    float buttonAreaY = gridAreaHeight + 20.0f; // Adjust based on button padding

    if (currentState == GameState::Menu) {
        sf::Vector2f mousePos(static_cast<float>(x), static_cast<float>(y));
        if (easyButton.getGlobalBounds().contains(mousePos)) {
            startGame(Difficulty::Easy);
        }
        else if (mediumButton.getGlobalBounds().contains(mousePos)) {
            startGame(Difficulty::Medium);
        }
        else if (hardButton.getGlobalBounds().contains(mousePos)) {
            startGame(Difficulty::Hard);
        }
    }
    else if (currentState == GameState::Playing) {
        if (y < padding + gridSize) {
            float cellX = static_cast<float>(x - padding);
            float cellY = static_cast<float>(y - padding);
            if (cellX < 0 || cellY < 0) {
                selectedRow = -1;
                selectedCol = -1;
                return; // Click outside the grid
            }

            int col = static_cast<int>(cellX / cellSize);
            int row = static_cast<int>(cellY / cellSize);

            if (col >= 0 && col < SudokuBoard::SIZE && row >= 0 && row < SudokuBoard::SIZE) {
                selectedRow = row;
                selectedCol = col;
            }
        }
    }
}

void GameWindow::startGame(Difficulty difficulty) {
    board = SudokuBoard(difficulty); // Initialize board with selected difficulty
    currentState = GameState::Playing;
    // Reset selected cells
    selectedRow = -1;
    selectedCol = -1;
}

void GameWindow::handleKeyPress(sf::Keyboard::Key key)
{
    if (selectedRow == -1 || selectedCol == -1) {
        return; // No cell selected
    }

    char inputChar = '.';
    if (key >= sf::Keyboard::Num0 && key <= sf::Keyboard::Num9) {
        inputChar = '0' + (key - sf::Keyboard::Num0);
    }
    else if (key >= sf::Keyboard::A && key <= sf::Keyboard::F) {
        inputChar = 'A' + (key - sf::Keyboard::A);
    }

    if (inputChar != '.') {
        if (!board.isCellPrefilled(selectedRow, selectedCol)) {
            if (board.setCell(selectedRow, selectedCol, inputChar)) {
                std::cout << "Set cell (" << selectedRow << ", " << selectedCol << ") to " << inputChar << "\n";
            }
            else {
                std::cout << "Invalid move\n";
            }
        }
        else {
            std::cout << "Cannot modify pre-filled cell\n";
        }
    }
}

void GameWindow::render()
{
    window.clear(sf::Color::Black);

    if (currentState == GameState::Menu) {
        drawMenu();
    }
    else if (currentState == GameState::Playing) {
        drawBoard();
        drawCells();
        drawUndoButton();
    }

    window.display();
}

void GameWindow::drawMenu()
{
    // Draw background
    sf::RectangleShape background(sf::Vector2f(static_cast<float>(window.getSize().x),
                                               static_cast<float>(window.getSize().y)));
    background.setFillColor(sf::Color(50, 50, 50)); // Dark gray
    window.draw(background);

    // Draw title
    sf::Text title;
    title.setFont(font);
    title.setString("Hexadecimal Sudoku");
    title.setCharacterSize(40);
    title.setFillColor(sf::Color::White);

    sf::FloatRect titleRect = title.getLocalBounds();
    title.setOrigin(titleRect.left + titleRect.width / 2.0f,
                   titleRect.top + titleRect.height / 2.0f);
    title.setPosition(static_cast<float>(window.getSize().x) / 2.0f,
                     padding);

    window.draw(title);

    // Draw Difficulty Buttons
    window.draw(easyButton);
    window.draw(easyButtonText);

    window.draw(mediumButton);
    window.draw(mediumButtonText);

    window.draw(hardButton);
    window.draw(hardButtonText);
}

void GameWindow::drawUndoButton()
{
    window.draw(undoButton);
    window.draw(undoButtonText);
}

void GameWindow::drawBoard()
{
    sf::RectangleShape line;
    line.setFillColor(sf::Color::White);

    // Draw vertical lines
    for (int i = 0; i <= SudokuBoard::SIZE; ++i) {
        if (i % 4 == 0) {
            line.setSize(sf::Vector2f(4.0f, gridSize)); // Thicker line for subgrids
        }
        else {
            line.setSize(sf::Vector2f(1.0f, gridSize));
        }
        line.setPosition(padding + i * cellSize, padding);
        window.draw(line);
    }

    // Draw horizontal lines
    for (int i = 0; i <= SudokuBoard::SIZE; ++i) {
        if (i % 4 == 0) {
            line.setSize(sf::Vector2f(gridSize, 4.0f)); // Thicker line for subgrids
        }
        else {
            line.setSize(sf::Vector2f(gridSize, 1.0f));
        }
        line.setPosition(padding, padding + i * cellSize);
        window.draw(line);
    }

    // Highlight selected cell
    if (selectedRow != -1 && selectedCol != -1) {
        sf::RectangleShape highlight(sf::Vector2f(cellSize, cellSize));
        highlight.setPosition(padding + selectedCol * cellSize, padding + selectedRow * cellSize);
        highlight.setFillColor(sf::Color(100, 100, 250, 100)); // Semi-transparent blue
        window.draw(highlight);
    }
}

void GameWindow::drawCells()
{
    for (int row = 0; row < SudokuBoard::SIZE; ++row) {
        for (int col = 0; col < SudokuBoard::SIZE; ++col) {
            char cellValue = board.getCell(row, col);
            if (cellValue != '.') {
                sf::Text text;
                text.setFont(font);
                text.setString(std::string(1, cellValue));
                
                // Adjust character size based on cell size (e.g., 50% of cell height)
                text.setCharacterSize(static_cast<unsigned int>(cellSize * 0.5f));

                if (board.isCellPrefilled(row, col)) {
                    text.setFillColor(sf::Color::Red); // Pre-filled cells in red
                }
                else {
                    text.setFillColor(sf::Color::Green); // User-inputted cells in green
                }

                // Center the text within the cell
                sf::FloatRect textRect = text.getLocalBounds();
                text.setOrigin(textRect.left + textRect.width / 2.0f,
                               textRect.top + textRect.height / 2.0f);
                text.setPosition(padding + (col + 0.5f) * cellSize,
                                 padding + (row + 0.5f) * cellSize);

                window.draw(text);
            }
        }
    }
}
