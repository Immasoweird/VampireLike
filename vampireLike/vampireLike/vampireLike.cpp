#include <iostream>
#include "raylib.h"
#include <vector>
#include <raymath.h>
using namespace std;


// Глобальные переменные
const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;
const int MAX_ENEMIES = 10;

int score;
bool gameOver;

//classes
class Player {
public:
	Vector2 position = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	Vector2 size = { 100, 100 };
	float speed = 3;
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
	int attackRange = 10;

	void Control() {
		if (IsKeyDown(KEY_D)) position.x += speed;
		if (IsKeyDown(KEY_A)) position.x -= speed;
		if (IsKeyDown(KEY_W)) position.y -= speed;
		if (IsKeyDown(KEY_S)) position.y += speed;

		if (position.x < 0) position.x += speed;
		if (position.x > (SCREEN_WIDTH - 110)) position.x -= speed;
		if (position.y < 0) position.y += speed;
		if (position.y > (SCREEN_HEIGHT - 110)) position.y -= speed;

<<<<<<< Updated upstream
	}
}player;


=======
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

		//if (CheckCollisionRecs(playerRect, testRect)) {
		//	printf("daoiwhfdoawihfoiawhfoiawhfoiawfhoiwaqfho\n");
		//}

		//if (CheckCollisionCircleRec(position + size / 2, attackRange, testRect)) {
		//	printf("111111111111111111111111111111\n");
		//	float distance = Vector2Distance( );

		//	// Проверяем, находится ли объект в области коллизии
		//	if (distance <= collisionRadius)
		//}
	}



	void Draw() {
		DrawCircleV(Vector2Add(position, Vector2Scale(size, 0.5f)), attackRange, RED);//Коллизия атаки 
		DrawRectangleV(position, size, GOLD); //Коллизия игрока
	}

};

struct Enemy {
	Rectangle body;
	Vector2 speed;
	Vector2 position;
	Color color;
	bool active;
	Vector2 size = { 100, 100 };
	int lvl = 1;
	int health = 10;
	int armor = 0;
	int damage = 1;
};

struct TextureInfo {
	Texture2D texture;           // Текстура
	Vector2 position;            // Позиция на экране
};

struct Circle {
	Vector2 center;
	float radius;
};

// Текстуры
TextureInfo background;
vector<Enemy> enemies;
Player player;
>>>>>>> Stashed changes

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
	gamestate.gameOver = false;
	while (!WindowShouldClose()) {
		UpdateGame();
		DrawGame();

<<<<<<< Updated upstream
		if (gameOver) InitGame();
=======
		if (gamestate.gameOver) 
			InitGame();
>>>>>>> Stashed changes
	}
	CloseWindow();
}


void InitGame() {
<<<<<<< Updated upstream
	score = 0;
	gameOver = false;
=======
	int posX, posY;
	// Инициализация камеры
	gamestate.camera.target = Vector2Add(player.position, Vector2Scale(player.size, 0.5f)); // Центр игрока
	gamestate.camera.offset = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f }; // Центр экрана
	gamestate.camera.zoom = 0.5f;

	gamestate.score = 0;
	gamestate.gameOver = false;

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
		enemies.push_back(
			current
		);
	}

	LoadTextures();
>>>>>>> Stashed changes
}



void PrintEnemies(const vector<Enemy>& items) {
	for (const auto& item : items)
	{
		cout << item.position.x << " " << item.position.y << "\n";
	}
}
void UpdateGame() {
<<<<<<< Updated upstream
	player.Control();
	if (gameOver) return;
=======
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

	for (int i = 0; i < enemies.size(); i++)
	{
		auto playerPosition = player.position;
		Vector2 direction = Vector2Normalize(Vector2Subtract(playerPosition, enemies[i].position));
		Vector2 move = { enemies[i].speed.x * direction.x,enemies[i].speed.y * direction.y };
		enemies[i].position = Vector2Add(enemies[i].position,move);
		enemies[i].body.x = enemies[i].position.x;
		enemies[i].body.y = enemies[i].position.y;
	}
>>>>>>> Stashed changes
}

void LoadTextures() {

}

void DrawGame() {
	BeginDrawing();
	ClearBackground(DARKGRAY);
<<<<<<< Updated upstream
	DrawRectangleV(player.position, player.size, GOLD);
=======



	BeginMode2D(gamestate.camera);
	{
		DrawTextureV(background.texture, background.position, WHITE);
		player.Draw();
		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			if (enemies[i].active) {
				DrawRectangleRec(enemies[i].body,enemies[i].color);
			}
		}
	}
	EndMode2D();

>>>>>>> Stashed changes

	EndDrawing();



	UpdateGame();
}

void UnloadGame() {
	//UnloadTexture
}
