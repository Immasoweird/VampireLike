#pragma once
#include "gameObjects.h"

extern Gamestate gamestate;
extern int cost1;
extern int cost2;
extern int cost3;

extern Player player;
extern Enemy enemy;
extern Weapon weapon;
extern std::vector<Shoot> shoot;
extern std::vector<Enemy> enemies;
extern TextureInfo background;
extern Triangle attack_triangle;
extern bool attack;
extern float shootSpeed;
extern int waveCount;
extern int coins;
extern int currentScreen;
extern Image IdleImage;
extern Rectangle PlayerRectangle;
extern int GlobalFrameCounter;
extern bool spritesLoaded;
extern bool isRunningLeft;
extern Texture2D enemyTextureLeft;
extern Texture2D enemyTextureRight;
extern Texture2D enemyWalkTextureRight;
extern Texture2D enemyWalkTextureLeft;
extern Texture2D playerTexture;
extern Texture2D playerRunTextureRight;
extern Texture2D playerRunTextureLeft;
extern Texture2D playerIdleTextureRight;
extern Texture2D playerIdleTextureLeft;
extern Texture2D SWORD_TEXTURE;
extern std::vector<Stat> gameStats;
extern std::vector<Button> buttons;

extern SwordAnimation SWORD_ANIMATION;
