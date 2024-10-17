# Hexadecimal Sudoku

 -->

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Building the Project](#building-the-project)
- [Running the Game](#running-the-game)
- [How to Play](#how-to-play)
- [Known Shortcomings](#known-shortcomings)
- [License](#license)

---

## Overview

**Hexadecimal Sudoku** is a graphical user interface (GUI) application for playing Hexadecimal Sudoku, a 16x16 variant of the classic Sudoku puzzle. Developed in C++ with the [SFML](https://www.sfml-dev.org/) (Simple and Fast Multimedia Library), this project offers an interactive and visually appealing platform for Sudoku enthusiasts to challenge themselves with larger grids and hexadecimal digits (`0-9` and `A-F`).

---

## Features

- **Undo Functionality:** Allows players to revert their last move using the Undo button.
- **Difficulty Selection:** An initial menu screen lets players choose their preferred difficulty level (Easy, Medium, Hard).
- **Sudoku Board Generation:** Generates puzzle boards based on selected difficulty levels.

---

## Prerequisites

Before building and running **Hexadecimal Sudoku**, ensure that your system meets the following requirements:

- **Operating System:** Windows, macOS, or Linux
- **C++ Compiler:** C++17 compatible (e.g., GCC, Clang, MSVC)
- **CMake:** Version 3.10 or higher
- **SFML:** Version 2.5 or higher

### Installing SFML

#### On Windows:
Download the SFML SDK from the [official website](https://www.sfml-dev.org/download.php) and follow the [tutorial](https://www.sfml-dev.org/tutorials/2.5/start-vc.php) to set it up with your compiler.

#### On macOS using Homebrew:

```bash

brew install sfml
```


#### On Linux (e.g., Ubuntu):

```bash
sudo apt-get update
sudo apt-get install libsfml-dev
```


---

## Building the Project

Follow these steps to build **Hexadecimal Sudoku**:

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/kyavuzkurt/Hexadecimal-Sudoku
   cd Hexadecimal-Sudoku
   ```

2. **Create a Build Directory:**
   ```bash
   mkdir build
   cd build
   ```

3. **Configure the Project with CMake:**
   ```bash
   cmake ..
   ```
   *Note: If SFML is installed in a non-standard location, you may need to specify the path:
   ```bash
   cmake -DSFML_DIR=/path/to/SFML ..
   ```

4. **Build the Project:**
   ```bash
   make
   ```
   *On Windows using Visual Studio, replace `make` with your IDE's build command.*

5. **Ensure Resources are Copied:**
   The `resources/` directory should be copied to the `build/` directory automatically. If not, ensure that your build configuration handles resource copying.

---

## Running the Game

After successfully building the project, run the executable:

- **On Linux/macOS:**
  ```bash
  ./HexSudoku
  ```
- **On Windows:**
  Double-click `HexSudoku.exe` in the `build/` directory or run it via the Command Prompt:
  ```cmd
  HexSudoku.exe
  ```

---

## How to Play

1. **Launch the Game:**
   Upon running the executable, you'll be presented with an initial menu screen.

2. **Select Difficulty:**
   Choose between **Easy**, **Medium**, or **Hard** difficulty levels. The number of pre-filled cells varies based on your selection.

3. **Gameplay Interface:**
   - **Pre-filled Cells:** Displayed in **red** and cannot be altered.
   - **User-inputted Cells:** Rendered in **green**, indicating your entries.
   - **Grid Highlighting:** Thicker lines distinguish 4x4 subgrids for better visual separation.

4. **Making a Move:**
   - Click on an empty cell to select it.
   - Enter a hexadecimal digit (`0-9` or `A-F`) using your keyboard.
   - To clear a cell, select it and press **Backspace**.

5. **Undoing a Move:**
   - Click the **Undo** button below the grid to revert your last move.

6. **Resizing the Window:**
   - The game interface is responsive. Resize the window, and the grid along with its elements will adjust accordingly.

7. **Winning the Game:**
   - Complete the grid by correctly filling all empty cells without violating Sudoku rules.

---

## Known Shortcomings

While **Hexadecimal Sudoku** offers a robust platform for playing 16x16 Sudoku puzzles, it has certain limitations:

- **Sudoku Board Generation:**
  - The current implementation of the Sudoku board generator uses a simplified method that **does not guarantee a unique solution** for each puzzle.
  - It employs a basic backtracking algorithm to fill the grid and then removes cells based on difficulty. However, without verifying the uniqueness of the solution, some puzzles may have multiple valid completions.

- **User Feedback:**
  - The game provides minimal feedback for invalid moves or conflicts. Enhancements like highlighting conflicting cells or displaying error messages would improve user experience.

- **Advanced Features:**
  - Features such as hints, a timer, solve functionality, or the ability to save and load game states are not yet implemented.

--- 

## License

This project is licensed under the [MIT License](LICENSE).


