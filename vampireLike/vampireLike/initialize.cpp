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
	this->dashCooldown = 0.8f;
	this->cooldownTimer = 0.0f; // Таймер для отслеживания времени восстановления
	this->dashTimer = 0.0f;
}

void InitGame() {
	gamestate.camera.target = Vector2Add(player.position, Vector2Scale(player.size, 0.5f));
	gamestate.camera.offset = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
	gamestate.camera.zoom = 0.5f;
	player = {};
	enemies.clear();
	attack_triangle = { };
	attack = false;
	for (int i = 0; i < MAX_ENEMIES; i++) {
		enemies.push_back({
			{0,0,150,150},     // body
			{1.0f,1.0f},        // speed
			{(float)GetRandomValue(0,SCREEN_WIDTH), (float)GetRandomValue(0,SCREEN_HEIGHT)}, // position
			BLUE,               // color
			true,               // active
			1000,               // health
			{100,100}           // size
			});
	}
	LoadTextures();
}

void LoadTextures() {
	Image image1 = LoadImage("assets\\Background\\background.png");
	ImageResize(&image1, 10000, 10000);
	background.texture = LoadTextureFromImage(image1);
	background.position = { -5000, -5000 };
	UnloadImage(image1);
}

void UnloadGame() {
	UnloadTexture(background.texture);
}