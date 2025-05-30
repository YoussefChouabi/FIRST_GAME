#include "Camera.h"
#include "Player.h"

Cameraa::Cameraa(int windowWidth, int windowHeight) {
    camera2D = {0};
    camera2D.target = {0.0f, 0.0f};
    camera2D.offset = {0.0f, 0.0f};
    camera2D.rotation = 0.0f;
    camera2D.zoom = 1.0f;
}

void Cameraa::Reset() {
    camera2D.target = {0.0f, 0.0f};
}

void Cameraa::Update(const Player& player) {
    camera2D.target.x = player.GetPosition().x + player.GetSize().x * 1.5f;
    camera2D.target.y = 0.0f; // Adjust as needed
}

Camera2D Cameraa::GetCamera2D() const {
    return camera2D;
}