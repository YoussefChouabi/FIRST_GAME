#pragma once
#include <raylib.h>

class Player {
public:
    Player(int windowWidth, int windowHeight);
    void Draw() const;
    void Update();
    bool IsActive() const;
    void SetActive(bool active);
    Vector2 GetPosition() const;
    Vector2 GetSize() const;
    Texture2D GetPlayerTexture() const;

private:
    Texture2D playerTexture;
    Vector2 position;
    Vector2 size;
    float speed;
    float velectiy;
    float gravity;
    float groundy;
    float JumpForce;
    bool isJumping;
    bool isactive;
}; 