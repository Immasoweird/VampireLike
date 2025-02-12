#include "raylib.h"
#include "initialize.h"
#include "updateHandler.h"
#include "render.h"
#include "inputHandler.h"

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
	return 0;
}