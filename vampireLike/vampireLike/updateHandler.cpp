#include "updateHandler.h"
#include "initialize.h"
#include "globals.h"
#include <iostream>
#include <raymath.h>
#include <map>

bool CheckCollisionAreaEnemy(Enemy& enemy_p, Circle& dmgArea) {
	return CheckCollisionCircleRec(dmgArea.center, dmgArea.radius, enemy_p.body);
}

bool CheckCollisionAttackRange(const Triangle& triangle, const Rectangle& body) {

	std::vector<std::pair<Vector2, Vector2>> triangle_lines{ {triangle.first,triangle.second}, { triangle.first,triangle.third }, { triangle.second,triangle.third} };

	std::vector<std::pair<Vector2, Vector2>> rectangle{
		{{body.x, body.y}, { body.x + body.width, body.y }},
		{{body.x, body.y}, { body.x, body.y + body.height }},
		{{body.x + body.width, body.y + body.height}, { body.x + body.width, body.y }},
		{{body.x + body.width, body.y + body.height},{ body.x, body.y + body.height }}
	};
	Vector2 collision_point = {};
	for (const auto& triangle_line : triangle_lines) {
		for (const auto& rect_line : rectangle) {
			if (CheckCollisionLines(triangle_line.first, triangle_line.second, rect_line.first, rect_line.second, &collision_point)) {
				return true;
			}
		}
	}
	return false;

}

void StaticCollisionResolution(Vector2& position_b, float radius_b, Vector2& position_a, float radius_a) {
	Vector2 delta = Vector2Subtract(position_b, position_a);
	float distance = Vector2Length(delta);
	float overlap = distance - radius_a - radius_b;
	Vector2 direction = Vector2Scale(Vector2Normalize(delta), (overlap / 2));
	position_a = Vector2Add(position_a, direction);
	position_b = Vector2Add(position_b, Vector2Negate(direction));
}

void HandleCollision(Enemy& a, Enemy& b) {
	float radius_b = b.body.width / 2;
	Vector2 position_b = { b.body.x + radius_b,b.body.y + radius_b };
	float radius_a = a.body.width / 2;
	Vector2 position_a = { a.body.x + radius_a,a.body.y + radius_a };
	Vector2 delta = Vector2Subtract(position_b, position_a);
	float length = Vector2Length(delta);
	float minDistance = radius_a + radius_b;

	if (length < minDistance) {
		StaticCollisionResolution(position_b, radius_b, position_a, radius_a);
	}
	a.body.x = position_a.x - radius_a;
	a.body.y = position_a.y - radius_a;
	b.body.x = position_b.x - radius_b;
	b.body.y = position_b.y - radius_b;
}

void UpdateGame() {
	gamestate.fullscreen();
	player.Update();
	Vector2 mousePosition = GetMousePosition();

	if (weapon.cooldown > 0.0f) {
		weapon.cooldown -= GetFrameTime();
	}

	bool anyAlive = false;
	for (int i = 0; i < enemies.size(); i++) {
		auto& enemy = enemies[i];
		if (enemy.health <= 0) {
			enemies[i].active = false;
		}
		if (enemies[i].active) {
			anyAlive = true;
		}
	}
	if (!anyAlive) {
		printf("Wave: %d \n", ++waveCount);
		InitEnemies(waveCount * 2 + 10);
	}

	if (IsKeyReleased(KEY_EQUAL)) {
		weapon.selectWeapon++;
		if (weapon.selectWeapon > 3) {
			weapon.selectWeapon = 1;
		}
		printf("%d", weapon.selectWeapon);
	}

	if (weapon.selectWeapon == 1) { //sword
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
					shoot[i].speed = Vector2Scale(direction, 300.0f); // Уменьшенная скорость
					shoot[i].active = true;
					shoot[i].radius = 10.0f; // Увеличенный радиус
					shoot[i].color = YELLOW; // Яркий цвет
					break;
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
	}

	if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
		attack = false;
	}

	if (gamestate.gameOver) return;

	// Обновление камеры (после движения игрока)
	Vector2 desiredTarget = Vector2Add(player.position, Vector2Scale(player.size, 0.5f)); // Центр игрока
	gamestate.camera.target = Vector2Lerp(gamestate.camera.target, desiredTarget, 0.1f); // Плавное преследование

	// После Lerp добавьте ограничения (пример):
	Vector2 minBounds = { -5000, -5000 };            // Левый верхний угол уровня
	Vector2 maxBounds = { 5000, 5000 };      // Правый нижний угол уровня

	gamestate.camera.target.x = Clamp(gamestate.camera.target.x,
		minBounds.x + gamestate.camera.offset.x,
		maxBounds.x - gamestate.camera.offset.x);

	gamestate.camera.target.y = Clamp(gamestate.camera.target.y,
		minBounds.y + gamestate.camera.offset.y,
		maxBounds.y - gamestate.camera.offset.y);


	// Движение противников
	for (int i = 0; i < enemies.size(); i++)
	{
		auto playerPosition = player.position;
		Vector2 direction = Vector2Normalize(Vector2Subtract(playerPosition, enemies[i].position));
		Vector2 move = { enemies[i].speed.x * direction.x,enemies[i].speed.y * direction.y };
		enemies[i].position = Vector2Add(enemies[i].position, move);
		enemies[i].body.x = enemies[i].position.x;
		enemies[i].body.y = enemies[i].position.y;
	}
}