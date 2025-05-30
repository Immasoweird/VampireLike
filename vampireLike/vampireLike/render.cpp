#include "render.h"
#include "globals.h"
#include "raymath.h"

void Player::DrawAuraCirlce() {
	//DrawCircleV(damageAura.center, damageAura.radius, damageAura.color);
}

void Player::DrawIdleRight() {
	//DrawAuraCirlce();
	//DrawRectangleV(position, size, GOLD);
	//DrawTexture(texture, position.x, position.y, RAYWHITE);
	DrawTextureRec(idleTextureRight, { ((float)idleTextureRight.width / 10) * (FrameCounter % 10), 0, (float)idleTextureRight.width / 10, (float)idleTextureRight.height }, { position.x - 115, position.y - 140 }, RAYWHITE);
}

void Player::DrawIdleLeft() {
	//DrawAuraCirlce();
	//DrawRectangleV(position, size, GOLD);
	//DrawTexture(texture, position.x, position.y, RAYWHITE);
	DrawTextureRec(idleTextureLeft, { ((float)idleTextureLeft.width / 10) * (FrameCounter % 10), 0, (float)idleTextureLeft.width / 10, (float)idleTextureLeft.height }, { position.x - 140, position.y - 140 }, RAYWHITE);
}

void Player::DrawRunRight() {
	//DrawAuraCirlce();
	//DrawRectangleV(position, size, GOLD);
	//DrawTexture(texture, position.x, position.y, RAYWHITE);
	DrawTextureRec(runTextureRight, { ((float)runTextureRight.width / 10) * (FrameCounter % 10), 0, (float)runTextureRight.width / 10, (float)runTextureRight.height }, { position.x - 115, position.y - 140 }, RAYWHITE);
}

void Player::DrawRunLeft() {
	//DrawAuraCirlce();
	//DrawRectangleV(position, size, GOLD);
	//DrawTexture(texture, position.x, position.y, RAYWHITE);
	DrawTextureRec(runTextureLeft, { ((float)runTextureLeft.width / 10) * (FrameCounter % 10), 0, (float)runTextureLeft.width / 10, (float)runTextureLeft.height }, { position.x - 140, position.y - 140 }, RAYWHITE);
}

void Enemy::DrawWalkRight()
{
	//DrawRectangleRec(body, color);
	DrawTextureRec(enemyWalkTextureRight, { ((float)enemyWalkTextureRight.width / 6) * (FrameCounter % 6), 0, (float)enemyWalkTextureRight.width / 6, (float)enemyWalkTextureRight.height }, { position.x-50, position.y-60 }, RAYWHITE);
}

void Enemy::DrawWalkLeft()
{
	//DrawRectangleRec(body, color);
	DrawTextureRec(enemyWalkTextureLeft, { ((float)enemyWalkTextureLeft.width / 6) * (FrameCounter % 6), 0, (float)enemyWalkTextureLeft.width / 6, (float)enemyWalkTextureLeft.height }, { position.x-50, position.y-60}, RAYWHITE);
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
		/*if (attack)
		{
			DrawTriangle(attack_triangle.first, attack_triangle.second, attack_triangle.third, GREEN);
			DrawLineEx({ 0,0 }, attack_triangle.range, 10, RED);
			DrawLineEx(attack_triangle.range, attack_triangle.tangent, 10, GREEN);
			DrawLineEx({ 0,0 }, attack_triangle.tangent, 10, PURPLE);
			DrawLineEx(attack_triangle.range, attack_triangle.NTangent, 10, GREEN);
			DrawLineEx({ 0,0 }, attack_triangle.NTangent, 10, PURPLE);
		}*/
		if (SWORD_ANIMATION.IsPlaying()) 
			SWORD_ANIMATION.Draw({player.position.x+player.size.x/2,player.position.y + player.size.y / 2 });
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
		};
		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i].active) {
				if (enemies[i].direction.x > 0)
				{
					enemies[i].isWalkingLeft = false;
					enemies[i].DrawWalkRight();
				}
				else if (enemies[i].direction.x < 0)
				{
					enemies[i].isWalkingLeft = true;
					enemies[i].DrawWalkLeft();
				}
				else if (enemies[i].direction.y > 0)
				{
					if (enemies[i].isWalkingLeft)
						enemies[i].DrawWalkLeft();
					else
						enemies[i].DrawWalkRight();
				}
				else if (enemies[i].direction.y < 0)
				{
					if (enemies[i].isWalkingLeft)
						enemies[i].DrawWalkLeft();
					else
						enemies[i].DrawWalkRight();
				}
				else
				{
						enemies[i].DrawWalkLeft();

				};

			}
		}

		HUD healthBar = HUD(100, 110, 125, GREEN, false);
		healthBar.SetValue(player.health);
		healthBar.DrawHUD(Vector2Add(player.position, Vector2Scale(player.size, 0.5)));
		HUD dashBar = HUD(player.dashCooldown,80, 95, GOLD, false);
		dashBar.SetValue(player.dashCooldown - player.cooldownTimer);
		dashBar.DrawHUD(Vector2Add(player.position, Vector2Scale(player.size, 0.5)));

	}
	EndMode2D();
	EndDrawing();
}

void DrawMenu() {
	BeginDrawing();
	DrawTexturePro(
		backgroundMenu,
		{ 0, 0, (float)backgroundMenu.width, (float)backgroundMenu.height },
		{ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() },
		{ 0, 0 },
		0,
		WHITE
	);

	for (auto& button : buttons) {
		button.Draw();
	}
	EndDrawing();
}

void DrawShop() {
	BeginDrawing();
	DrawTexturePro(
		backgroundShop,
		{ 0, 0, (float)backgroundShop.width, (float)backgroundShop.height }, // ������� ��������
		{ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() },         // ������� ������
		{ 0, 0 },                                                          // ����� ����������
		0,                                                               // ���� ��������
		WHITE                                                            // ����
	);
	
	for (auto& button : buttons) {
		button.Draw();
	}
	DrawText(("cost: "+ std::to_string(cost1)).c_str(), 400, SCREEN_HEIGHT / 2.38, 14, YELLOW);
	DrawText(("cost: " + std::to_string(cost2)).c_str(), 900, SCREEN_HEIGHT / 2.38, 14, YELLOW);
	DrawText(("cost: " + std::to_string(cost3)).c_str(), 1360, SCREEN_HEIGHT / 2.38, 14, YELLOW);

	DrawText(("count: " + std::to_string(count1)).c_str(), 400, SCREEN_HEIGHT / 2.26, 14, YELLOW);
	DrawText(("count: " + std::to_string(count2)).c_str(), 900, SCREEN_HEIGHT / 2.26, 14, YELLOW);
	DrawText(("count: " + std::to_string(count3)).c_str(), 1360, SCREEN_HEIGHT / 2.26, 14, YELLOW);


	EndDrawing();

}