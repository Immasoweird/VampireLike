#include "weaponHandler.h"
#include "updateHandler.h"
#include "initialize.h"
#include "globals.h"
#include <iostream>
#include <raymath.h>

void weaponHandler() {
	if (IsKeyReleased(KEY_EQUAL)) {
		weapon.selectWeapon++;
		if (weapon.selectWeapon > weapon.allWeapons) {
			weapon.selectWeapon = 1;
		}
		printf("%d", weapon.selectWeapon);
	}

	if (weapon.selectWeapon == 1) { //sword
		for (auto& stat : player.Stats) {
			if (stat.name == StatType::AttackAngle) {
				stat.value
			}
		}
		player.attackAngle = PI / 6;
		weapon.attackRange = 200;
		player.damageAura.radius = 200;
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 player_pos = Vector2Add({ player.position.x, player.position.y }, Vector2Scale(player.size, 0.5f));
			Vector2 center = Vector2Add(player_pos, Vector2Scale(player.size, 0.5f));
			center = { abs(center.x),abs(center.y) };
			Vector2 mouse = GetMousePosition();
			mouse = Vector2Subtract(Vector2Add(mouse, center), gamestate.camera.offset);
			Vector2 dir = Vector2Normalize({ mouse.x - center.x,mouse.y - center.y });
			Vector2 range = { dir.x * weapon.attackRange,dir.y * weapon.attackRange };
			Vector2 tangent = Vector2Scale(Vector2Rotate(dir, PI / 2), tan(player.attackAngle) * weapon.attackRange);
			Vector2 edge = Vector2Add(player_pos, range);
			Vector2 left = Vector2Add(edge, tangent);
			Vector2 NTangent = Vector2Rotate(tangent, PI);
			Vector2 right = Vector2Add(edge, NTangent);
			attack_triangle = { player_pos,left,right,range,tangent,NTangent };

			attack = true;
			for (int i = 0; i < enemies.size(); i++)
			{
				if (enemies[i].active) {
					if (CheckCollisionAttackRange(attack_triangle, enemies[i].body) && CheckCollisionAreaEnemy(enemies[i], player.damageAura)) {
						enemies[i].health -= weapon.attackDamage;
						std::cout << enemies[i].health << "\n";
					}
				}
			}
		}
	}
	else if (weapon.selectWeapon == 2) { //spear
		player.attackAngle = PI / 40;
		weapon.attackRange = 500;
		player.damageAura.radius = 500;

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) and weapon.cooldown <= 0) {
			Vector2 player_pos = Vector2Add({ player.position.x, player.position.y }, Vector2Scale(player.size, 0.5f));
			Vector2 center = Vector2Add(player_pos, Vector2Scale(player.size, 0.5f));
			center = { abs(center.x),abs(center.y) };
			Vector2 mouse = GetMousePosition();
			mouse = Vector2Subtract(Vector2Add(mouse, center), gamestate.camera.offset);
			Vector2 dir = Vector2Normalize({ mouse.x - center.x,mouse.y - center.y });
			Vector2 range = { dir.x * weapon.attackRange,dir.y * weapon.attackRange };
			Vector2 tangent = Vector2Scale(Vector2Rotate(dir, PI / 2), tan(player.attackAngle) * weapon.attackRange);
			Vector2 edge = Vector2Add(player_pos, range);
			Vector2 left = Vector2Add(edge, tangent);
			Vector2 NTangent = Vector2Rotate(tangent, PI);
			Vector2 right = Vector2Add(edge, NTangent);
			attack_triangle = { player_pos,left,right,range,tangent,NTangent };

			attack = true;
			for (int i = 0; i < enemies.size(); i++)
			{
				if (enemies[i].active) {
					if (CheckCollisionAttackRange(attack_triangle, enemies[i].body) && CheckCollisionAreaEnemy(enemies[i], player.damageAura)) {
						enemies[i].health -= weapon.attackDamage;
						std::cout << enemies[i].health << "\n";
					}
				}
			}
			weapon.cooldown = SPEAR_ATTACK_COOLDOWN;
		}
	}
	else if (weapon.selectWeapon == 3) { // Bow
		// Создание стрелы
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 playerCenter = Vector2Add(player.position, Vector2Scale(player.size, 0.5f));
			Vector2 mousePosition = GetMousePosition();
			Vector2 mouseWorldPos = GetScreenToWorld2D(mousePosition, gamestate.camera);

			Vector2 direction = Vector2Normalize(Vector2Subtract(mouseWorldPos, playerCenter));

			for (int i = 0; i < MAX_SHOOTS; i++) {
				if (!shoot[i].active) {
					shoot[i].position = playerCenter;
					shoot[i].speed = Vector2Scale(direction, 1000.0f); // Уменьшенная скорость
					shoot[i].active = true;
					shoot[i].radius = 10.0f; // Увеличенный радиус
					shoot[i].color = YELLOW; // Яркий цвет
					break;
				}
			}
		}
	}
	else if (weapon.selectWeapon == 4) { // fireball
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 playerCenter = Vector2Add(player.position, Vector2Scale(player.size, 0.5f));
			Vector2 mousePosition = GetMousePosition();
			Vector2 mouseWorldPos = GetScreenToWorld2D(mousePosition, gamestate.camera);

			Vector2 direction = Vector2Normalize(Vector2Subtract(mouseWorldPos, playerCenter));

			for (int i = 0; i < MAX_SHOOTS; i++) {
				if (!shoot[i].active) {
					shoot[i].position = playerCenter;
					shoot[i].speed = Vector2Scale(direction, 500.0f); // Уменьшенная скорость
					shoot[i].active = true;
					shoot[i].radius = 20.0f; // Увеличенный радиус
					shoot[i].color = BLACK; // Яркий цвет
					break;
				}
			}
		}
		for (int i = 0; i < MAX_SHOOTS; i++) {
			if (shoot[i].active) {
				shoot[i].position = Vector2Add(
					shoot[i].position,
					Vector2Scale(shoot[i].speed, GetFrameTime())
				);

				// Проверка выхода за пределы экрана
				Vector2 screenPos = GetWorldToScreen2D(shoot[i].position, gamestate.camera);
				if (screenPos.x < 0 || screenPos.x > SCREEN_WIDTH ||
					screenPos.y < 0 || screenPos.y > SCREEN_HEIGHT) {
					shoot[i].active = false;
				}

				// Проверка столкновений
				for (auto& enemy : enemies) {
					if (enemy.active) {
						if (CheckCollisionCircleRec(shoot[i].position, shoot[i].radius, enemy.body)) {
							shoot[i].explosion.active = true;
							shoot[i].explosion.body.center = shoot[i].position;
							enemy.health -= weapon.attackDamage;
							std::cout << enemy.health << "\n";
							for (auto& enemy : enemies) {
								if (enemy.active) {
									if (CheckCollisionCircleRec(shoot[i].explosion.body.center, shoot[i].explosion.body.radius, enemy.body)) {
										enemy.health -= shoot[i].explosion.damage;
										std::cout << enemy.health << "\n";
										enemy.color = BLACK;
									}
								}
							}
							shoot[i].active = false;
							break;
						}
					}
				}


			}
		}
	}

	// Обновление стрел
	for (int i = 0; i < MAX_SHOOTS; i++) {
		if (shoot[i].active) {
			shoot[i].position = Vector2Add(
				shoot[i].position,
				Vector2Scale(shoot[i].speed, GetFrameTime())
			);
			// Проверка выхода за пределы экрана
			Vector2 screenPos = GetWorldToScreen2D(shoot[i].position, gamestate.camera);
			if (screenPos.x < 0 || screenPos.x > SCREEN_WIDTH ||
				screenPos.y < 0 || screenPos.y > SCREEN_HEIGHT) {
				shoot[i].active = false;
			}

			// Проверка столкновений
			for (auto& enemy : enemies) {
				if (enemy.active) {
					if (CheckCollisionCircleRec(shoot[i].position, shoot[i].radius, enemy.body)) {
						enemy.health -= weapon.attackDamage;
						std::cout << enemy.health << "\n";
						shoot[i].active = false;
						enemy.color = ORANGE; // Изменение цвета врага
						break;
					}
				}
			}
		}
	}

	if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
		attack = false;
	}
}