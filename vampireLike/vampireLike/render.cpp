#include "render.h"
#include "globals.h"
#include "raymath.h"

void Player::DrawAuraCirlce() {
	DrawCircleV(damageAura.center, damageAura.radius, damageAura.color);
}

void Player::DrawIdleRight() {
	DrawAuraCirlce();
	DrawRectangleV(position, size, GOLD);
	//DrawTexture(texture, position.x, position.y, RAYWHITE);
	DrawTextureRec(idleTextureRight, { ((float)idleTextureRight.width / 10) * (FrameCounter % 10), 0, (float)idleTextureRight.width / 10, (float)idleTextureRight.height }, { position.x - 115, position.y - 140 }, RAYWHITE);
}

void Player::DrawIdleLeft() {
	DrawAuraCirlce();
	DrawRectangleV(position, size, GOLD);
	//DrawTexture(texture, position.x, position.y, RAYWHITE);
	DrawTextureRec(idleTextureLeft, { ((float)idleTextureLeft.width / 10) * (FrameCounter % 10), 0, (float)idleTextureLeft.width / 10, (float)idleTextureLeft.height }, { position.x - 140, position.y - 140 }, RAYWHITE);
}

void Player::DrawRunRight() {
	DrawAuraCirlce();
	DrawRectangleV(position, size, GOLD);
	//DrawTexture(texture, position.x, position.y, RAYWHITE);
	DrawTextureRec(runTextureRight, { ((float)runTextureRight.width / 10) * (FrameCounter % 10), 0, (float)runTextureRight.width / 10, (float)runTextureRight.height }, { position.x - 115, position.y - 140 }, RAYWHITE);
}

void Player::DrawRunLeft() {
	DrawAuraCirlce();
	DrawRectangleV(position, size, GOLD);
	//DrawTexture(texture, position.x, position.y, RAYWHITE);
	DrawTextureRec(runTextureLeft, { ((float)runTextureLeft.width / 10) * (FrameCounter % 10), 0, (float)runTextureLeft.width / 10, (float)runTextureLeft.height }, { position.x - 140, position.y - 140 }, RAYWHITE);
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
		if (player.direction.x > 0)
		{
			isRunningLeft = false;
			player.DrawRunRight();
		}
		else if (player.direction.x < 0)
		{
			isRunningLeft = true;
			player.DrawRunLeft();
		}
		else if (player.direction.y > 0)
		{
			if (isRunningLeft)
				player.DrawRunLeft();
			else
				player.DrawRunRight();
		}
		else if (player.direction.y < 0)
		{
			if (isRunningLeft)
				player.DrawRunLeft();
			else
				player.DrawRunRight();
		}
		else
		{
			if (isRunningLeft)
				player.DrawIdleLeft();
			else
				player.DrawIdleRight();

		}


		player.direction = { 0,0 };
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



void DrawShop() {
	BeginDrawing();
	ClearBackground(GREEN);
	if (player.direction.x > 0)
	{
		isRunningLeft = false;
		player.DrawRunRight();
	}
	else if (player.direction.x < 0)
	{
		isRunningLeft = true;
		player.DrawRunLeft();
	}
	else if (player.direction.y > 0)
	{
		if (isRunningLeft)
			player.DrawRunLeft();
		else
			player.DrawRunRight();
	}
	else if (player.direction.y < 0)
	{
		if (isRunningLeft)
			player.DrawRunLeft();
		else
			player.DrawRunRight();
	}
	else
		if (isRunningLeft)
			player.DrawIdleLeft();
		else
			player.DrawIdleRight();


	player.direction = { 0,0 };
	EndDrawing();

}