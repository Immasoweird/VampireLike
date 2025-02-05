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
	Camera2D camera; // Глобальная переменная камеры
	int score;
	bool gameOver;

	void fullscrean() {
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
	void DrawAuraCirlce() {
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
		DrawAuraCirlce(); //Аура
		DrawRectangleV(position, size, GOLD); //Игрок
	}

}; /////

struct TextureInfo {
	Texture2D texture;           // Текстура
	Vector2 position;            // Позиция на экране
};


struct Enemy {
	Vector2 position;
	Rectangle body;
	Color color;
	Vector2 speed;
	float health;
};
// Текстуры
TextureInfo background;
Enemy enemy = {};
Player player = {};
vector<Enemy> enemies;
Player player;

// declare funcs 
void InitGame();
void LoadTextures();
void UpdateGame();
void DrawGame();
void UnloadGame();

void CheckCollisionAreaEnemy(Enemy& enemy_p, Circle& dmgArea) {
	if (CheckCollisionCircleRec(dmgArea.center, dmgArea.radius,enemy_p.body)) {
		enemy_p.health -= player.damage;
		cout << enemy_p.health;
	}
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

	// Инициализация врага
	enemy.body = { 500, 500, 200, 200};
	enemy.speed = { 10, 10 };
	enemy.color = BLUE;
	enemy.health = 1000;



	gamestate.score = 0;
	gamestate.gameOver = false;
	LoadTextures();
}



void UpdateGame() {
	gamestate.fullscrean();
	player.Update();
	Vector2 mousePosition = GetMousePosition();
	
	if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
		printf("Mouse Position: X = %d, Y = %d\n", (int)mousePosition.x, (int)mousePosition.y); //для упрощения отрисовки координат в дальнейшем
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


	// Проверка на столкновение врага и dmgArea
	CheckCollisionAreaEnemy(enemy, player.damageAura);
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
		DrawRectangleRec(enemy.body,enemy.color);
		
		// Здесь будут другие объекты (враги, предметы)
	}
	EndMode2D();


	EndDrawing();

}

void UnloadGame() {
	UnloadTexture(background.texture);
}
