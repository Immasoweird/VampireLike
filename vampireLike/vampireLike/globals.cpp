#include "globals.h"

Gamestate gamestate;
Player player;
Weapon weapon;
std::vector<Shoot> shoot;
Enemy enemy;
std::vector<Enemy> enemies;
TextureInfo background;
Triangle attack_triangle;
bool attack;
float shootSpeed;
int waveCount;
int coins;
int currentScreen;
Image IdleImage;
Rectangle PlayerRectangle;
int GlobalFrameCounter;
bool spritesLoaded = false;
bool isRunningLeft;
Texture2D enemyTexture;
Texture2D playerTexture;
Texture2D playerRunTextureRight;
Texture2D playerRunTextureLeft;

Button upgradeButton;
std::vector<Stat> gameStats;

