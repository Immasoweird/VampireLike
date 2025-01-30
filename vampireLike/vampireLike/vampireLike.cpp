#include <iostream>
#include "raylib.h"
#include <vector>
#include <raymath.h>
#include <map>
using namespace std;


// Глобальные переменные
const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;

// Классы
class Gamestate {
public:
	int score;
	bool gameOver;
}gamestate;

class WeaponList {
public:
	map<string, int> weapon = {
		{"claymore", 1},
		{"bow", 2},
		{"axe", 3},
	};

};

//classes
class Player {
public:
	Vector2 position = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	Vector2 size = { 100, 100 };
	float speed = 700;
	int lvl = 1;
	int health = 100;
	float hpRegen = 0.5;
	int armor = 10;

	int luck = 0;
	float evasion = 0; // percent 
	float lifesteal = 1; // percent 
	float collectArea = 0; // percent 

	int damage = 1;
	float critDamage = 50; // percent 
	float critChance = 5; // percent 
	int attackSpeed = 1;
	int attackRange = 100;

	//dash
	bool isDashing = false; // Отслеживание состояния рывка
	float dashDuration = 0.15f; 
	float dashSpeed = 1500.0f;
	float dashCooldown = 0.8f;
	float cooldownTimer = 0.0f; // Таймер для отслеживания времени восстановления
	float dashTimer = 0.0f;     // Таймер для отслеживания времени рывка

	void Update() {
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

		position.x = Clamp(position.x, 0, SCREEN_WIDTH - size.x); // Ограничение экрана по X
		position.y = Clamp(position.y, 0, SCREEN_HEIGHT - size.y); // Ограничение экрана по Y

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



	}


	void Draw() {
		DrawCircleV(position+size/2, attackRange, RED); // Коллизия радиуса атаки
		DrawRectangleV(position, size, GOLD); //Коллизия игрока
	} 

}player;

struct TextureInfo {
	Texture2D texture;           // Текстура
	Vector2 position;            // Позиция на экране
};

// Текстуры
TextureInfo background;


// declare funcs 
void InitGame();
void LoadTextures();
void UpdateGame();
void DrawGame();
void UnloadGame();



int main() {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Devil May Cry 9");
	SetTargetFPS(165);

	InitGame();

	while (!WindowShouldClose()) {
		UpdateGame();
		DrawGame();

		if (gamestate.gameOver) InitGame();
	}
	CloseWindow();
}


void InitGame() {
	gamestate.score = 0;
	gamestate.gameOver = false;
	LoadTextures();
}



void UpdateGame() {
	player.Update();
	if (gamestate.gameOver) return;
}

void LoadTextures() {
	Image image1 = LoadImage("F:\aC++\GITHUB\VampireLike\vampireLike\vampireLike\assets\Backgroundbackground.jpg");
	background.texture = LoadTextureFromImage(image1);
	background.position = { SCREEN_WIDTH, SCREEN_HEIGHT };
	UnloadImage(image1);
}

void DrawGame() {
	BeginDrawing();
	ClearBackground(DARKGRAY);
	DrawTextureV(background.texture, background.position, WHITE);
	player.Draw();

	EndDrawing();

}

void UnloadGame() {
	UnloadTexture(background.texture);
}
