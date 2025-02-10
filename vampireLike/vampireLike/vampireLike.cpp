﻿#include <iostream>
#include "raylib.h"
#include <vector>
#include <raymath.h>
#include <map>
using namespace std;


// Глобальные переменные
const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;
const int MAX_ENEMIES = 10;

// Классы
class Gamestate {
public:
	Camera2D camera; // Глобальная переменная камеры
	int score;
	bool gameOver;

	void fullscreen() {
		if (IsKeyReleased(KEY_F11)) {
			ToggleBorderlessWindowed();
		}
	}
}gamestate;

class WeaponList {
public:
	map<string, int> weapon = {
		{"sword", 1},
		{"bow", 2},
		{"axe", 3},
	};

};

struct Circle {
	Vector2 center;
	float radius;
	Color color;
};
//classes
class Player {
private:
	void DrawAuraCircle() {
		DrawCircleV(damageAura.center, damageAura.radius, damageAura.color);
	}


public:
	Vector2 position = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	Circle damageAura = { {position.x + 50, position.y+50},200,RED };  
	Vector2 size = { 100,100 };
	float speed = 700;
	int attackRange = 200;
	int lvl = 1;
	int health = 100;
	float hpRegen = 0.5;
	int armor = 10;

	int luck = 0;
	int reroll = 0;
	float evasion = 0; // percent 
	float lifesteal = 1; // percent 
	float collectArea = 0; // percent 

	int damage = 1;
	float critDamage = 50; // percent 
	float critChance = 5; // percent 
	int attackSpeed = 1;

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
		damageAura.center = Vector2Add(position,Vector2Scale(size,0.5f));
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

	void Draw() {
		DrawAuraCircle(); //Аура
		DrawRectangleV(position, size, GOLD); //Игрок
		DrawRectangle(500, 500, 200, 200, PURPLE);
	}

}; /////

struct TextureInfo {
	Texture2D texture;           // Текстура
	Vector2 position;            // Позиция на экране
};


struct Enemy {
	Rectangle body;
	Vector2 speed;
	Vector2 position;
	Color color;
	bool active;
	float health = 1000;
	Vector2 size = { 100, 100 };
	int lvl = 1;
	int armor = 0;
	int damage = 1;
};

struct Triangle {
	Vector2 first;
	Vector2 second;
	Vector2 third;
};
// Текстуры
TextureInfo background;
Enemy enemy = {};
Player player = {};
vector<Enemy> enemies;

// declare funcs 
void InitGame();
void LoadTextures();
void UpdateGame();
void DrawGame();
void UnloadGame();

bool CheckCollisionAreaEnemy(Enemy& enemy_p, Circle& dmgArea) {
	return CheckCollisionCircleRec(dmgArea.center, dmgArea.radius, enemy_p.body);
}


bool CheckCollisionAttackRange(const Triangle& triangle, const Rectangle& body) {
	
	std::vector<pair<Vector2, Vector2>> triangle_lines{ {triangle.first,triangle.second}, { triangle.first,triangle.third }, { triangle.second,triangle.third} };

	std::vector<pair<Vector2, Vector2>> rectangle{
		{{body.x, body.y}, { body.x + body.width, body.y }},
		{{body.x, body.y}, { body.x, body.y + body.height }},
		{{body.x + body.width, body.y + body.height}, { body.x + body.width, body.y }},
		{{body.x + body.width, body.y + body.height},{ body.x, body.y + body.height }}
	};
	bool collision = false;
	Vector2 collision_point = {};
	for (const auto& triangle_line : triangle_lines) {
		for (const auto& rect_line : rectangle) {
			if (CheckCollisionLines(triangle_line.first, triangle_line.second, rect_line.first, rect_line.second, &collision_point)) {
				return collision;
			}
		}
	}
	return collision;

}
int main() {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Devil May Cry 9");
	SetTargetFPS(165);
	InitGame();

	while (!WindowShouldClose()) {
		UpdateGame();
		DrawGame();

		if (gamestate.gameOver) 
			InitGame();
	}
	CloseWindow();
}


