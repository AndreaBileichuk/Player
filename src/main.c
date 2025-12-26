#include "raylib.h"
#include "./../include/audio_manager.h"
#include "./../include/ui_draw.h"

int main() {
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "Raylib Player Example");

	SetTargetFPS(60);

	MusicPlayer myPlayer;
   InitPlayer(&myPlayer);

	while(!WindowShouldClose()) {
		if(IsFileDropped()) {
			FilePathList dropped = LoadDroppedFiles();
			
			if (dropped.count > 0) {
            LoadMusic(&myPlayer, dropped.paths[0]);
         }
         UnloadDroppedFiles(dropped);
		}

		if (IsKeyPressed(KEY_SPACE)) {
         TogglePlayPause(&myPlayer);
      }

      UpdatePlayer(&myPlayer);

		BeginDrawing();
			ClearBackground(RAYWHITE);

			DrawInterface(&myPlayer, screenWidth, screenHeight);
		EndDrawing();
	}

	ClosePlayer(&myPlayer);
   CloseWindow();
	
	return 0;	
}