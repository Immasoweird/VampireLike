#include "render.h"
#include "globals.h"

void Player::DrawAuraCirlce() {
    DrawCircleV(damageAura.center, damageAura.radius, damageAura.color);
}

void Player::Draw() {
    DrawAuraCirlce();
    DrawRectangleV(position, size, GOLD);
}

void DrawGame() {
    BeginDrawing();
    ClearBackground(DARKGRAY);

    BeginMode2D(gamestate.camera);
    {
        DrawTextureV(background.texture, background.position, WHITE);
        player.Draw();
        for (auto& enemy : enemies) {
            if (enemy.active) DrawRectangleRec(enemy.body, enemy.color);
        }
    }
    EndMode2D();
    EndDrawing();
}