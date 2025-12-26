#include "./../include/audio_manager.h"
#include <string.h>

void InitPlayer(MusicPlayer* player) {
	InitAudioDevice();
	player->isLoaded = false;
	player->isPlaying = false;
	player->volume = 1.0f;
}

void LoadMusic(MusicPlayer* player, const char* filePath) {
	if(player->isLoaded) {
		UnloadMusicStream(player->currentMusic);
	}

	player->currentMusic = LoadMusicStream(filePath);
	player->currentMusic.looping = false;
	player->isLoaded = true;
	player->isPlaying = true;

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