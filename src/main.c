#include "raylib.h"
#include "./../include/audio_manager.h"
#include "./../include/ui_draw.h"

int main() {
	const int screenWidth = 1000;
	const int screenHeight = 550;

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

		if(IsKeyDown(KEY_UP)) {
         IncreaseVolume(&myPlayer);
      }

      if(IsKeyDown(KEY_DOWN)) {
         DecreaseVolume(&myPlayer);
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