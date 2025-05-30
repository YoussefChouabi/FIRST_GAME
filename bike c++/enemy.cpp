#include "Enemy.h"
#include <raylib.h>

Enemy::Enemy(int windowWidth, int windowHeight, float speed, const char* texturePath) 
    : speed(speed), active(true) {
    texture = LoadTexture(texturePath);
    float scale = 0.4f;
    size = {128 * scale, 128 * scale};
    position = {(float)windowWidth, (float)windowHeight * 0.57f};
}

void Enemy::Update() {
    float dt = GetFrameTime();
    position.x -= speed * dt;

    if (position.x < -size.x) active = false;

    if (!active) {
        int winW = GetScreenWidth();
        int winH = GetScreenHeight();
        position = {(float)winW, (float)winH * 0.57f};
        active = true;
    }
}

void Enemy::Draw() const {
    if (!active) return;
    Rectangle src = {0, 0, 128, 128};
    Rectangle dst = {position.x, position.y, size.x, size.y};
    DrawTexturePro(texture, src, dst, {0,0}, 0.0f, WHITE);
}

bool Enemy::IsActive() const { return active; }
Vector2 Enemy::GetPosition() const { return position; }
Vector2 Enemy::GetSize() const { return size; }
Texture2D Enemy::GetTexture() const { return texture; }