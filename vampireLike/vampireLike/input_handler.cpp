#include "inputHandler.h"
#include "globals.h"
#include <raymath.h>

void Gamestate::fullscrean() {
    if (IsKeyReleased(KEY_F11)) ToggleBorderlessWindowed();
}

void Player::Update() {
	float deltaTime = GetFrameTime(); // ����� ����� �������

	Vector2 direction = { 0, 0 };
	if (IsKeyDown(KEY_D) or IsKeyDown(KEY_RIGHT)) direction.x += 1;
	if (IsKeyDown(KEY_A) or IsKeyDown(KEY_LEFT)) direction.x -= 1;
	if (IsKeyDown(KEY_W) or IsKeyDown(KEY_UP)) direction.y -= 1;
	if (IsKeyDown(KEY_S) or IsKeyDown(KEY_DOWN)) direction.y += 1;

	// ������������ ������� �����������, ����� ����� �� ��������� �� ������������ x2
	if (Vector2Length(direction) > 0) {
		direction = Vector2Normalize(direction);
	}
	// ���������� �������� � ���������������� �������
	position.x += direction.x * speed * deltaTime;
	position.y += direction.y * speed * deltaTime;
	damageAura.center = Vector2Add(position, Vector2Scale(size, 0.5f));
	//position.x = Clamp(position.x, 0, SCREEN_WIDTH - size.x); // ����������� ������ �� X
	//position.y = Clamp(position.y, 0, SCREEN_HEIGHT - size.y); // ����������� ������ �� Y

	// ������ �����
	if (IsKeyPressed(KEY_SPACE) and cooldownTimer <= 0 and !isDashing) {
		isDashing = true; // ��������� �����
		speed += dashSpeed; // ���������� ��������
		dashTimer = dashDuration; // ������ ������� �����

	}

	// ��������� ������� �����
	if (isDashing) {
		dashTimer -= deltaTime; // ���������� ������� �����
		if (dashTimer <= 0) {
			isDashing = false; // ���������� �����
			speed -= dashSpeed; // ������� � �������� ��������
			cooldownTimer = dashCooldown; // ������ ������� ��������������
		}
	}

	// ��������� ������� ��������������
	if (cooldownTimer > 0) {
		cooldownTimer -= deltaTime; // ���������� ������� ��������������
	}


	Rectangle playerRect = { position.x, position.y, size.x, size.y };
	Rectangle testRect = { 500, 500, 200, 200 };


}