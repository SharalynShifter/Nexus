#pragma once
#include "fmod.hpp"

class Sound
{
private:
	static bool running;
	static bool possible;
	static char* currentSound;
	unsigned int version;
	static FMOD_RESULT result;
	static FMOD::System* fmodsys;
	static FMOD::Sound* sound;
	static FMOD::Channel* channel;

public:
	static void init(void);

	static void setVolume(float v);
	static void setPitch(float p);
	static void load(const char* file);
	static void unload(void);
	static void play(bool pause = false, bool loop = false);
	
	static bool getSound(void);

	static void setPause(bool pause);
	static void setSound(bool sound);

	static void toggleSound(void);
	static void togglePause(void);
};

