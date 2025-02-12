#include "inputHandler.h"
#include "globals.h"
#include <raymath.h>

void Gamestate::fullscrean() {
    if (IsKeyReleased(KEY_F11)) ToggleBorderlessWindowed();
}

void Player::Update() {
	float deltaTime = GetFrameTime(); // Время между кадрами

	Vector2 direction = { 0, 0 };
	if (IsKeyDown(KEY_D) or IsKeyDown(KEY_RIGHT)) direction.x += 1;
	if (IsKeyDown(KEY_A) or IsKeyDown(KEY_LEFT)) direction.x -= 1;
	if (IsKeyDown(KEY_W) or IsKeyDown(KEY_UP)) direction.y -= 1;
	if (IsKeyDown(KEY_S) or IsKeyDown(KEY_DOWN)) direction.y += 1;

	// Нормализация вектора направления, чтобы рывок по диагонали не увеличивался x2
	if (Vector2Length(direction) > 0) {
		direction = Vector2Normalize(direction);
	}
	// Применение скорости к нормализованному вектору
	position.x += direction.x * speed * deltaTime;
	position.y += direction.y * speed * deltaTime;
	damageAura.center = Vector2Add(position, Vector2Scale(size, 0.5f));
	//position.x = Clamp(position.x, 0, SCREEN_WIDTH - size.x); // Ограничение экрана по X
	//position.y = Clamp(position.y, 0, SCREEN_HEIGHT - size.y); // Ограничение экрана по Y

	// Логика рывка
	if (IsKeyPressed(KEY_SPACE) and cooldownTimer <= 0 and !isDashing) {
		isDashing = true; // Активация рывка
		speed += dashSpeed; // Увеличение скорости
		dashTimer = dashDuration; // Запуск таймера рывка

	}

	// Обработка времени рывка
	if (isDashing) {
		dashTimer -= deltaTime; // Уменьшение таймера рывка
		if (dashTimer <= 0) {
			isDashing = false; // Завершение рывка
			speed -= dashSpeed; // Возврат к исходной скорости
			cooldownTimer = dashCooldown; // Запуск таймера восстановления
		}
	}

	// Обработка времени восстановления
	if (cooldownTimer > 0) {
		cooldownTimer -= deltaTime; // Уменьшение таймера восстановления
	}


	Rectangle playerRect = { position.x, position.y, size.x, size.y };
	Rectangle testRect = { 500, 500, 200, 200 };


}