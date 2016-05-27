#include "Audio.h"


GE161::Audio::Audio(std::string filename, GE161::Audio::Type type){
	t = type;
	switch (t){
	case MUSIC:
		audioFile = Mix_LoadMUS((GE161::Game::basePath() + filename).c_str());
		if (!audioFile)
			printf(("Mix_LoadMUS(\"" + filename + "\"): %s\n").c_str(), Mix_GetError());
		break;
	case SAMPLE:
		soundChunk = Mix_LoadWAV((GE161::Game::basePath() + filename).c_str());
		if (!audioFile)
			printf(("Mix_LoadWAV(\"" + filename + "\"): %s\n").c_str(), Mix_GetError());
		break;
	}
}

GE161::Audio::~Audio(){
	if (audioFile)
		Mix_FreeMusic(audioFile);
	if (soundChunk)
		Mix_FreeChunk(soundChunk);
}

void GE161::Audio::play(int repeat){
	switch (t){
	case MUSIC:
		if (Mix_PlayMusic(audioFile, repeat) == -1)
			printf("Mix_PlayMusic: %s\n", Mix_GetError());
		break;
	case SAMPLE:
		if (Mix_PlayChannel(-1, soundChunk, repeat) == -1)
			printf("Mix_PlayChannel: %s\n", Mix_GetError());
		break;
	}
}

void GE161::Audio::stop(){
	if (Mix_Playing(-1)){
		Mix_HaltChannel(-1);
	}
}