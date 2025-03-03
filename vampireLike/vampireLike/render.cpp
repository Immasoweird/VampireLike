#include "render.h"
#include "globals.h"
#include "raymath.h"

void Player::DrawAuraCirlce() {
	DrawCircleV(damageAura.center, damageAura.radius, damageAura.color);
}

void Player::Draw() {
	DrawAuraCirlce();
	DrawRectangleV(position, size, GOLD);
	DrawTexture(texture, position.x, position.y, RAYWHITE);
}

void Enemy::Draw()
{
	DrawRectangleRec(body, color);
	DrawTexture(texture, position.x, position.y, RAYWHITE);
}

void DrawGame() {
	BeginDrawing();
	ClearBackground(DARKGRAY);

	BeginMode2D(gamestate.camera);
	{
		DrawTextureV(background.texture, background.position, WHITE);
		player.Draw();
		if (attack)
		{
			DrawTriangle(attack_triangle.first, attack_triangle.second, attack_triangle.third, GREEN);
			DrawLineEx({ 0,0 }, attack_triangle.range, 10, RED);
			DrawLineEx(attack_triangle.range, attack_triangle.tangent, 10, GREEN);
			DrawLineEx({ 0,0 }, attack_triangle.tangent, 10, PURPLE);
			DrawLineEx(attack_triangle.range, attack_triangle.NTangent, 10, GREEN);
			DrawLineEx({ 0,0 }, attack_triangle.NTangent, 10, PURPLE);
		}
		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i].active) {
				enemies[i].Draw();

			}
		}
		for (int i = 0; i < MAX_SHOOTS; i++)
		{
			if (shoot[i].active) {
				DrawCircleV(shoot[i].position, shoot[i].radius, shoot[i].color);
				if (weapon.selectWeapon == 3) {
					DrawLineEx(
						shoot[i].position,
						Vector2Add(shoot[i].position, Vector2Scale(shoot[i].speed, 0.05f)),
						3.0f,
						BLACK
					);
				}
			}
			if (shoot[i].explosion.active) {
				DrawCircleV(shoot[i].explosion.body.center, shoot[i].explosion.body.radius, shoot[i].explosion.body.color);
			}
		}
	
	}
	EndMode2D();
	EndDrawing();
}