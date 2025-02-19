#include "render.h"
#include "globals.h"

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
	//DrawRectangleRec(body, color);
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
	
	
	}
	EndMode2D();
	EndDrawing();
}