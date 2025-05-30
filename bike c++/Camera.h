#pragma once
#include <raylib.h>

class Player; // Forward declaration

class Cameraa {  // Removed the misplaced comment
public:
    Cameraa(int windowWidth, int windowHeight);
    void Reset();
    void Update(const Player& player);
    Camera2D GetCamera2D() const;

private:
    Camera2D camera2D;
};