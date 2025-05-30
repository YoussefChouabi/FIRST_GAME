#include "Map.h"
#include <raylib.h>
#include <cmath>

Map::Map(int windowWidth, int windowHeight) 
    : isCoinActive(true), respawnTimer(0.0f) {
    blockTexture = LoadTexture("Map/grass.png");
    block2Texture = LoadTexture("Map/dirt.png");
    CloudTexture = LoadTexture("Map/cloud.png");
    TreeTexture = LoadTexture("Map/Tree.png");
    WinBlockTexture = LoadTexture("Map/coin.png");
    blockWidth = (float)blockTexture.width;
    blockHight = (float)blockTexture.height;

    for (int i = 0; i < TREE_COUNT; i++)
        treePosition[i] = {i * 300.0f, 280.0f};

    winBlockPosition = {100.0f, 400.0f};
    previousCoinPosition = winBlockPosition;
}

void Map::Update() {
    float treeSpeed = 0.2f;
    for (int i = 0; i < TREE_COUNT; i++) {
        treePosition[i].x -= treeSpeed;
        if (treePosition[i].x < -TreeTexture.width * 0.2f)
            treePosition[i].x = GetScreenWidth();
    }

    // Coin respawn logic
    if (!isCoinActive) {
        respawnTimer -= GetFrameTime();
        if (respawnTimer <= 0.0f) {
            float newX;
            do {
                newX = GetRandomValue(50, GetScreenWidth() - 50);
            } while (abs(newX - previousCoinPosition.x) < 100);
            winBlockPosition = {newX, 400.0f};
            isCoinActive = true;
        }
    }
}

void Map::Draw() const {
    float scale = 0.1f;
    float scaleWidth = blockWidth * scale;
    float y = GetScreenWidth() * 0.6f;

    for (int i = 0; i < TREE_COUNT; i++)
        DrawTextureEx(TreeTexture, treePosition[i], 0.0f, 0.375f, WHITE);

    int blockcountx = GetScreenWidth() / scaleWidth + 1;
    for (int i = 0; i < blockcountx; i++)
        DrawTextureEx(blockTexture, {i * scaleWidth, y}, 0.0f, scale, WHITE);

    for (int j = 1; j < GetScreenHeight() / (blockHight * scale) + 1; j++) {
        float rowy = y + j * blockHight * scale;
        for (int i = 0; i < blockcountx; i++)
            DrawTextureEx(block2Texture, {i * scaleWidth, rowy}, 0.0f, scale, WHITE);
    }

    DrawTexture(CloudTexture, 0, -50, WHITE);
    if (isCoinActive) {
        DrawTextureEx(WinBlockTexture, winBlockPosition, 0.0f, 0.1f, WHITE);
    }
}

void Map::SetWinBlockPosition(Vector2 newPos) {
    winBlockPosition = newPos;
}

Vector2 Map::GetWinBlockPosition() const { return winBlockPosition; }
Texture2D Map::GetBlockTexture() const { return blockTexture; }
Texture2D Map::GetBlock2Texture() const { return block2Texture; }
Texture2D Map::GetCloudTexture() const { return CloudTexture; }
Texture2D Map::GetTreeTexture() const { return TreeTexture; }
Texture2D Map::GetWinBlockTexture() const { return WinBlockTexture; }
bool Map::IsCoinActive() const { return isCoinActive; }
void Map::DeactivateCoin(float respawnTime) {
    isCoinActive = false;
    previousCoinPosition = winBlockPosition;
    respawnTimer = respawnTime;
}