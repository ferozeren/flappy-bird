# Flappy Bird in C++

My first game in raylib here! Lets get flappy! 🐦

|   |   |
| - | - |
|   |   |

NOTE: Download the zip files from release tags, make sure you resources directory placed correctly. Assets are not bundled with the executable!

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
