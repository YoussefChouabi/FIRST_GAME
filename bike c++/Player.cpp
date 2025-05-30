#include "Player.h"
#include <raylib.h>

Player::Player(int windowWidth, int windowHeight) 
    : speed(0.1f), velectiy(0), gravity(800.0f), 
      isJumping(false), JumpForce(-400.0f), isactive(true) {
    playerTexture = LoadTexture("Player/player.png");
    size = {playerTexture.width * 1.0f, playerTexture.height * 1.0f};
    position = {(windowWidth - size.x)/2 - 250, (windowHeight - size.y)/2 + 110};
    groundy = position.y;
}

void Player::Draw() const {
    DrawTextureEx(playerTexture, position, 0.0f, 0.5f, WHITE);
}

void Player::Update() {
    float dt = GetFrameTime();
    int windowWidth = GetScreenWidth();
    int windowHeight = GetScreenHeight();

    // Movement logic (same as original)
    if (IsKeyDown(KEY_RIGHT)) {
        position.x += speed;
        if (position.x > windowWidth - size.x * 0.5f)
            position.x = windowWidth - size.x * 0.5f;
    }
    if (IsKeyDown(KEY_LEFT)) {
        position.x -= speed;
        if (position.x < 0) position.x = 0;
    }

    // Jumping
    if (!isJumping && IsKeyPressed(KEY_UP)) {
        velectiy = JumpForce;
        isJumping = true;
    }

    velectiy += gravity * dt;
    position.y += velectiy * dt;

    // Ground collision
    if (position.y >= groundy) {
        position.y = groundy;
        velectiy = 0;
        isJumping = false;
    }
}

bool Player::IsActive() const { return isactive; }
void Player::SetActive(bool active) { isactive = active; }
Vector2 Player::GetPosition() const { return position; }
Vector2 Player::GetSize() const { return size; }
Texture2D Player::GetPlayerTexture() const { return playerTexture; } 