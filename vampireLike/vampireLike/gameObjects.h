#pragma once
#include "raylib.h"
#include <vector>
#include <map>
#include <string>

// Константы
constexpr int SCREEN_WIDTH = 1600;
constexpr int SCREEN_HEIGHT = 900;
constexpr int MAX_ENEMIES = 10;

// Основные структуры
struct Circle {
    Vector2 center;
    float radius;
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

// Класс Gamestate
class Gamestate {
public:
    Camera2D camera;
    int score = 0;
    bool gameOver = false;

    void fullscrean();
};

// Класс WeaponList
class WeaponList {
public:
    std::map<std::string, int> weapon = {
        {"sword", 1},
        {"bow", 2},
        {"axe", 3}
    };
};

// Класс Player
class Player {
private:
    void DrawAuraCirlce();
public:
    Vector2 position;
    Circle damageAura;
    Vector2 size;
    float speed;

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

    int health;
    float hpRegen;
    int armor;

    bool isDashing;
    float dashDuration;
    float dashSpeed;
    float dashCooldown;
    float dashTimer;    


    Player();
    void Update();
    void Draw();
};

// Структура Enemy
struct Enemy {
    Rectangle body;
    Vector2 speed;
    Vector2 position;
    Color color;
    bool active;
    float health;
    Vector2 size;
};