#include "initialize.h"
#include "globals.h"
#include <raymath.h>
#include "gameObjects.h"



Player::Player() {
	this->position = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	this->damageAura = { {position.x + 50, position.y + 50},200,{position.x + 50, position.y + 50},RED };
	this->size = { 100,100 };
	this->speed = 700;
	this->attackRange = 200;
	this->attackAngle = PI / 6;
	this->health = 100;
	this->hpRegen = 0.5;
	this->armor = 10;
	this->direction = { 0,0 };

	this->luck = 0;
	this->reroll = 0;
	this->evasion = 0; // percent 
	this->lifesteal = 1; // percent 
	this->collectArea = 0; // percent 

	this->damage = 1;
	this->critDamage = 50; // percent 
	this->critChance = 5; // percent 
	this->attackSpeed = 1;

	//dash
	this->isDashing = false; // Отслеживание состояния рывка
	this->dashDuration = 0.15f;
	this->dashSpeed = 1500.0f;
	this->dashCooldown = 3.8f;
	this->cooldownTimer = 0.0f; // Таймер для отслеживания времени восстановления

	this->idleTextureLeft = {};
	this->idleTextureRight = {};
	this->FrameCounter = 1;
}

void InitEnemies(int enemiesNumber) {
	enemies.clear();
	for (int i = 0; i < enemiesNumber; i++)
	{
		int x, y;
		if (i % 4 == 0) {
			x = GetRandomValue(player.position.x - SCREEN_WIDTH - 300, player.position.x - SCREEN_WIDTH);
			y = GetRandomValue(player.position.y - SCREEN_HEIGHT, player.position.y + SCREEN_HEIGHT);
		}
		if (i % 4 == 1) {
			x = GetRandomValue(player.position.x + SCREEN_WIDTH, player.position.x + SCREEN_WIDTH + 300);
			y = GetRandomValue(player.position.y - SCREEN_HEIGHT, player.position.y + SCREEN_HEIGHT);
		}
		if (i % 4 == 2) {
			x = GetRandomValue(player.position.x - SCREEN_WIDTH, player.position.x + SCREEN_WIDTH);
			y = GetRandomValue(player.position.y - SCREEN_HEIGHT - 300, player.position.y - SCREEN_HEIGHT);
		}
		if (i % 4 == 3) {
			x = GetRandomValue(player.position.x - SCREEN_WIDTH, player.position.x + SCREEN_WIDTH);
			y = GetRandomValue(player.position.y + SCREEN_HEIGHT, player.position.y + SCREEN_HEIGHT + 300);
		}

		int width = 150;
		int height = 150;
		Rectangle body = { x,y,width,height };
		Vector2 speed = { 1.0f ,1.0f };
		Vector2 position = { x,y };
		Color color = BLUE;
		auto active = true;
		float health = 100;
		float damage = 1;
		Enemy current = Enemy{
				body,
				speed,
				position,
				color,
				active,
				health,
				damage,
				enemyTexture
		};
		enemies.push_back(current);
	}
}
void InitGame() {
	gamestate.camera.target = Vector2Add(player.position, Vector2Scale(player.size, 0.5f));
	gamestate.camera.offset = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
	gamestate.camera.zoom = 0.5f;
	player = {};
	player.texture = playerTexture;
	player.runTextureLeft = playerRunTextureLeft;
	player.runTextureRight = playerRunTextureRight;
	player.idleTextureLeft = playerIdleTextureLeft;
	player.idleTextureRight = playerIdleTextureRight;
	attack_triangle = { };
	attack = false;
	shootSpeed = 1200.0f;
	waveCount = 1;
	gamestate.score = 0;
	player.lvl = 0;

	upgradeButton = { "damage",
10,
"adawd",
	};

	Stat atackStat = { "damage",
	1,
	10,
	111,

	[](int lvl) {return 1 * lvl;} };

	gameStats.push_back(atackStat);

	shoot.resize(MAX_SHOOTS);
	for (int i = 0; i < MAX_SHOOTS; i++) {
		shoot[i].position = { 0,0 };
		shoot[i].speed = { 0,0 };
		shoot[i].active = false;
		shoot[i].color = WHITE;

		Vector2 position = { 0,0 };
		int radius = 250;
		Vector2 center = { 0, 0 };
		Color color = PINK;
		Circle body = {
			position,
			radius,
			center,
			color,
		};

		bool active = false;
		float damage = 100;

		shoot[i].explosion = {
			body,
			active,
			damage,
		};
	}

	InitEnemies(10);
	if (!spritesLoaded) {
		LoadTextures();
		spritesLoaded = true;
	}
}

void LoadTextures() {
	Image image1 = LoadImage("assets\\Background\\background.png");
	ImageResize(&image1, 10000, 10000);
	background.texture = LoadTextureFromImage(image1);
	background.position = { -5000, -5000 };
	UnloadImage(image1);

	Image image2 = LoadImage("assets\\_IdleRight.png");
	ImageResize(&image2, image2.width * 3, image2.height * 3);
	playerIdleTextureRight = LoadTextureFromImage(image2);
	player.idleTextureRight = playerIdleTextureRight;
	
	image2 = LoadImage("assets\\_IdleLeft.png");
	ImageResize(&image2, image2.width * 3, image2.height * 3);
	playerIdleTextureLeft = LoadTextureFromImage(image2);
	player.idleTextureLeft = playerIdleTextureLeft;

	image2 = LoadImage("assets\\_RunRight.png");
	ImageResize(&image2, image2.width * 3, image2.height * 3);
	playerRunTextureRight = LoadTextureFromImage(image2);
	player.runTextureRight = playerRunTextureRight;

	image2 = LoadImage("assets\\_RunLeft.png");
	ImageResize(&image2, image2.width * 3, image2.height * 3);
	playerRunTextureLeft = LoadTextureFromImage(image2);
	player.runTextureLeft = playerRunTextureLeft;
	UnloadImage(image2);

	Image image3 = LoadImage("assets\\SkeletonIdle.png");
	ImageCrop(&image3, { 0,0,23,32 });
	ImageResize(&image3, 100, 100);
	enemyTexture = LoadTextureFromImage(image3);
	for (int i = 0; i < MAX_ENEMIES; i++) {
		enemies[i].texture = enemyTexture;
	}
	UnloadImage(image3);

}

void UnloadGame() {
	UnloadTexture(background.texture);
}