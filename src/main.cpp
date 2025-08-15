#include "../include/resource_dir.h" // utility header for SearchAndSetResourceDir
#include "raylib.h"

enum Scale : int { ONE = 1, TWO = 2 };

Scale scale = ONE;

class MainWindow {
private:
  const int windowWidth = scale * 600;
  const int windowHeight = scale * 800;
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
  Color defaultColor = WHITE;
  void clearBackground(Color color) { ClearBackground(color); }
  void drawText(const char *text, int xPos, int yPos, int fontSize,
                Color color) {
    DrawText(text, xPos, yPos, fontSize, color);
  }
};

class BackgroundImage {
public:
  int x_pos = 0;
  int y_pos = 0;
  int width = 1200;
  int height = 800;
  char background_name[20] = "city.png";
  Texture backgroundTexture;
  BackgroundImage(int x, int y, int w, int h)
      : x_pos(x), y_pos(y), width(w), height(h) {}

  void LoadBackgroundImage() {
    backgroundTexture = LoadTexture(background_name);
  }

  void DrawBackground() { DrawTexture(backgroundTexture, x_pos, y_pos, WHITE); }
  void UnLoadBackground() { UnloadTexture(backgroundTexture); }
  void ResetBackground() {
    x_pos -= 6;
    if (x_pos <= -(width)) {
      x_pos = 0;
    }
  }
};

int main() {
  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  // InitWindow(1280, 800, "Flapyy Bird");
  MainWindow mainWindow;
  Renderer renderer;
  BackgroundImage backgroundImage(0, 0, 2100, 800);

  mainWindow.create();

  SearchAndSetResourceDir("resources");
  // Load a texture from the resources directory
  Texture wabbit = LoadTexture("wabbit_alpha.png");
  backgroundImage.LoadBackgroundImage();
  // Texture background = LoadTexture("city-800.png");

  while (!WindowShouldClose())

  {

    // update
    backgroundImage.ResetBackground();

    // drawing
    mainWindow.beginDrawing();
    // Setup the back buffer for drawing (clear color and depth buffers)
    // renderer.clearBackground(BLACK);

    // draw some text using the default font
    renderer.drawText("Hola,Como estas? :D", GetScreenWidth() / 2,
                      GetScreenHeight() / 2, renderer.defaultFontSize,
                      renderer.defaultColor);
    // draw our texture to the screen
    DrawTexture(wabbit, 400, 200, WHITE);
    backgroundImage.DrawBackground();

    mainWindow.endDrawing();
  }

  // cleanup
  // unload our texture so it can be cleaned up
  UnloadTexture(wabbit);

  // UnloadTexture(background);
  backgroundImage.UnLoadBackground();

  // destroy the window and cleanup the OpenGL context
  mainWindow.destroy();
  return 0;
}
