#include "../include/resource_dir.h" // header for SearchAndSetResourceDir
#include "raylib.h"
#include <cstdio>

enum Scale : int { ONE = 1, TWO = 2 };
Scale scale = ONE;

static int counter = 0;
const int counterLimit = 15;
class MainWindow {

private:
  // const int windowWidth = scale * 680;
  // // const int windowWidth = scale * 600;
  // const int windowHeight = scale * 900;
  const int windowFps = 60;
  const char *windowTitle = "Flappy Bird";

public:
  const int windowWidth = scale * 680;
  // const int windowWidth = scale * 600;
  const int windowHeight = scale * 900;
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
  int xPos = 0;
  int yPos = 0;
  int width = 1200;
  int height = 800;
  char backgroundName[20] = "city.png";
  Texture backgroundTexture;
  BackgroundImage(int x, int y, int w, int h)
      : xPos(x), yPos(y), width(w), height(h) {}

  void LoadBackgroundImage() {
    backgroundTexture = LoadTexture(backgroundName);
  }

  void DrawBackground() { DrawTexture(backgroundTexture, xPos, yPos, WHITE); }
  void UnLoadBackground() { UnloadTexture(backgroundTexture); }
  void ResetBackground() {
    xPos -= 4;
    // if (xPos <= -(width)-760) {
    //   xPos = GetScreenWidth();
    // }
    if (xPos <= -(width)) {
      xPos = 0;
    }
  }
};
class Bird {
private:
  bool inMotion = false;

public:
  bool gameOver = false;
  int scoreCount = 0;
  const int width = 0;
  const int height = 0;
  int xPos = 0;
  int yPos = 0;

  int forwardSpeed = 12;
  int fallSpeed = 8;
  bool counterReset = false;
  bool wingUp = false;
  bool wingDown = true;
  char birdName[20] = "bird-n.png";
  char birdName2[20] = "bird-n2.png";
  Texture birdTexture;
  Texture birdTexture2;
  Bird(int x, int y, int w, int h) : xPos(x), yPos(y), width(w), height(h) {}

  void LoadBird2() { birdTexture2 = LoadTexture(birdName2); }
  void UnLoadBird() { UnloadTexture(birdTexture2); }
  void DrawBird2() { DrawTexture(birdTexture2, xPos, yPos, WHITE); }

  void LoadBird() { birdTexture = LoadTexture(birdName); }
  void DrawBird() {

    Rectangle source = {0, 0, (float)width, (float)height}; // full texture
    Rectangle dest = {(float)xPos, (float)yPos, (float)width,
                      (float)height};               // destination size
    Vector2 origin = {width / 2.0f, height / 2.0f}; // rotate around center
    float rotation = 90.0f;

    if (wingUp) {
      // printf("UP\n");
      if (!inMotion) {
        DrawTexturePro(birdTexture, source, dest, origin, 45.0f, WHITE);
      } else {
        DrawTexturePro(birdTexture, source, dest, origin, -45.0f, WHITE);
      }

    } else if (wingDown) {
      // printf("Down\n");
      if (inMotion || counter != 0) {
        DrawTexturePro(birdTexture2, source, dest, origin, -45.0f, WHITE);
      } else {
        DrawTexturePro(birdTexture2, source, dest, origin, 10.0f, WHITE);
      }
    };
  }

  void ScoreCount() {
    // scoreCount += 1; //WARNING
    if (yPos >= GetScreenHeight() - height / 2) {
      gameOver = true;
    }
  };

  void UnLoadBird2() { UnloadTexture(birdTexture); }

  void ResetBird() {
    // printf("Counter: %d inMotion: %d\n", counter, inMotion);

    if (!wingUp) {
      wingUp = true;
    } else if (wingUp && counter > 0) {
      wingUp = false;
    }

    if (counterReset) {
      counter = 0;
      counterReset = false;
    }
    if (inMotion || counter != 0) {
      counter += 1;
      if (counter < forwardSpeed)
        yPos -= forwardSpeed; // flight distance
      if (counter >= counterLimit) {
        counterReset = true;
        inMotion = false;
      }
    } else {

      if (IsKeyPressed(KEY_UP) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (!(yPos - (forwardSpeed * forwardSpeed) <= 0)) {
          // yPos -= forwardSpeed;
          inMotion = true;
        }
      } else if (yPos + height / 2 >= GetScreenHeight()) {
        yPos = GetScreenHeight() - height / 2;
      } else if (yPos - height >= 0) {
        // yPos = -1;
        yPos += fallSpeed;
      } else {
        yPos += fallSpeed;
      }
    }
  }
};

