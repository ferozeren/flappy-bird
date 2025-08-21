// raylib lib
#include "../include/resource_dir.h" // header for SearchAndSetResourceDir
#include "raylib.h"
#include <cstdio>

const unsigned int windowWidth = 1340;
const unsigned int windowHeight = 900;

const int narrowPassage = 300;
constexpr int fps = 60;

Color defaultColor = WHITE;

static unsigned int counter = 0;
const unsigned int counterLimit = 24;
bool counterReset = false;
short int currentFrame = 0;
short int frameSeconds = 0;
unsigned int frameMinutes = 0;

unsigned int scoreCount = 0;
unsigned int hightestScore = 0;

bool spawnRelieve = true;
bool isStartMenu = true;
bool resetValues = false;
bool inMotion = false;
bool isGameOver = false;
bool isPaintObstacle = false;

unsigned short int defaultFontSize = 34;

class MainWindow {

private:
  const char *windowTitle = "Flappy Bird";

public:
  void create() const {
    InitWindow(windowWidth, windowHeight, windowTitle);
    SetTargetFPS(fps);
  }
  void beginDrawing() const { BeginDrawing(); };
  void endDrawing() const { EndDrawing(); };
  void destroy() const { CloseWindow(); };
};

class Renderer {
public:
  Color fontColor = GREEN;
  void clearBackground(Color color) { ClearBackground(color); }
  void drawText(const char *text, int xPos, int yPos, int fontSize,
                Color color) {
    DrawText(text, xPos, yPos, fontSize, color);
  }
};

class BackgroundImage {

public:
  int westVelocity = 4;
  int resetPosition = 1600;

  int xPos;
  int yPos;
  int width;
  int height;

  char backgroundName[20] = "city-1.png";
  Texture backgroundTexture;

  int xPos2;
  int yPos2;
  int width2;
  int height2;
  char background2Name[20] = "city-2.png";
  Texture background2Texture;

  BackgroundImage(int x, int y, int w, int h, int x2, int y2, int w2, int h2)
      : xPos(x), yPos(y), width(w), height(h), xPos2(x2), yPos2(y2), width2(w2),
        height2(h2) {}

  void LoadBackgroundImage() {
    backgroundTexture = LoadTexture(backgroundName);
    background2Texture = LoadTexture(background2Name);
  }

  void DrawBackground() {
    DrawTexture(backgroundTexture, xPos, yPos, defaultColor);

    DrawTexture(background2Texture, xPos2, yPos2, defaultColor);
  }

  void UnLoadBackground() { UnloadTexture(backgroundTexture); }

  void ResetBackground() {

    xPos -= westVelocity;
    xPos2 -= westVelocity;

    if (xPos <= -width) {
      xPos = resetPosition;
    }
    if (xPos2 <= -width) {
      xPos2 = resetPosition;
    }
  }
};

class StartMenu {
private:
public:
  unsigned short fontSize = 60;
  Color fontColor = GREEN;
  Color fontColorTwo = DARKBLUE;

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

  void DrawBird() { DrawTexture(birdTexture, birdX, birdY, defaultColor); }

  void UnLoadBird() { UnloadTexture(birdTexture); }

  void DrawBackground() { ClearBackground(fontColorTwo); }

  void DrawContent() {
    DrawRectangle(recX, recY, recWidth, recHeight, fontColor);
    DrawText(TextFormat("\t\t\tStart\n\n\n\nPress q to exit"), recX, recY,
             fontSize, defaultColor);
  }
};

