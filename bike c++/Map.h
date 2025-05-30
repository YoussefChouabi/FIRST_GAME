#pragma once
#include <raylib.h>

#define TREE_COUNT 3

class Map {
public:
    Map(int windowWidth, int windowHeight);
    void Update();
    void Draw() const;
    Vector2 GetWinBlockPosition() const;
    void SetWinBlockPosition(Vector2 newPos);
    Texture2D GetBlockTexture() const;
    Texture2D GetBlock2Texture() const;
    Texture2D GetCloudTexture() const;
    Texture2D GetTreeTexture() const;
    Texture2D GetWinBlockTexture() const;
    bool IsCoinActive() const;
    void DeactivateCoin(float respawnTime);

private:
    Vector2 treePosition[TREE_COUNT];
    Vector2 winBlockPosition;
    Vector2 previousCoinPosition;
    Texture2D blockTexture;
    Texture2D block2Texture;
    Texture2D CloudTexture;
    Texture2D TreeTexture;
    Texture2D WinBlockTexture;
    float blockWidth;
    float blockHight;
    bool isCoinActive;
    float respawnTimer;
};