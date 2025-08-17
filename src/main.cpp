#include "../include/resource_dir.h" // header for SearchAndSetResourceDir
#include "raylib.h"
#include <cstdio>

const int OBSTACLE_PIPE = 10;

enum Scale : int { ONE = 1, TWO = 2 };
Scale scale = ONE;

int fps = 60;

int positionDefaultOneXPos = 268;
int positionDefaultTwoXPos = 536;
int positionDefaultThreeXPos = 804;
int positionDefaultFourXPos = 1072;

int currentFrame = 0;
int frameSeconds = 0;
int frameMinutes = 0;

static int counter = 0;
const int counterLimit = 24;
int hightestScore = 0;
bool isMainMenu = true;
bool defaultPositions = false;

class MainWindow {

private:
  // const int windowWidth = scale * 680;
  // // const int windowWidth = scale * 600;
  // const int windowHeight = scale * 900;
  const char *windowTitle = "Flappy Bird";

public:
  const int windowFps = fps;
  const int windowWidth = scale * 1340;
  // const int windowWidth = scale * 1700;
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

class BackgroundImage : public MainWindow {
public:
  int xPos = 0;
  int yPos = 0;
  int xPos2 = 0;
  int yPos2 = 0;
  int width = 0;
  int height = 0;
  int width2 = 0;
  int height2 = 0;
  char backgroundName[20] = "city-1.png";
  char background2Name[20] = "city-2.png";
  Texture backgroundTexture;
  Texture background2Texture;
  BackgroundImage(int x, int y, int w, int h, int x2, int y2, int w2, int h2)
      : xPos(x), yPos(y), width(w), height(h), xPos2(x2), yPos2(y2), width2(w2),
        height2(h2) {}

  void LoadBackgroundImage() {
    backgroundTexture = LoadTexture(backgroundName);
    background2Texture = LoadTexture(background2Name);
  }

  void DrawBackground() {
    DrawTexture(backgroundTexture, xPos, yPos, WHITE);
    DrawTexture(background2Texture, xPos2, yPos2, WHITE);
  }

  void UnLoadBackground() { UnloadTexture(backgroundTexture); }
  void ResetBackground() {

    xPos -= 4;
    xPos2 -= 4;

    if (xPos <= -width) {
      xPos = 1600;
    }
    if (xPos2 <= -width) {
      xPos2 = 1600;
    }
  }
};

class StartMenu : public MainWindow {
private:
public:
  int recWidth = 440;
  int recHeight = 60;
  int recX = windowWidth / 2 - recWidth / 2;
  int recY = windowHeight / 2 - recHeight + 100;
  Texture startMenuTexture;

  int birdWidth = 300;
  int birdHeight = 234;
  int birdX = windowHeight / 2 + birdWidth - 240;
  int birdY = windowHeight / 2 - birdHeight;
  char birdName[20] = "bird-big-g1.png";
  Texture birdTexture;

  void LoadBird() { birdTexture = LoadTexture(birdName); }

  void DrawBird() { DrawTexture(birdTexture, birdX, birdY, WHITE); }

  void UnLoadBird() { UnloadTexture(birdTexture); }

  void DrawBackground() { ClearBackground(DARKBLUE); }

  void DrawContent() {
    DrawRectangle(recX, recY, recWidth, recHeight, GREEN);
    DrawText(TextFormat("\t\t\tStart\n\n\n\nPress q to exit"), recX, recY, 60,
             WHITE);
  }
};

class Bird : public MainWindow {
private:
  bool inMotion = false;

public:
  bool gameOver = false;
  int scoreCount = 0;
  const int width = 0;
  const int height = 0;
  int xPos = 0;
  int yPos = 0;

  int forwardSpeed = 8;
  int fallSpeed = 12;
  bool counterReset = false;
  bool wingUp = false;
  bool wingDown = true;
  char birdName[20] = "bird-g1.png";
  char birdName2[20] = "bird-g2.png";
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

