#pragma once
#include <raylib.h>
#include <string>

class Enemy {
public:
    Enemy(int windowWidth, int windowHeight, float speed, const char* texturePath);
    void Update();
    void Draw() const;
    bool IsActive() const;
    Vector2 GetPosition() const;
    Vector2 GetSize() const;
    Texture2D GetTexture() const;

private:
    Vector2 position;
    Vector2 size;
    Texture2D texture;
    float speed;
    bool active;
};