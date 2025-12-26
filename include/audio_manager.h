#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "raylib.h"

typedef struct MusicPlayer {
	 Music currentMusic;
	 bool isLoaded;
	 bool isPlaying;
	 int volume;
	 char songTitle[256];
} MusicPlayer;

void InitPlayer(MusicPlayer* player);
void LoadMusic(MusicPlayer* player, const char* filePath);
void UpdatePlayer(MusicPlayer* player);
void TogglePlayPause(MusicPlayer* player);
void ClosePlayer(MusicPlayer* player);

void IncreaseVolume(MusicPlayer* player);
void DecreaseVolume(MusicPlayer* player);

#endif