void InitGame() {
	int posX, posY;
	// Инициализация камеры
	gamestate.camera.target = Vector2Add(player.position, Vector2Scale(player.size, 0.5f)); // Центр игрока
	gamestate.camera.offset = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f }; // Центр экрана
	gamestate.camera.zoom = 0.5f;


	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		int x = GetRandomValue(0, SCREEN_WIDTH);
		int y = GetRandomValue(0, SCREEN_HEIGHT);
		int width = 150;
		int height = 150;
		Rectangle body = { x,y,width,height };
		Vector2 speed = { 1.0f ,1.0f };
		Vector2 position = { x,y };
		Color color = BLUE;
		auto active = true;
		Enemy current = Enemy{
				body,
				speed,
				position,
				color,
				active
		};
		enemies.push_back(current);
	}

	gamestate.score = 0;
	gamestate.gameOver = false;
	LoadTextures();
}


Triangle attack_triangle = {0,0,0};
bool attack = false;

void UpdateGame() {
	gamestate.fullscreen();
	player.Update();
	Vector2 mousePosition = GetMousePosition();
	
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		float x = player.position.x;
		float y = player.position.y;
		Vector2 player_pos = {x,y};
		Vector2 center = Vector2Subtract(player_pos, Vector2Scale(player.size, 0.5f));
		Vector2 mouse = GetMousePosition();
		printf("Center: X = %d, Y = %d\n", (int)center.x, (int)center.y);
		mouse = Vector2Subtract(mouse,gamestate.camera.target);//////////////////////////////////////////////////////////// поменять на add когда в scrn hght / wdth
		printf("Player Position: X = %d, Y = %d\n", (int)player_pos.x, (int)player_pos.y);
		printf("Mouse Position: X = %d, Y = %d\n", (int)mouse.x, (int)mouse.y);
		Vector2 dir = Vector2Normalize({ mouse.x - player_pos.x,mouse.y - player_pos.y });
		Vector2 range = { dir.x * player.attackRange,dir.y * player.attackRange };
		printf("Range: X = %d, Y = %d\n", (int)range.x, (int)range.y);
		Vector2 tangent = Vector2Rotate(dir, 90);
		printf("Tangent: X = %d, Y = %d\n", (int)tangent.x, (int)tangent.y);
		float coef = 0.577 * player.attackRange;
		Vector2 left = { tangent.x * coef,tangent.y * coef };
		Vector2 NTangent = Vector2Negate(tangent);
		Vector2 right = { NTangent.x * coef,NTangent.y * coef };
		attack_triangle = { center,Vector2Add(left,range),Vector2Add(right,range) };
		printf("Triangle:"); 
		printf("1: X = %d, Y = %d\n", (int)attack_triangle.first.x, (int)attack_triangle.first.y); 
		printf("2: X = %d, Y = %d\n", (int)attack_triangle.second.x, (int)attack_triangle.second.y); 
		printf("2: X = %d, Y = %d\n", (int)attack_triangle.third.x, (int)attack_triangle.third.y); 

		attack = true;
		for (int i = 0; i < enemies.size(); i++)
		{
			if (CheckCollisionAttackRange(attack_triangle, enemies[i].body) && CheckCollisionAreaEnemy(enemies[i], player.damageAura)) {
				enemies[i].health -= player.damage;
				cout << enemies[i].health << "\n";
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
		enemies[i].position = Vector2Add(enemies[i].position,move);
		enemies[i].body.x = enemies[i].position.x;
		enemies[i].body.y = enemies[i].position.y;
	}
}

void LoadTextures() {
	Image image1 = LoadImage("C:\\Users\\Academy\\Desktop\\VampireLike\\VampireLike\\vampireLike\\vampireLike\\assets\\Background\\background.png");
	ImageResize(&image1, 10000, 10000);
	background.texture = LoadTextureFromImage(image1);
	background.position = { -5000, -5000 };
	UnloadImage(image1);

}

void DrawGame() {
	BeginDrawing();
	ClearBackground(DARKGRAY);


	BeginMode2D(gamestate.camera);
	{

		DrawTextureV(background.texture, background.position, WHITE);
		player.Draw(); 
		
		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			if (enemies[i].active) {
				DrawRectangleRec(enemies[i].body, enemies[i].color);
				if (attack)
					//printf("dahwdhawhdahw");
					DrawTriangle(attack_triangle.first,attack_triangle.second,attack_triangle.third, GREEN);

			}
		}		// Здесь будут другие объекты (враги, предметы)
	}
	EndMode2D();


	EndDrawing();

}

void UnloadGame() {
	UnloadTexture(background.texture);
}
