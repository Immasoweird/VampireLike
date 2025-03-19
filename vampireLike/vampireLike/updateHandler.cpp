#include "updateHandler.h"
#include "initialize.h"
#include "weaponHandler.h"
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
	a.position = { a.body.x,a.body.y };
	b.body.x = position_b.x - radius_b;
	b.body.y = position_b.y - radius_b;
	b.position = { b.body.x,b.body.y };
}

void UpdateGame() {
	gamestate.fullscreen();

	if (IsKeyPressed(KEY_P)) {
		printf("SCORES: %d", gamestate.score);
		std::cout << std::endl;
	}

	if (IsKeyReleased(KEY_R)) {
		InitGame();
		gamestate.gameOver = false;
	}
	if (gamestate.gameOver) return;


	player.Update();
	Vector2 mousePosition = GetMousePosition();

	if (weapon.cooldown > 0.0f) {
		weapon.cooldown -= GetFrameTime();
	}

	bool anyAlive = false;
	for (int i = 0; i < enemies.size(); i++) {
		auto& enemy = enemies[i];
		if (enemy.health <= 0) {
			if (enemies[i].active) {
				gamestate.score++;
				enemies[i].active = false;
			}
		}
		if (enemies[i].active) {
			anyAlive = true;
		}
	}
	if (!anyAlive) {
		printf("Wave: %d \n", ++waveCount);
		InitEnemies(waveCount * 2 + 10);
	}

	weaponHandler();


	// ���������� ������ (����� �������� ������)
	Vector2 desiredTarget = Vector2Add(player.position, Vector2Scale(player.size, 0.5f)); // ����� ������
	gamestate.camera.target = Vector2Lerp(gamestate.camera.target, desiredTarget, 0.1f); // ������� �������������

	// ����� Lerp �������� ����������� (������):
	Vector2 minBounds = { -5000, -5000 };            // ����� ������� ���� ������
	Vector2 maxBounds = { 5000, 5000 };      // ������ ������ ���� ������

	gamestate.camera.target.x = Clamp(gamestate.camera.target.x,
		minBounds.x + gamestate.camera.offset.x,
		maxBounds.x - gamestate.camera.offset.x);

	gamestate.camera.target.y = Clamp(gamestate.camera.target.y,
		minBounds.y + gamestate.camera.offset.y,
		maxBounds.y - gamestate.camera.offset.y);


	// �������� �����������
	for (int i = 0; i < enemies.size(); i++)
	{
		auto playerPosition = player.position;
		Vector2 direction = Vector2Normalize(Vector2Subtract(playerPosition, enemies[i].position));
		Vector2 move = { enemies[i].speed.x * direction.x,enemies[i].speed.y * direction.y };
		enemies[i].position = Vector2Add(enemies[i].position, move);
		enemies[i].body.x = enemies[i].position.x;
		enemies[i].body.y = enemies[i].position.y;
		if (enemies[i].active and player.health > 0 and CheckCollisionRecs({ player.position.x, player.position.y }, enemies[i].body)) {
			player.health -= enemies[i].damage;
			std::cout << player.health << std::endl;	
		}
	}

	for (int i = 0; i < enemies.size() - 1; i++)
	{
		if (enemies[i].active) {
			for (int j = i + 1; j < enemies.size(); j++)
			{
				if(enemies[j].active)
					HandleCollision(enemies[i], enemies[j]);
			}
		}
	}

	if (player.health < 1) {
		gamestate.gameOver = true;
	}
}


void Purchase(int index) {
	coins -= upgradeButton.cost;
	gameStats[index].lvl++;

}


void UpdateShop() {
	gamestate.fullscreen();

	if (IsKeyPressed(KEY_P)) {
		printf("SCORES: %d", gamestate.score);
		std::cout << std::endl;
	}

	if (IsKeyReleased(KEY_R)) {
		InitGame();
		gamestate.gameOver = false;
	}
	if (gamestate.gameOver) return;


	player.Update();
	Vector2 mousePosition = GetMousePosition();

}