class FrameTime : public MainWindow {
private:
public:
  void ResetFrameTime() {

    if (isStartMenu || resetValues) {
      currentFrame = 0;
      frameSeconds = 0;
      frameMinutes = 0;
      return;
    }
    if (currentFrame >= fps) {
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

class Obstacle {
private:
public:
  int minimumHeight = 400;
  int maximumHeight = 200;

  char shortBuildingName[20] = "short-building.png";
  int shortBuildingHeight = 0;
  int shortBuildingWidth = 466;
  int shortBuildingXPos = 100;
  int shortBuildingYPos = windowHeight - shortBuildingWidth;
  Texture shortBuildingTexture;

  char longBuildingName[20] = "long-building.png";
  int longBuildingHeight = 643;
  int longBuildingWidth = 300;
  int longBuildingXPos = 0;
  int longBuildingYPos = windowHeight - longBuildingHeight;
  Texture longBuildingTexture;

  char groundTowerName[20] = "ground-tower.png";
  int groundTowerHeight = 600;
  int groundTowerWidth = 190;
  int groundTowerXPos = 500;
  int groundTowerYPos = windowHeight - groundTowerHeight;
  Texture groundTowerTexture;

  char grayPipeSkyName[20] = "gray-pipe-s.png";
  // int grayPipeSkyHeight = 700;
  // int grayPipeSkyWidth = 300;
  int grayPipeSkyWidth = 202;
  int grayPipeSkyHeight = 900;
  int grayPipeSkyXPos = 0;
  int grayPipeSkyYPos = 0;
  Texture grayPipeSkyTexture;

  char grayPipeGroundName[20] = "gray-pipe-g.png";
  int grayPipeGroundWidth = 202;
  int grayPipeGroundHeight = 900;
  int grayPipeGroundXPos = 0;
  int grayPipeGroundYPos = windowHeight - grayPipeGroundHeight;
  Texture grayPipeGroundTexture;

  void LoadObstacle() {
    // shortBuildingTexture = LoadTexture(shortBuildingName);
    // longBuildingTexture = LoadTexture(longBuildingName);
    // groundTowerTexture = LoadTexture(groundTowerName);
    grayPipeSkyTexture = LoadTexture(grayPipeSkyName);
    grayPipeGroundTexture = LoadTexture(grayPipeGroundName);
  }

  void DrawObstacle() {
    // DrawTexture(shortBuildingTexture, shortBuildingXPos, shortBuildingYPos,
    //             defaultColor);
    // DrawTexture(longBuildingTexture, longBuildingXPos, longBuildingYPos,
    //             defaultColor);
    // DrawTexture(groundTowerTexture, groundTowerXPos, groundTowerYPos,
    //             defaultColor);
    // DrawTexture(grayPipeSkyTexture, grayPipeSkyXPos, grayPipeSkyYPos,
    // defaultColor); DrawTexture(positionOneTexture, positionOneXPos,
    // positionOneYPos,
    //             defaultColor);
    // DrawTexture(positionTwoTexture, positionTwoXPos, positionTwoYPos,
    //             defaultColor);

    // if (frameSeconds % 3 == 0) {
    //   ResetObstacle();
    //   DrawTexture(grayPipeSkyTexture, grayPipeSkyXPos, grayPipeSkyYPos,
    //               defaultColor);

    //   DrawTexture(grayPipeGroundTexture, grayPipeGroundXPos,
    //   grayPipeGroundYPos,
    //               defaultColor);
    // }

    DrawTexture(grayPipeSkyTexture, grayPipeSkyXPos, grayPipeSkyYPos,
                defaultColor);

    DrawTexture(grayPipeGroundTexture, grayPipeGroundXPos, grayPipeGroundYPos,
                defaultColor);
  }

  void UnLoadObstacle() {
    UnloadTexture(longBuildingTexture);
    UnloadTexture(shortBuildingTexture);
    UnloadTexture(groundTowerTexture);
    UnloadTexture(grayPipeSkyTexture);
    UnloadTexture(grayPipeGroundTexture);
  }

  void ResetObstacle() {
    // int narrowPassage = 300;
    // int minimumHeight = 400;
    // int maximumHeight = 200;

    // if (frameSeconds % 5 == 0 && isPaintObstacle) {

    //   int rPassageS = GetRandomValue(200, 500);
    //   int rPassageG = rPassageS + narrowPassage;
    //   printf("%d,%d\n", rPassageS, rPassageG);

    //   grayPipeSkyYPos = rPassageS - grayPipeSkyHeight;
    //   grayPipeGroundYPos = rPassageG;

    //   // if (grayPipeGroundXPos + grayPipeGroundWidth >= windowWidth &&
    //   //     grayPipeSkyYPos + grayPipeSkyWidth >= windowWidth) {

    //   //   printf("%d\n", grayPipeSkyXPos);

    //   //   grayPipeGroundXPos -= windowWidth;
    //   //   grayPipeSkyXPos -= windowWidth;
    //   // }
    //   isPaintObstacle = false;
    // }

    if (isStartMenu) {
      return;
    }

    grayPipeSkyXPos -= 4;
    grayPipeGroundXPos -= 4;

    // printf("%d, %d\n", grayPipeGroundXPos, grayPipeGroundYPos);

    if (grayPipeGroundXPos <= -grayPipeGroundWidth &&
        grayPipeSkyYPos <= -grayPipeSkyWidth) {
      // if (grayPipeGroundXPos <= -500 && grayPipeSkyYPos <= -500) {
      printf("%d\n", grayPipeSkyXPos);
      grayPipeSkyXPos += windowWidth + windowWidth / 2;
      grayPipeGroundXPos += windowWidth + windowWidth / 2;
      isPaintObstacle = true;

      int rPassageS = GetRandomValue(0, 700);
      int rPassageG = rPassageS + narrowPassage;
      // printf("%d,%d\n", rPassageS, rPassageG);

      grayPipeSkyYPos = rPassageS - grayPipeSkyHeight;
      grayPipeGroundYPos = rPassageG;

      // if (grayPipeGroundXPos + grayPipeGroundWidth >= windowWidth &&
      //     grayPipeSkyYPos + grayPipeSkyWidth >= windowWidth) {

      //   printf("%d\n", grayPipeSkyXPos);

      //   grayPipeGroundXPos -= windowWidth;
      //   grayPipeSkyXPos -= windowWidth;
      // }
      isPaintObstacle = false;
    }
  }
};

class Bird : public Obstacle {
private:
public:
  const int width = 0;
  const int height = 0;

  int xPos = 0;
  int yPos = 0;
  int velocity = 8;
  int gravity = 12;
  bool wingUp = false;
  bool flapSpan = 60;
  bool wingDown = true;
  char birdName[20] = "bird-g1.png";
  Texture birdTexture;

  char birdName2[20] = "bird-g2.png";
  Texture birdTexture2;

  Bird(int x, int y, int w, int h) : xPos(x), yPos(y), width(w), height(h) {}

  void LoadBird2() { birdTexture2 = LoadTexture(birdName2); }
  void UnLoadBird() { UnloadTexture(birdTexture2); }
  void DrawBird2() { DrawTexture(birdTexture2, xPos, yPos, defaultColor); }

  void LoadBird() { birdTexture = LoadTexture(birdName); }
  void DrawBird() {

    Rectangle source = {0, 0, (float)width, (float)height}; // full texture
    Rectangle dest = {(float)xPos, (float)yPos, (float)width,
                      (float)height};               // destination size
    Vector2 origin = {width / 2.0f, height / 2.0f}; // rotate around center
    float rotation = 90.0f;

    if (wingUp) {
      if (!inMotion && yPos >= GetScreenHeight() - 4 * height) {
        DrawTexturePro(birdTexture, source, dest, origin, 90.0f, defaultColor);
      } else if (!inMotion && yPos >= GetScreenHeight() - 6 * height) {
        DrawTexturePro(birdTexture, source, dest, origin, 0.0f, defaultColor);
      } else {
        DrawTexturePro(birdTexture, source, dest, origin, -30.0f, defaultColor);
      }

    } else if (wingDown) {
      if (inMotion || counter != 0) {
        DrawTexturePro(birdTexture2, source, dest, origin, -30.0f,
                       defaultColor);
      } else {
        DrawTexturePro(birdTexture2, source, dest, origin, 0.0f, defaultColor);
      }
    };
  }

  void ScoreCount() {

    if (isStartMenu) {
      return;
    }

    if (!isGameOver) {
      scoreCount += 1; // WARNING
    }

    if (yPos >= GetScreenHeight() - height / 2) {

      if (scoreCount > hightestScore) {
        hightestScore = scoreCount;
      }

      isGameOver = true;
      resetValues = true;
      spawnRelieve = true;
    }
  };

  void UnLoadBird2() { UnloadTexture(birdTexture); }

  void ResetBird() {
    if (frameSeconds > 0) {
      spawnRelieve = false;
    }
    if (spawnRelieve) {
      return;
    }

    if (isStartMenu) {
      return;
    }

    if (resetValues) {
      // yPos = windowHeight / 2 - height / 2;
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
        yPos -= velocity; // flight distance
      else if (counter >= counterLimit) {
        counterReset = true;
        inMotion = false;
      }

    } else {

      if (IsKeyPressed(KEY_UP) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

        if (!(yPos - (velocity * velocity) <= 0)) {
          // yPos -= velocity;
          inMotion = true;
        }

      } else if (yPos + height / 2 >= GetScreenHeight()) {
        // yPos = GetScreenHeight() - height / 2;
      } else if (yPos - height >= 0) {
        // yPos = -1;
        yPos += gravity;
      } else {
        yPos += gravity;
      }
    }
  }
};

MainWindow mainWindow;
Renderer renderer;
StartMenu startMenu;
Obstacle obstacle[3];
FrameTime frameTime;

void checkCollion(Bird &bird, Obstacle &obstacle) {

  bool isCollidingSky =
      (bird.xPos < obstacle.grayPipeSkyXPos + obstacle.grayPipeSkyWidth &&
       bird.xPos + bird.width > obstacle.grayPipeSkyXPos &&
       bird.yPos < obstacle.grayPipeSkyYPos + obstacle.grayPipeSkyHeight &&
       bird.yPos + bird.height > obstacle.grayPipeSkyYPos);
  bool isCollidingGround =
      (bird.xPos < obstacle.grayPipeGroundXPos + obstacle.grayPipeGroundWidth &&
       bird.xPos + bird.width > obstacle.grayPipeGroundXPos &&
       bird.yPos <
           obstacle.grayPipeGroundYPos + obstacle.grayPipeGroundHeight &&
       bird.yPos + bird.height > obstacle.grayPipeGroundYPos);
  if (isCollidingSky || isCollidingGround) {
    isGameOver = true;

    // printf("obstacleG X: %d, y: %d, Width: %d, height: %d\n",
    //        obstacle.grayPipeGroundXPos, obstacle.grayPipeGroundYPos,
    //        obstacle.grayPipeSkyWidth, obstacle.grayPipeGroundHeight);
  }
}

int main() {

  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
  SearchAndSetResourceDir("resources");

  BackgroundImage backgroundImage(0, 0, 1600, 900, 1600, 0, 1600, 900);
  Bird bird(160, 0, 100, 100);
  bird.yPos = windowHeight / 2 - bird.height / 2;
  mainWindow.create();

  backgroundImage.LoadBackgroundImage();
  bird.LoadBird();
  bird.LoadBird2();

  for (int i = 0; i < 4; i++) {
    obstacle[i].LoadObstacle();
  }

  // obstacle.LoadObstacle();
  startMenu.LoadBird();

  while (!WindowShouldClose()) {
    // float frameTimer = GetFrameTime();
    // update

    backgroundImage.ResetBackground();
    if (!(isGameOver || isStartMenu)) {
      bird.ResetBird();
      bird.ScoreCount();
      frameTime.ResetFrameTime();
      if (!spawnRelieve) {

        for (int i = 0; i < 4; i++) {
          obstacle[i].ResetObstacle();
        }

      } else {
        obstacle[0].grayPipeSkyXPos = 670;
        obstacle[0].grayPipeGroundXPos = 670;
        obstacle[0].grayPipeSkyYPos = -400;
        obstacle[0].grayPipeGroundYPos = 800;

        obstacle[1].grayPipeSkyXPos = 1340;
        obstacle[1].grayPipeGroundXPos = 1340;
        obstacle[1].grayPipeSkyYPos = -600;
        obstacle[1].grayPipeGroundYPos = 600;

        obstacle[2].grayPipeSkyXPos = 2110;
        obstacle[2].grayPipeGroundXPos = 2110;
        obstacle[2].grayPipeSkyYPos = -300;
        obstacle[2].grayPipeGroundYPos = 900;
      }
    }

    // drawing
    mainWindow.beginDrawing();
    backgroundImage.DrawBackground();

    if (isStartMenu) {
      startMenu.DrawBackground();
      startMenu.DrawContent();
      startMenu.DrawBird();

      if (IsKeyPressed(KEY_ENTER) || IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        // bird.yPos = 200;
        isStartMenu = false;
        // resetValues = true;
      } else if (IsKeyPressed(KEY_Q)) {
        mainWindow.endDrawing();
        break;
      }
    } else {

      renderer.drawText(TextFormat("Scores: %i", scoreCount), 20, 20,
                        defaultFontSize, defaultColor);
      renderer.drawText(TextFormat("Record: %i", hightestScore),
                        GetScreenWidth() - 220, 20, defaultFontSize,
                        defaultColor);
      if (!isGameOver) {
        for (int i = 0; i < 4; i++) {
          checkCollion(bird, obstacle[i]);
          obstacle[i].DrawObstacle();
          if (isGameOver) {
            obstacle[0].grayPipeSkyXPos = 670;
            obstacle[0].grayPipeGroundXPos = 670;
            obstacle[0].grayPipeSkyYPos = -400;
            obstacle[0].grayPipeGroundYPos = 800;

            obstacle[1].grayPipeSkyXPos = 1340;
            obstacle[1].grayPipeGroundXPos = 1340;
            obstacle[1].grayPipeSkyYPos = -600;
            obstacle[1].grayPipeGroundYPos = 600;

            obstacle[2].grayPipeSkyXPos = 2110;
            obstacle[2].grayPipeGroundXPos = 2110;
            obstacle[2].grayPipeSkyYPos = -300;
            obstacle[2].grayPipeGroundYPos = 900;
          }
        }
        bird.DrawBird();
        if (IsKeyPressed(KEY_UP) || IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
          spawnRelieve = false;
        }
        renderer.clearBackground(BLACK);

      } else {
        // bird.isGameOver = false; // WARNING
        renderer.drawText("\t\t\t\t\t\tGAME OVER\n\npress Enter to start "
                          "again!\n\n\n\n\n\t\t\t\tPress q To Quit.",
                          GetScreenWidth() / 2 - 250,
                          GetScreenHeight() / 2 - 50, defaultFontSize,
                          renderer.fontColor);

        if (IsKeyPressed(KEY_ENTER) ||
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
          scoreCount = 0;
          isGameOver = false;
          bird.yPos = windowHeight / 2 - bird.height / 2;
          resetValues = false;
          spawnRelieve = true;

        } else if (IsKeyPressed(KEY_Q)) {
          mainWindow.endDrawing();
          break;
        }
      }
    }

    mainWindow.endDrawing();
  }

  // Unload Artificats
  backgroundImage.UnLoadBackground();
  bird.UnLoadBird();
  bird.UnLoadBird2();

  for (int i = 0; i < 4; i++) {
    obstacle[i].UnLoadObstacle();
  }

  startMenu.UnLoadBird();

  mainWindow.destroy();
  return 0;
}
