#pragma once
#include "gameObjects.h"

extern Gamestate gamestate;
extern Player player;
extern Weapon weapon;
extern std::vector<Shoot> shoot;
extern std::vector<Enemy> enemies;
extern TextureInfo background;
extern Triangle attack_triangle;
extern bool attack;
extern float shootSpeed;
extern int waveCount;
extern Image IdleImage;
extern Rectangle PlayerRectangle;
extern int GlobalFrameCounter;
extern bool spritesLoaded;
extern bool isRunningLeft;
extern Texture2D enemyTexture;
extern Texture2D playerTexture;
extern Texture2D playerRunTextureRight;
extern Texture2D playerRunTextureLeft;
extern Texture2D playerIdleTextureRight;
extern Texture2D playerIdleTextureLeft;