# Flappy Bird in C++

My first game in raylib here! Lets get flappy! 🐦

|                                                                                                                                           |                                                                                                                                         |
| ----------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------- |
| <img width="1617" height="1080" alt="start=menu" src="https://github.com/user-attachments/assets/a8705492-340d-4479-a053-9d66b1b4b884" /> | <img width="1605" height="1080" alt="gameplay" src="https://github.com/user-attachments/assets/e36e0c21-6916-4a58-83a0-1586122d3506" /> |

## Download  
Get the Game/ Precompiled binaries for Windows Or Linux from [github release](https://github.com/ferozeren/flappy-bird/releases/tag/0.1.0).


NOTE: Download the zip files from release tags, make sure you dynamic libraries present within the executable directory.

## Supported Platforms

The Flappy Bird game can be compiled on:

- Windows
- Linux
- macOS

## Compiling the Game

Ensure you have a compiler toolchain installed (e.g., MinGW-W64 for Windows, GCC for Linux, or Clang for macOS) and raylib set up. The main game code is in `src/main.cpp`.

### VSCode Users (All Platforms)

- Open the project folder in VSCode
- Run the build task (CTRL+SHIFT+B or F5)

### Windows Users

#### Using MinGW-W64

- Open a terminal in the project folder
- Use `W64devkit.exe` terminal if W64devkit isn’t in your PATH, or ensure `gcc`/`MinGW-W64` is in your PATH
- Run `make`

#### Using Microsoft Visual Studio

- Run `build-VisualStudio2022.bat` to generate the `.sln` file
- Open the `.sln` file in Visual Studio
- Build the solution

### Linux Users

- In a terminal, navigate to the `build` folder
- Run `./premake5 gmake`
- Return to the root folder
- Run `make`

### macOS Users

- In a terminal, navigate to the `build` folder
- Run `./premake5.osx gmake`
- Return to the root folder
- Run `make`

## Output Files

The compiled game executable will be in the `bin` directory.

## License

This project is licensed under the [MIT LICENSE](LICENSE).

## Acknowledgment

- [https://github.com/raysan5/raylib](https://github.com/raysan5/raylib)
- [https://github.com/raylib-extras/raylib-quickstart](https://github.com/raylib-extras/raylib-quickstart)
