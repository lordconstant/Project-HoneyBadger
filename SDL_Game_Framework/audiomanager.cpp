

#include "audiomanager.h"

AudioManager* AudioManager::instance = NULL;

AudioManager* AudioManager::getInstance()
{
	if(instance == NULL)
		instance = new AudioManager();
	return instance;
}

AudioManager::AudioManager()
{
	// Initialise Mixer
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);

	// Get some channels
	Mix_AllocateChannels(35);
	Mix_GroupChannels(0, 34 , 1);
}

AudioManager::~AudioManager()
{
	// Free mixer resources
	Mix_HaltGroup(1);

	for(CMAPIT it = soundmap.begin() ; it != soundmap.end() ; ++it)
		Mix_FreeChunk(it->second);

	Mix_CloseAudio();
}

bool AudioManager::addSound(char* filename, string name)
{
	CMAPIT it = soundmap.find(name);;
	Mix_Chunk* chunk = NULL;

	// See if 'name' already exists
	if(it != soundmap.end()) return false;
		
	// Attempt to load wav file
	chunk = Mix_LoadWAV(filename);
	if (chunk == NULL) return false;

	Mix_VolumeChunk(chunk, MIX_MAX_VOLUME);
	soundmap[name] = chunk;
	return true;
}

void AudioManager::playSound(string name)
{
	CMAPIT it = soundmap.find(name);
	if(it != soundmap.end())
		Mix_PlayChannel(-1, it->second, 0);
}