      if (!inMotion && yPos >= GetScreenHeight() - 4 * height) {
        DrawTexturePro(birdTexture, source, dest, origin, 90.0f, WHITE);
      } else if (!inMotion && yPos >= GetScreenHeight() - 6 * height) {
        DrawTexturePro(birdTexture, source, dest, origin, 05.0f, WHITE);
      } else {
        DrawTexturePro(birdTexture, source, dest, origin, -30.0f, WHITE);
      }

    } else if (wingDown) {

      if (inMotion || counter != 0) {
        DrawTexturePro(birdTexture2, source, dest, origin, -30.0f, WHITE);
      } else {
        DrawTexturePro(birdTexture2, source, dest, origin, 10.0f, WHITE);
      }
    };
  }

  void ScoreCount() {

    if (isMainMenu) {
      return;
    }

    if (!gameOver) {
      scoreCount += 1; // WARNING
    }

    if (yPos >= GetScreenHeight() - height / 2) {

      if (scoreCount > hightestScore) {
        hightestScore = scoreCount;
      }

      gameOver = true;
      defaultPositions = true;
    }
  };

  void UnLoadBird2() { UnloadTexture(birdTexture); }

  void ResetBird() {

    if (isMainMenu) {
      return;
    }

    if (defaultPositions) {
      yPos = 0;
    }

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

      if (counter < counterLimit)
        yPos -= forwardSpeed; // flight distance
      else if (counter >= counterLimit) {
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

class FrameTime : public MainWindow {
private:
public:
  void ResetFrameTime() {

    if (isMainMenu) {
      return;
    } else if (defaultPositions) {
      currentFrame = 0;
      frameSeconds = 0;
      frameMinutes = 0;
      return;
    } else if (currentFrame >= fps) {
      frameSeconds += 1;
      currentFrame = 0;

      if (frameSeconds >= fps) {
        frameMinutes += 1;
        frameSeconds = 0;
      }

    } else {
      currentFrame += 1;
    }
  }
};

class GroundObstacle : public FrameTime {
private:
public:
  char shortBuildingName[20] = "short-building.png";
  int shortBuildingHeight = 0;
  int shortBuildingWidth = 466;
  int shortBuildingXPos = 100;
  int shortBuildingYpos = windowHeight - shortBuildingWidth;
  Texture shortBuildingTexture;

  char longBuildingName[20] = "long-building.png";
  int longBuildingHeight = 643;
  int longBuildingWidth = 300;
  int longBuildingXPos = 0;
  int longBuildingYpos = windowHeight - longBuildingHeight;
  Texture longBuildingTexture;

  char groundTowerName[20] = "ground-tower.png";
  int groundTowerHeight = 600;
  int groundTowerWidth = 190;
  int groundTowerXPos = 500;
  int groundTowerYpos = windowHeight - groundTowerHeight;
  Texture groundTowerTexture;

  char grayPipeName[20] = "gray-pipe.png";
  int grayPipeHeight = 700;
  int grayPipeWidth = 300;
  int grayPipeXPos = 0;
  int grayPipeYpos = windowHeight - grayPipeHeight;
  Texture grayPipeTexture;

  int positionCount = 4;

  int positionOneXPos = 268;
  int positionOneYPos;
  char *positionOneName;
  int posiitonOneWidth;
  int posiitonOneHeight;

  int positionTwoXPos = 536;
  int positionTwoYPos;
  char *positionTwoName;
  int posiitonTwoWidth;
  int posiitonTwoHeight;

  int positionThreeXPos = 804;
  int positionThreeYPos;
  char *positionThreeName;
  int posiitonThreeWidth;
  int posiitonThreeHeight;

  int positionFourXPos = 1072;
  int positionFourYPos;
  char *positionFourName;
  int posiitonFourWidth;
  int posiitonFourHeight;

  Texture positionOneTexture;
  Texture positionTwoTexture;
  Texture positionThreeTexture;
  Texture positionFourTexture;

  void LoadObstacle() {
    // Load shortObstaclBuilding
    shortBuildingTexture = LoadTexture(shortBuildingName);

    // Load longObstaclBuilding
    longBuildingTexture = LoadTexture(longBuildingName);

    // Load groundTower
    groundTowerTexture = LoadTexture(groundTowerName);

    // Load grayPipe
    grayPipeTexture = LoadTexture(grayPipeName);

    // positionOneTexture = LoadTexture(posiitonOneName);

    // positionTwoTexture = LoadTexture(posiitonTwoName);

    // positionThreeTexture = LoadTexture(posiitonThreeName);

    // positionFourTexture = LoadTexture(posiitonFourName);
  }

  void DrawObstacle() {

    DrawTexture(shortBuildingTexture, shortBuildingXPos, shortBuildingYpos,
                WHITE);
    DrawTexture(longBuildingTexture, longBuildingXPos, longBuildingYpos, WHITE);
    DrawTexture(groundTowerTexture, groundTowerXPos, groundTowerYpos, WHITE);
    DrawTexture(grayPipeTexture, grayPipeXPos, grayPipeYpos, WHITE);
    DrawTexture(positionOneTexture, positionOneXPos, positionOneYPos, WHITE);
    DrawTexture(positionTwoTexture, positionTwoXPos, positionTwoYPos, WHITE);
    DrawTexture(grayPipeTexture, grayPipeXPos, grayPipeYpos, WHITE);

    bool drawRandom = true;
    if (drawRandom) {
      DrawTexture(positionOneTexture, positionOneXPos, positionOneYPos, WHITE);
      DrawTexture(positionTwoTexture, positionTwoXPos, positionTwoYPos, WHITE);
      DrawTexture(positionThreeTexture, positionThreeXPos, positionThreeYPos,
                  WHITE);
      DrawTexture(positionFourTexture, positionFourXPos, positionFourYPos,
                  WHITE);
    }
  }
  // void DrawObstacleOne() {
  //   DrawTexture(positionOneTexture, positionOneXPos, positionOneYPos, WHITE);
  // }

  // void DrawObstacleTwo() {
  //   DrawTexture(positionTwoTexture, positionTwoXPos, positionTwoYPos, WHITE);
  // }

  // void DrawObstacleThree() {
  //   DrawTexture(positionThreeTexture, positionThreeXPos, positionThreeYPos,
  //               WHITE);
  // }

  // void DrawObstacleFour() {
  //   DrawTexture(positionFourTexture, positionFourXPos, positionFourYPos,
  //   WHITE);
  // }

  void setPositionIdValues(int posiitonId, char name[20], Texture texture,
                           int posX, int posY, int width, int height) {
    switch (posiitonId) {
    case 1:
      positionOneTexture = texture;
      positionOneName = name;
      posiitonOneWidth = width;
      posiitonOneHeight = height;
      // positionOneXPos = posX;
      positionOneYPos = posY;

    case 2:
      positionTwoTexture = texture;
      positionTwoName = name;
      posiitonTwoWidth = width;
      posiitonTwoHeight = height;
      // positionTwoXPos = posX;
      positionTwoYPos = posY;
    case 3:
      positionThreeTexture = texture;
      positionThreeName = name;
      posiitonThreeWidth = width;
      posiitonThreeHeight = height;
      // positionThreeXPos = posX;
      positionThreeYPos = posY;
    case 4:
      positionFourTexture = texture;
      positionFourName = name;
      posiitonFourWidth = width;
      posiitonFourHeight = height;
      // positionFourXPos = posX;
      positionFourYPos = posY;
    default:
      return;
    }
  }

  void randomHelper(int positionId) {
    int randomObstacleId = GetRandomValue(1, 4);

    switch (randomObstacleId) {
    case 1:
      setPositionIdValues(positionId, shortBuildingName, shortBuildingTexture,
                          shortBuildingXPos, shortBuildingYpos,
                          shortBuildingWidth, shortBuildingHeight);
      // printf("%s \n ", shortBuildingName);
    case 2:
      setPositionIdValues(positionId, longBuildingName, longBuildingTexture,
                          longBuildingXPos, longBuildingYpos, longBuildingWidth,
                          longBuildingHeight);
      // printf("%s \n ", longBuildingName);
    case 3:
      setPositionIdValues(positionId, groundTowerName, groundTowerTexture,
                          groundTowerXPos, groundTowerYpos, groundTowerWidth,
                          groundTowerHeight);
      // printf("%s \n ", groundTowerName);

    case 4:
      setPositionIdValues(positionId, grayPipeName, grayPipeTexture,
                          grayPipeXPos, grayPipeYpos, grayPipeWidth,
                          grayPipeHeight);
      // printf("%s \n ", grayPipeName);

    default:
      return;
    }
  }

  void UnLoadObstacle() {
    UnloadTexture(longBuildingTexture);
    UnloadTexture(shortBuildingTexture);
    UnloadTexture(groundTowerTexture);
    UnloadTexture(grayPipeTexture);
  }

  void ResetObstacle() {
    if (isMainMenu) {
      return;
    }
    if (defaultPositions) {
      groundTowerXPos = 100;
      positionOneXPos = positionDefaultOneXPos;
      positionTwoXPos = positionDefaultTwoXPos;
      positionThreeXPos = positionDefaultThreeXPos;
      positionFourXPos = positionDefaultFourXPos;
      return;
    }

    // groundTowerXPos -= 4;
    positionOneXPos -= 4;
    positionTwoXPos -= 4;
    positionThreeXPos -= 4;
    positionFourXPos -= 4;

    printf("sec: %d\n", frameSeconds);

    if (frameSeconds == 10) {
      for (int i = 1; i <= positionCount; i++) {
        randomHelper(i);
        // switch (i) {
        // case 1:
        //   printf("Position %i\n", i);
        //   randomHelper(i);
        // case 2:
        //   printf("Position %i\n", i);
        //   randomHelper(i);
        // case 3:
        //   printf("Position %i\n", i);
        //   randomHelper(i);
        // case 4:
        //   printf("Position %i\n", i);
        //   randomHelper(i);
        // default:
        //   return;
        // }
      }
    }
  }
};

int main() {
  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  MainWindow mainWindow;
  Renderer renderer;
  BackgroundImage backgroundImage(0, 0, 1600, 900, 1600, 0, 1600, 900);
  StartMenu startMenu;
  Bird bird(160, 300, 100, 100);
  GroundObstacle groundObstacle;
  FrameTime frameTime;
  mainWindow.create();

  SearchAndSetResourceDir("resources");
  backgroundImage.LoadBackgroundImage();
  bird.LoadBird();
  bird.LoadBird2();
  groundObstacle.LoadObstacle();
  startMenu.LoadBird();

  while (!WindowShouldClose()) {

    // Time
    float frameTimer = GetFrameTime();
    // printf("%f\n", frameTimer);

    // update
    frameTime.ResetFrameTime();
    backgroundImage.ResetBackground();
    bird.ResetBird();
    bird.ScoreCount();
    groundObstacle.ResetObstacle();

    // drawing
    mainWindow.beginDrawing();
    backgroundImage.DrawBackground();

    if (isMainMenu) {
      startMenu.DrawBackground();
      startMenu.DrawContent();
      startMenu.DrawBird();

      if (IsKeyPressed(KEY_ENTER) || IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        bird.yPos = 200;
        isMainMenu = false;
      } else if (IsKeyPressed(KEY_Q)) {
        mainWindow.endDrawing();
        break;
      }
    } else {

      // bird.gameOver = false; // WARNING

      if (bird.gameOver) {
        renderer.drawText(TextFormat("Scores: %i", bird.scoreCount), 20, 20,
                          renderer.defaultFontSize, renderer.defaultColor);

        renderer.drawText(TextFormat("Record: %i", hightestScore),
                          GetScreenWidth() - 220, 20, renderer.defaultFontSize,
                          renderer.defaultColor);
        renderer.drawText("\t\t\t\t\t\tGAME OVER\n\npress Enter to start "
                          "again!\n\n\n\n\n\t\t\t\tPress q To Quit.",
                          GetScreenWidth() / 2 - 250,
                          GetScreenHeight() / 2 - 50, renderer.defaultFontSize,
                          GREEN);

        if (IsKeyPressed(KEY_ENTER) ||
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
          bird.scoreCount = 0;
          bird.gameOver = false;
          bird.yPos = 0;
          defaultPositions = false;
          // backgroundImage.xPos = 0;
        } else if (IsKeyPressed(KEY_Q)) {
          mainWindow.endDrawing();
          break;
        }

      } else {
        // groundObstacle.DrawObstacle();
        bird.DrawBird();
        renderer.clearBackground(BLACK);
        renderer.drawText(TextFormat("Scores: %i", bird.scoreCount), 20, 20,
                          renderer.defaultFontSize, renderer.defaultColor);
        renderer.drawText(TextFormat("Record: %i", hightestScore),
                          GetScreenWidth() - 220, 20, renderer.defaultFontSize,
                          renderer.defaultColor);
      }
    }
    mainWindow.endDrawing();
  }

  // UnloadTexture(background);
  backgroundImage.UnLoadBackground();
  bird.UnLoadBird();
  bird.UnLoadBird2();
  groundObstacle.UnLoadObstacle();
  startMenu.UnLoadBird();

  // destroy the window and cleanup the OpenGL context
  mainWindow.destroy();

  return 0;
}
