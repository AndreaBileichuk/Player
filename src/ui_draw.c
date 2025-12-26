#include "../include/ui_draw.h"
#include <stdio.h>

// Function declarations
void DrawVolume(MusicPlayer* player, int screenWidth, int screenHeight);

void DrawInterface(MusicPlayer* player, int screenWidth, int screenHeight) {
    
	if (!player->isLoaded) {
      const char* text = "DRAG & DROP MUSIC FILE HERE (.mp3, .wav)";
      int textWidth = MeasureText(text, 20);
      
      DrawText(text, (screenWidth - textWidth) / 2, screenHeight / 2 - 10, 20, DARKGRAY);
        
      DrawRectangleLines(50, 50, screenWidth - 100, screenHeight - 100, LIGHTGRAY);
      return; 
   }

    DrawText("NOW PLAYING:", 50, 50, 20, LIGHTGRAY);
    DrawText(player->songTitle, 50, 80, 20, DARKGRAY);

    int centerY = screenHeight / 2;
    Color waveColor = MAROON;
    
    for (int i = 40; i < screenWidth - 80; i += 5) {
        float height = 2.0f; 

        if (player->isPlaying) {
            height = GetRandomValue(10, 150) * (0.2f + (float)i / screenWidth * 0.5f);
        }

        DrawLine(i, centerY - height, i, centerY + height, waveColor);
    }

    float timePlayed = GetMusicTimePlayed(player->currentMusic);
    float timeTotal = GetMusicTimeLength(player->currentMusic);
    
    if (timeTotal <= 0) timeTotal = 1.0f; 

    float progress = timePlayed / timeTotal;
    
    int barX = 50;
    int barY = screenHeight - 80;
    int barWidth = screenWidth - 100;
    int barHeight = 15;

    DrawRectangle(barX, barY, barWidth, barHeight, LIGHTGRAY);
    DrawRectangle(barX, barY, (int)(barWidth * progress), barHeight, RED);

	 int currentMin = (int)(timePlayed / 60);
    int currentSec = (int)timePlayed % 60;
    int totalMin = (int)(timeTotal / 60);
    int totalSec = (int)timeTotal % 60;

    const char* timeText = TextFormat("%02d:%02d / %02d:%02d", 
                                     currentMin, currentSec, 
                                     totalMin, totalSec);
    
    DrawText(timeText, barX, barY - 30, 20, GRAY);

	DrawVolume(player, screenWidth, screenHeight);

    if (!player->isPlaying) {
        DrawText("PAUSED", screenWidth / 2 - 60, centerY - 20, 40, RED);
    }
}


// A function to show volume bar on the ui
void DrawVolume(MusicPlayer* player, int screenWidth, int screenHeigh) {
	int volBarHeight = 200;
	int volBarWidth = 20;
	int volX = screenWidth - 40;
	int volY = screenHeigh - 400;

	DrawRectangle(volX, volY, volBarWidth, volBarHeight, LIGHTGRAY);

	int filledHeight = (int)((player->volume / 100.0f) * volBarHeight);

	DrawRectangle(volX, volY + (volBarHeight - filledHeight), volBarWidth, filledHeight, MAROON);

	DrawText("VOL", volX - 10, volY + volBarHeight + 5, 10, GRAY);
    
    const char* volText = TextFormat("%d%%", player->volume);
    DrawText(volText, volX - 10, volY - 20, 10, DARKGRAY);
}