# JWChess
A C++ chess game built using SDL2. This project is still under development, with plans to include features like en passant and castling.

## Features
- Basic chess gameplay with standard moves
- Graphical user interface using SDL2
- Piece movement validation
- Turn-based play

### Prerequisites
- C++17 or higher
- [SDL2](https://www.libsdl.org/download-2.0.php)
- CMake 3.22 or higher

### Unix Users: Installing SDL2
If you're on a Unix-based system, you may need to install SDL2 before building the project. Use the following commands based on your distribution:

- **Ubuntu/Debian**:
  ```bash
  sudo apt-get install libsdl2-dev
  ```

- **Fedora**:
  ```bash
  sudo dnf install SDL2-devel
  ```

- **Arch Linux**:
  ```bash
  sudo pacman -S sdl2
  ```

### Building the Project

1. **Clone the repository**:

   ```bash
   git clone https://github.com/JoWatersASC/JWChess.git
   cd chess-game
   ```

2. **Build the project using CMake**:

   ```bash
   cmake -B ./build
   cmake --build ./build
   ```

3. **Run the game**:
   
   Linux
   ```bash
   ./build/JWChess
   ```l

   Windows
   ```
   cd ./build
   start JWChess.sln
   ```   

### Controls

- Click on a piece to select it.
- Click on a destination square to move the selected piece.
- Turn-based play between two players.

### Upcoming Features

- **Redo**: Add a redo functionality to match undo.
- **Pawn Promotion**.
- **Network Play**

---
