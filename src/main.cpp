#include "../include/resource_dir.h" // utility header for SearchAndSetResourceDir
#include "raylib.h"

enum Scale : int { ONE = 1, TWO = 2 };

Scale scale = ONE;

class MainWindow {
private:
  const int windowWidth = scale * 960;
  const int windowHeight = scale * 540;
  const int windowFps = 60;
  const char *windowTitle = "Flappy Bird";

public:
  void create() const {
    InitWindow(windowWidth, windowHeight, windowTitle);
    SetTargetFPS(windowFps);
  }
  void beginDrawing() const { BeginDrawing(); };
  void endDrawing() const { EndDrawing(); };
  void destroy() const { CloseWindow(); };
};

class Renderer {
public:
  int defaultFontSize = 34;
  Color defaultColor = BLACK;
  void clearBackground(Color color) { ClearBackground(color); }
  void drawText(const char *text, int xPos, int yPos, int fontSize,
                Color color) {
    DrawText(text, xPos, yPos, fontSize, color);
  }
};

int main() {
  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  // InitWindow(1280, 800, "Flapyy Bird");
  MainWindow mainWindow;
  Renderer renderer;

  mainWindow.create();

  SearchAndSetResourceDir("resources");
  // Load a texture from the resources directory
  Texture wabbit = LoadTexture("wabbit_alpha.png");

  while (!WindowShouldClose())

  {
    // drawing
    mainWindow.beginDrawing();
    // Setup the back buffer for drawing (clear color and depth buffers)
    renderer.clearBackground(BLUE);

    // draw some text using the default font
    renderer.drawText("Hola,Como estas? :D", GetScreenWidth() / 2,
                      GetScreenHeight() / 2, renderer.defaultFontSize,
                      renderer.defaultColor);
    // draw our texture to the screen
    DrawTexture(wabbit, 400, 200, WHITE);

    mainWindow.endDrawing();
  }

  // cleanup
  // unload our texture so it can be cleaned up
  UnloadTexture(wabbit);

  // destroy the window and cleanup the OpenGL context
  mainWindow.destroy();
  return 0;
}
