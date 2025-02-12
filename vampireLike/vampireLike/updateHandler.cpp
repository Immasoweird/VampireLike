#include "updateHandler.h"
#include "globals.h"
#include <iostream>
#include <raymath.h>

void CheckCollisionAreaEnemy(Enemy& enemy_p, Circle& dmgArea,float damage) {
    if (CheckCollisionCircleRec(dmgArea.center, dmgArea.radius, enemy_p.body)) {
        enemy_p.health -= damage;
        std::cout << enemy_p.health << "\n";
    }
}

void UpdateGame() {
    gamestate.fullscrean();
    player.Update();

    // Обновление позиций врагов
    for (auto& enemy : enemies) {
        Vector2 direction = Vector2Normalize(Vector2Subtract(player.position, enemy.position));
        enemy.position = Vector2Add(enemy.position, direction);
        enemy.body.x = enemy.position.x;
        enemy.body.y = enemy.position.y;
    }
}