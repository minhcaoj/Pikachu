#pragma once
#include "CommonFunc.h"

class MusicObject
{
public:
	MusicObject();
	~MusicObject();
	bool initAudio();
	Mix_Music* getMusic() { return music; }
	void closeAudio(Mix_Music* music);
private:
	Mix_Music* music;
};

