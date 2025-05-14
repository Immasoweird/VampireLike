#include "initialize.h"
#include "updateHandler.h"
#include "render.h"
#include "inputHandler.h"
#include "gameObjects.h"
#include "raylib.h"
#include "globals.h"



int main() {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Devil May Cry 9");
	SetTargetFPS(165);
	InitMenu();

	
	while (!WindowShouldClose()) {

		switch (currentScreen) {
		case 0:
			UpdateMenu();
			DrawMenu();
			break;
		case 1:
			UpdateShop();
			DrawShop();
			break;
		case 2:
			UpdateGame();
			DrawGame();
			break;
		default:
			break;
		}
	}
	UnloadGame();
	CloseWindow();
}