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

### Dependencies
This project uses SDL2 as a submodule, which means you'll need its development dependencies installed on your system to compile and run the project.
SDL2 on Linux typically requires either X11 or Wayland development libraries

- **Ubuntu/Debian**:
  ```bash
  sudo apt update
  sudo apt install libx11-dev libxext-dev libxrandr-dev libxcursor-dev libxi-dev libudev-dev libgl1-mesa-dev
  ```

- **Fedora/CentOS/RHEL(dnf/yum)**:
  ```bash
  sudo dnf install libX11-devel libXext-devel libXrandr-devel libXcursor-devel libXi-devel libudev-devel mesa-libGL-devel
  ```

- **Arch Linux**:
  ```bash
  sudo pacman -S libx11 libxext libxrandr libxcursor libxi libudev mesa
  ```

### Building the Project

1. **Clone the repository**:

   ```bash
   git clone --recurse-submodules https://github.com/JoWatersASC/JWChess.git <project_dir>
   cd <project_dir>
   ```

2. **Build the project using CMake**:

   ```bash
   cd build
   cmake -S ..
   make
   ```

3. **Run the game**:

   Linux
   ```bash
   cd build/
   ./JWChess
   ```

   Windows
   ```bash
   cd build
   start JWChess.sln
   (And then run from visual studio solution)
   ```

### Controls

- Start the game by pressing the space bar
- Click on a piece to select it.
- Click on a destination square to move the selected piece.
- Turn-based play between two players.
