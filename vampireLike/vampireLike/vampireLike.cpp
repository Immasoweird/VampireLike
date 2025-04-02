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
	InitGame();
	InitShop();

	
	while (!WindowShouldClose()) {
		if (IsKeyPressed(KEY_RIGHT_BRACKET)) currentScreen++;
		
		else if (IsKeyPressed(KEY_LEFT_BRACKET)) currentScreen--;

		switch (currentScreen) {
		case 0:
			UpdateGame();
			DrawGame();
			break;
		case 1:
			UpdateShop();
			DrawShop();
			break;
		case 2:
			break;
		default:
			break;
		}
	}
	UnloadGame();
	CloseWindow();
}