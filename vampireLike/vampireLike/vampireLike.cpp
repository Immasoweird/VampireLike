#include <iostream>
#include "raylib.h"
#include <vector>
#include <raymath.h>
using namespace std;


// Глобальные переменные
const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;

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
	void Update() {
		if (IsKeyDown(KEY_D) or IsKeyDown(KEY_RIGHT)) position.x += speed;
		if (IsKeyDown(KEY_A) or IsKeyDown(KEY_LEFT)) position.x -= speed;
		if (IsKeyDown(KEY_W) or IsKeyDown(KEY_UP)) position.y -= speed;
		if (IsKeyDown(KEY_S) or IsKeyDown(KEY_DOWN)) position.y += speed;

		position.x = Clamp(position.x, 0, SCREEN_WIDTH - size.x); //Screen Limitation X.pos
		position.y = Clamp(position.y, 0, SCREEN_HEIGHT - size.y); // Screen Limitation Y.pos
			//if (position.x < 0) position.x += speed;
			//if (position.x > (SCREEN_WIDTH - 110)) position.x -= speed;
			//if (position.y < 0) position.y += speed;
			//if (position.y > (SCREEN_HEIGHT - 110)) position.y -= speed;
	}

	void Draw() {
		DrawRectangleV(player.position, player.size, GOLD);
	}

}player;



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

		if (gameOver) InitGame();
	}
	CloseWindow();
}


void InitGame() {
	score = 0;
	gameOver = false;
}



void UpdateGame() {
	player.Update();
	if (gameOver) return;
}

void LoadTextures() {

}

void DrawGame() {
	BeginDrawing();
	ClearBackground(DARKGRAY);
	player.Draw();

	EndDrawing();



	UpdateGame();
}

void UnloadGame() {
	//UnloadTexture
}
