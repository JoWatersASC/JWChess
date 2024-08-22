
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

### Building the Project

1. **Clone the repository**:

   ```bash
   git clone https://github.com/yourusername/chess-game.git
   cd chess-game
   ```

2. **Build the project using CMake**:

   ```bash
   cmake -B ./build
   cmake --build ./build
   ```

3. **Run the game**:

   ```bash
   ./build/ChessGame
   ```

### Controls

- Click on a piece to select it.
- Click on a destination square to move the selected piece.
- Turn-based play between two players.

### Upcoming Features

- **En Passant**: Implement the en passant capture move.
- **Castling**: Implement castling on both sides (king-side and queen-side).
- **AI Opponent**: Add a basic AI for single-player mode.