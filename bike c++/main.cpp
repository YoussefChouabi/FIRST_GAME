#include <raylib.h>
#include "Map.h"
#include "Player.h"
#include "Camera.h"
#include "enemy.h"
#include <cstring>

typedef enum {MAIN_MENU, PLAY, ABOUT, GameOver, WIN} GameState;

void DrawTextMultiLine(const char* text, int posX, int posY, int fontSize, int spacing, Color color) {
    const char* next = text;
    int y = posY;
    
    while (*next) {
        const char* nl = strchr(next, '\n');
        int lineLength = nl ? nl - next : strlen(next);
        
        char line[256];
        strncpy(line, next, lineLength);
        line[lineLength] = '\0';
        
        DrawText(line, posX, y, fontSize, color);
        y += fontSize + spacing;
        
        next = nl ? nl + 1 : next + lineLength;
    }
}

int main() {
    int finalscore=0;
    int windowWidth = 750;
    int windowHeight = 700;
    InitWindow(windowWidth,windowHeight, "my game");
    
    Player player(windowWidth, windowHeight);
    Map map(windowWidth, windowHeight);
    Cameraa cameraa(windowWidth, windowHeight);
    
    Enemy enemy1(windowWidth, windowHeight, 150.0f, "Enemy/zombie.png");
    Enemy enemy2(windowWidth, windowHeight, 250.0f, "Enemy/devil.png");
    
    GameState gamestate = MAIN_MENU;
    int score = 0;
    const int WIN_SCORE = 20; // Changed to 20 coins
    float gameTime = 90.0f; // 90-second timer
    
    const char* menuItems[] = {"Jouer", "A propos", "Quitter"};
    const int menuItemsCount = sizeof(menuItems)/sizeof(menuItems[0]);
    int selectedMenuItem = 0;
    Color menuItemColors[menuItemsCount] = {BLACK, BLACK, BLACK};
    
    const char* messageGameOver = "GAME OVER press Enter to play";
    const char* messageWin = "YOU WIN! Press Enter to play again";
    int fontSize = 30;
    int textWidth = MeasureText(menuItems[0], fontSize);
    int textx = (windowWidth - textWidth) /2-150;
    int texty = windowHeight / 2 - 150;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(SKYBLUE);

        switch (gamestate) {
            case MAIN_MENU: {
                if (IsKeyPressed(KEY_DOWN)) {
                    selectedMenuItem = (selectedMenuItem + 1) % menuItemsCount;
                }
                if (IsKeyPressed(KEY_UP)) {
                    selectedMenuItem = (selectedMenuItem - 1 + menuItemsCount) % menuItemsCount;
                }

                for (int i = 0; i < menuItemsCount; i++) {
                    menuItemColors[i] = (i == selectedMenuItem) ? RED : BLACK;
                }

                if (IsKeyPressed(KEY_ENTER)) {
                    switch (selectedMenuItem) {
                        case 0:
                            gamestate = PLAY;
                            score = 0;
                            gameTime = 90.0f; // Reset timer
                            break;
                        case 1:
                            gamestate = ABOUT;
                            break;
                        case 2:
                            CloseWindow();
                            break;
                    }
                }

                int y = texty;
                for (int i = 0; i < menuItemsCount; i++) {
                    int itemWidth = MeasureText(menuItems[i], fontSize);
                    int x = (windowWidth - itemWidth) / 2;
                    DrawText(menuItems[i], x, y, fontSize, menuItemColors[i]);
                    y += 60;
                }
            } break;
            
            case ABOUT: {
                const char* aboutText =
                                      "Controles:\n"
                                      "A/D - Deplacement\n"
                                      "ESPACE - Saut";
                
                if (IsKeyPressed(KEY_ENTER)) {
                    gamestate = MAIN_MENU;
                }
                
                DrawTextMultiLine(aboutText, textx - 100, texty - 50, fontSize, 5, BLACK);
            } break;
            
            case PLAY: {
                static bool canCollectCoin = true;
                
                player.Update();
                map.Update();
                enemy1.Update();
                enemy2.Update();

                // Update timer
                gameTime -= GetFrameTime();
                if (gameTime <= 0) {
                    gameTime = 0.0f;
                    gamestate = GameOver;
                    finalscore = score;
                }

                Rectangle playerRect = { 
                    player.GetPosition().x, 
                    player.GetPosition().y, 
                    player.GetSize().x * 0.3f, 
                    player.GetSize().y * 0.3f 
                };

                Rectangle winBlockRect = {
                    map.GetWinBlockPosition().x,
                    map.GetWinBlockPosition().y,
                    map.GetWinBlockTexture().width * 0.5f,
                    map.GetWinBlockTexture().height * 0.5f
                };

                // Coin collection logic
                if (map.IsCoinActive() && CheckCollisionRecs(playerRect, winBlockRect) && canCollectCoin) {
                    score++;
                    finalscore = score;
                    canCollectCoin = false;
                    map.DeactivateCoin(3.0f); // Deactivate for 3 seconds

                    if (score >= WIN_SCORE) {
                        gamestate = WIN;
                    }
                }
                else if (!CheckCollisionRecs(playerRect, winBlockRect)) {
                    canCollectCoin = true;
                }

                // Enemy collision checks
                auto handleEnemyCollision = [&](Enemy& enemy) {
                    if (enemy.IsActive()) {
                        Rectangle enemyRect = { 
                            enemy.GetPosition().x, 
                            enemy.GetPosition().y, 
                            enemy.GetSize().x, 
                            enemy.GetSize().y 
                        };
                        if (CheckCollisionRecs(playerRect, enemyRect)) {
                            player.SetActive(false);
                            // score = 0;
                            map.SetWinBlockPosition({100.0f, 400.0f});
                        }
                    }
                };

                handleEnemyCollision(enemy1);
                handleEnemyCollision(enemy2);

                map.Draw();
                enemy1.Draw();
                enemy2.Draw();
                player.Draw();
                
                // UI Elements
                DrawText(TextFormat("COINS: %d/%d", score, WIN_SCORE), 10, 10, 20, BLACK);
                int minutes = (int)(gameTime / 60);
                int seconds = (int)gameTime % 60;
                DrawText(TextFormat("TIME: %02d:%02d", minutes, seconds), 10, 40, 20, BLACK);

                if(!player.IsActive()) {
                    gamestate = GameOver;
                    finalscore = score;
                }
            } break;
            
            case WIN: {
                if (IsKeyPressed(KEY_ENTER)) {
                    player = Player(windowWidth, windowHeight);
                    enemy1 = Enemy(windowWidth, windowHeight, 150.0f, "Enemy/zombie.png");
                    enemy2 = Enemy(windowWidth, windowHeight, 250.0f, "Enemy/devil.png");
                    map = Map(windowWidth, windowHeight);
                    cameraa = Cameraa(windowWidth, windowHeight);
                    gamestate = PLAY;
                    score = 0;
                    gameTime = 90.0f;
                }
                map.Draw();
                player.Draw();
                DrawText(messageWin, textx, texty, fontSize, DARKGREEN);
                DrawText(TextFormat("Final Score: %d", score), textx, texty + 40, fontSize, DARKGREEN);
            } break;
            
            case GameOver: {
                if (IsKeyPressed(KEY_ENTER)) {
                    player = Player(windowWidth, windowHeight);
                    enemy1 = Enemy(windowWidth, windowHeight, 150.0f, "Enemy/zombie.png");
                    enemy2 = Enemy(windowWidth, windowHeight, 250.0f, "Enemy/devil.png");
                    cameraa = Cameraa(windowWidth, windowHeight);
                    gamestate = PLAY;
                    score = 0;
                    gameTime = 90.0f;
                }
                map.Draw();
                player.Draw();
                enemy1.Draw();
                enemy2.Draw();
                
                if (gameTime <= 0) {
                    DrawText("TIME'S UP! GAME OVER", textx, texty, fontSize, RED);
                } else {
                    DrawText(messageGameOver, textx, texty, fontSize, RED);
                }
                DrawText(TextFormat("Score: %d", finalscore), textx, texty + 40, fontSize, RED);
            } break;
        }

        EndDrawing();
    }
    
    UnloadTexture(map.GetBlockTexture());
    UnloadTexture(map.GetBlock2Texture());
    UnloadTexture(map.GetCloudTexture());
    UnloadTexture(map.GetTreeTexture());
    UnloadTexture(player.GetPlayerTexture());
    UnloadTexture(enemy1.GetTexture());
    UnloadTexture(enemy2.GetTexture());
    UnloadTexture(map.GetWinBlockTexture());
    
    CloseWindow();
    return 0;
}