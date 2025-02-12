#include "updateHandler.h"
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


void UpdateGame() {
    gamestate.fullscrean();
    player.Update();

	Vector2 mousePosition = GetMousePosition();

	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
		Vector2 player_pos = Vector2Add({ player.position.x, player.position.y }, Vector2Scale(player.size, 0.5f));
		Vector2 center = Vector2Add(player_pos, Vector2Scale(player.size, 0.5f));
		center = { abs(center.x),abs(center.y) };
		Vector2 mouse = GetMousePosition();
		mouse = Vector2Subtract(Vector2Add(mouse, center), gamestate.camera.offset);
		Vector2 dir = Vector2Normalize({ mouse.x - center.x,mouse.y - center.y });
		Vector2 range = { dir.x * player.attackRange,dir.y * player.attackRange };
		Vector2 tangent = Vector2Scale(Vector2Rotate(dir, PI / 2), tan(player.attackAngle) * player.attackRange);
		Vector2 edge = Vector2Add(player_pos, range);
		Vector2 left = Vector2Add(edge, tangent);
		Vector2 NTangent = Vector2Rotate(tangent, PI);
		Vector2 right = Vector2Add(edge, NTangent);
		attack_triangle = { player_pos,left,right,range,tangent,NTangent };

		attack = true;
		for (int i = 0; i < enemies.size(); i++)
		{ 
			if (CheckCollisionAttackRange(attack_triangle, enemies[i].body) && CheckCollisionAreaEnemy(enemies[i], player.damageAura)) {
				enemies[i].health -= player.damage;
				std::cout << enemies[i].health << "\n";
			}
		}
	}
	if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
		attack = false;
	}

	if (gamestate.gameOver) return;

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

    // ���������� ������� ������
    for (auto& enemy : enemies) {
        Vector2 direction = Vector2Normalize(Vector2Subtract(player.position, enemy.position));
        enemy.position = Vector2Add(enemy.position, direction);
        enemy.body.x = enemy.position.x;
        enemy.body.y = enemy.position.y;
    }
}