class GroundObstacle : public MainWindow {
private:
public:
  char shortObstacleName[20] = "short-building.png";
  int shortObstacleHeight = 0;
  int shortObstacleWidth = 466;
  int shortObstaclXPos = 100;
  int shortObstacleYpos = windowHeight - shortObstacleWidth;
  Texture shortObstacleBuildingTexture;

  char longObstacleName[20] = "long-building.png";
  int longObstacleHeight = 643;
  int longObstacleWidth = 300;
  int longObstaclXPos = 0;
  int longObstacleYpos = windowHeight - longObstacleHeight;
  Texture longObstacleBuildingTexture;

  void LoadObstacle() {
    // Load shortObstaclBuilding
    shortObstacleBuildingTexture = LoadTexture(shortObstacleName);

    // Load longObstaclBuilding
    longObstacleBuildingTexture = LoadTexture(longObstacleName);
  }

  void DrawObstacle() {
    // printf("sh: %d\n", shortObstacleYpos);
    // printf("ln: %d\n", longObstacleYpos);
    // Draw shortObstaclBuildingTexture
    DrawTexture(shortObstacleBuildingTexture, shortObstaclXPos,
                shortObstacleYpos, WHITE);
    // Draw longObstaclBuildingTexture
    DrawTexture(longObstacleBuildingTexture, longObstaclXPos, longObstacleYpos,
                WHITE);
  }

  void UnLoadObstacle() {
    UnloadTexture(longObstacleBuildingTexture);
    UnloadTexture(shortObstacleBuildingTexture);
  }
};

int main() {
  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  // InitWindow(1280, 800, "Flapyy Bird");
  MainWindow mainWindow;
  Renderer renderer;
  BackgroundImage backgroundImage(0, 0, 2100, 800);
  Bird bird(160, 300, 100, 100);
  GroundObstacle groundObstacle;

  mainWindow.create();

  // Load a texture from the resources directory
  SearchAndSetResourceDir("resources");
  backgroundImage.LoadBackgroundImage();
  bird.LoadBird();
  bird.LoadBird2();
  groundObstacle.LoadObstacle();

  while (!WindowShouldClose()) {

    // update
    backgroundImage.ResetBackground();
    bird.ResetBird();
    bird.ScoreCount();
    // drawing
    mainWindow.beginDrawing();
    backgroundImage.DrawBackground();

    // renderer.clearBackground(BLACK);
    // renderer.drawText("Hola,Como estas? :D", GetScreenWidth() / 2,
    //                   GetScreenHeight() / 2, renderer.defaultFontSize,
    //                   renderer.defaultColor);

    // draw our texture to the screen

    // bird.gameOver = false; // WARNING
    if (bird.gameOver) {
      renderer.drawText("\t\t\t\t\t\tGAME OVER\n\npress Enter to start again!",
                        GetScreenWidth() / 7, GetScreenHeight() / 3,
                        renderer.defaultFontSize, renderer.defaultColor);

      if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        bird.scoreCount = 0;
        bird.gameOver = false;
        bird.yPos = 0;
        backgroundImage.xPos = 0;
      }

    } else {

      bird.DrawBird();

      renderer.clearBackground(BLACK);
      renderer.drawText(TextFormat("Scores: %i", bird.scoreCount), 20, 20,
                        renderer.defaultFontSize, renderer.defaultColor);
      // groundObstacle.DrawObstacle();
    }
    mainWindow.endDrawing();
  }

  // UnloadTexture(background);
  backgroundImage.UnLoadBackground();
  bird.UnLoadBird();
  bird.UnLoadBird2();
  groundObstacle.UnLoadObstacle();

  // destroy the window and cleanup the OpenGL context
  mainWindow.destroy();

  return 0;
}
