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
Image IdleImage;
Rectangle PlayerRectangle;
int GlobalFrameCounter;
bool spritesLoaded = false;
