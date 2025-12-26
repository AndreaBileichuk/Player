#include "./../include/audio_manager.h"
#include <string.h>

void InitPlayer(MusicPlayer* player) {
	InitAudioDevice();
	player->isLoaded = false;
	player->isPlaying = false;
	player->volume = 50;
}

void LoadMusic(MusicPlayer* player, const char* filePath) {
	if(player->isLoaded) {
		UnloadMusicStream(player->currentMusic);
	}

	player->currentMusic = LoadMusicStream(filePath);
	player->currentMusic.looping = false;
	player->isLoaded = true;
	player->isPlaying = true;

	SetMusicVolume(player->currentMusic, player->volume / 100.0f);
	const char* fileName = GetFileName(filePath);

	strncpy(player->songTitle, fileName, 255);
	player->songTitle[255] = '\0';

	PlayMusicStream(player->currentMusic);
}

void UpdatePlayer(MusicPlayer* player) {
	if(player->isLoaded && player->isPlaying) {
		UpdateMusicStream(player->currentMusic);
	}
}

void TogglePlayPause(MusicPlayer* player) {
	if(!player->isLoaded) return;

	player->isPlaying = !player->isPlaying;

	if(player->isPlaying) ResumeMusicStream(player->currentMusic);
	else PauseMusicStream(player->currentMusic);
}

void ClosePlayer(MusicPlayer* player) {
	if (player->isLoaded) UnloadMusicStream(player->currentMusic);
   CloseAudioDevice();
}

void IncreaseVolume(MusicPlayer* player) {
	player->volume += 1;
	if(player->volume > 100) player->volume = 100;
	SetMusicVolume(player->currentMusic, player->volume / 100.0f);
}

void DecreaseVolume(MusicPlayer* player) {
	player->volume -= 1;
	if(player->volume < 0) player->volume = 0;
	SetMusicVolume(player->currentMusic, player->volume / 100.0f);
}