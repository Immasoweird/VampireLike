#include "initialize.h"
#include "updateHandler.h"
#include "render.h"
#include "inputHandler.h"
#include "gameObjects.h"
#include <iostream>
#include "raylib.h"
#include <vector>
#include <raymath.h>
#include <map>
using namespace std;

int main() {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Devil May Cry 9");
	SetTargetFPS(165);
	InitGame();
	while (!WindowShouldClose()) {
	
		UpdateGame();
		DrawGame();
	}
	UnloadGame();
	CloseWindow();
}
