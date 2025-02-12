#include "initialize.h"
#include "globals.h"
#include <raymath.h>

void InitGame() {
    gamestate.camera.target = Vector2Add(player.position, Vector2Scale(player.size, 0.5f));
    gamestate.camera.offset = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    gamestate.camera.zoom = 0.5f;

    enemies.clear();
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies.push_back({
            {0,0,150,150},     // body
            {1.0f,1.0f},        // speed
            {(float)GetRandomValue(0,SCREEN_WIDTH), (float)GetRandomValue(0,SCREEN_HEIGHT)}, // position
            BLUE,               // color
            true,               // active
            1000,               // health
            {100,100}           // size
            });
    }
    LoadTextures();
}

void LoadTextures() {
    Image image1 = LoadImage("background.png");
    ImageResize(&image1, 10000, 10000);
    background.texture = LoadTextureFromImage(image1);
    background.position = { -5000, -5000 };
    UnloadImage(image1);
}

void UnloadGame() {
    UnloadTexture(background.texture);
}