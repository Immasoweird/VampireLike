#include "globals.h"

Gamestate gamestate;
Player player;
Enemy enemy;
Weapon weapon;
std::vector<Shoot> shoot;
std::vector<Enemy> enemies;
TextureInfo background;
Triangle attack_triangle;
bool attack;
float shootSpeed;
int waveCount;
int coins;
int cost1;
int cost2;
int cost3;


int count1;
int count2;
int count3;

int currentScreen;
Image IdleImage;
Rectangle PlayerRectangle;
int GlobalFrameCounter;
bool spritesLoaded = false;
bool isRunningLeft;
Texture2D backgroundMenu;
Texture2D backgroundShop;
Texture2D enemyTextureLeft;
Texture2D enemyTextureRight;
Texture2D enemyWalkTextureRight;
Texture2D enemyWalkTextureLeft;
Texture2D playerTexture;
Texture2D playerRunTextureRight;
Texture2D playerRunTextureLeft;
Texture2D playerIdleTextureRight;
Texture2D playerIdleTextureLeft;
Texture2D SWORD_TEXTURE;
Button upgradeButton;
std::vector<Stat> gameStats;
std::vector<Button> buttons;
SwordAnimation SWORD_ANIMATION;
