#pragma once
#include "raylib.h"
#include <vector>
#include <map>
#include <string>
#include <functional>

constexpr int SCREEN_WIDTH = 1600;
constexpr int SCREEN_HEIGHT = 900;

constexpr float SWORD_ATTACK_COOLDOWN = 100.0f; // Êóëäàóí äëÿ àòàêè êîïü¸ì
constexpr float SPEAR_ATTACK_COOLDOWN = 1.0f; // Êóëäàóí äëÿ àòàêè êîïü¸ì
constexpr float BOW_ATTACK_COOLDOWN = 1.0f; // Êóëäàóí äëÿ àòàêè êîïü¸ì

constexpr int MAX_ENEMIES = 10;
constexpr int MAX_SHOOTS = 200;



struct Button {
	std::string title;
	int cost;
	std::string image;
};


struct Stat {
	std::string name;
	int lvl;
	int price;
	int value;

	std::function<int(int)> lvlup;
};

struct Circle {
	Vector2 position;
	float radius;
	Vector2 center;
	Color color;
};

struct Triangle {
	Vector2 first;
	Vector2 second;
	Vector2 third;
	Vector2 range;
	Vector2 tangent;
	Vector2 NTangent;

};

struct TextureInfo {
	Texture2D texture;
	Vector2 position;
};

// class Gamestate
class Gamestate {
public:
	Camera2D camera;
	int score = 0;
	bool gameOver = false;

	void fullscreen();
};

struct HUD
{
private:

	float innerRadius = 80.0f;
	float outerRadius = 120.0f;


	float startAngle = 50.0f;
	const float endAngle = 120.0f;
	const float segments = 200.0f;


	float max_value;
	float current_value;
	Color bar_color;
	bool show_text;

public:

	void DrawHUD(Vector2 position) {
		DrawRing(position, innerRadius-2.5f, outerRadius+2.5f, 47.5f, endAngle+2.5f, (int)segments, BLACK);
		DrawRing(position, innerRadius, outerRadius, startAngle, endAngle, (int)segments, bar_color);
	}
	bool SetValue(float value) {
		if (value < 0 || value > max_value) {
			return false;
		}
		float percentage = value / max_value;
		startAngle = endAngle - value / max_value * 70 ;
	}
	HUD() {};

	HUD(float max_value,int innerRadius, int outerRadius, Color bar_color, bool show_text) :

		max_value(max_value),
		innerRadius(innerRadius),
		outerRadius(outerRadius),
		bar_color(bar_color),
		show_text(show_text)
	{
	};

};

//classes
class Shape {

};


struct Weapon {
	int allWeapons = 4;
	int selectWeapon = 1;
	int attackRange = 200;
	float cooldown = 0.0f;
	int attackSpeed = 1;
	int attackDamage = 111;
	float weaponExp = 0.0f;
	int weaponLevel = 1;
	float critDamage = 50; // percent 
	float critChance = 5; // percent 

	void Attack(Shape x, Shape y) {
		printf("weapon attack");
	};
};

struct Explosion {
	Circle body;
	bool active = false;
	float damage;
};
struct Shoot {
	Vector2 position;
	Vector2 speed;
	float radius;
	bool active;
	Color color;
	Explosion explosion;
};

// class WeaponList
class WeaponList {
public:
	std::map<std::string, int> weapon = {
		{"sword", 1},
		{"bow", 2},
		{"axe", 3}
	};
};

// class Player
class Player {
private:
	void DrawAuraCirlce();
public:
	Vector2 position;
	Circle damageAura;
	Vector2 size;
	Vector2 direction;
	float speed;

	int lvl;
	int luck;
	int reroll;
	float evasion;
	float lifesteal;
	float collectArea;

	int damage;
	int attackRange;
	int attackSpeed;
	float attackAngle;
	float critDamage;
	float critChance;
	float cooldownTimer;
	int FrameCounter;

	int health;
	float hpRegen;
	int armor;

	bool isDashing;
	float dashDuration;
	float dashSpeed;
	float dashCooldown;
	float dashTimer;

	Texture2D texture;
	Texture2D idleTextureRight;
	Texture2D idleTextureLeft;
	Texture2D runTextureRight;
	Texture2D runTextureLeft;

	Player();
	void Update();
	void DrawIdleRight();
	void DrawIdleLeft();
	void DrawRunRight();
	void DrawRunLeft();

};

struct Enemy {
	Rectangle body;
	Vector2 speed;
	Vector2 position;
	Color color;
	bool active;
	float health;
	float damage;

	Texture2D texture;

	void Draw();

};