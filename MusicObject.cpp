#include "MusicObject.h"

MusicObject::MusicObject()
{
	music = nullptr;
}
MusicObject::~MusicObject()
{
	if (music != nullptr)
	{
		Mix_FreeMusic(music);
		music = nullptr;
	}
}

bool MusicObject::initAudio()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        SDL_Log("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }
    return true;
}

Mix_Music* loadMusic(const char* path)
{
    Mix_Music* music = Mix_LoadMUS(path);
    if (!music)
    {
        SDL_Log("Failed to load background music! SDL_mixer Error: %s\n", Mix_GetError());
    }
    return music;
}

void MusicObject::closeAudio(Mix_Music* music)
{
    Mix_FreeMusic(music);
    Mix_CloseAudio();
}
