#pragma once
#include "gameObjects.h"

void UpdateGame();
void UpdateShop();

bool CheckCollisionAttackRange(const Triangle& triangle, const Rectangle& body);
bool CheckCollisionAreaEnemy(Enemy& enemy_p, Circle& dmgArea);
void StaticCollisionResolution(Enemy& a, Enemy& b);
void HandleCollision(Enemy& a, Enemy& b);