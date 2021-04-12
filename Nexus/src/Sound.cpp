#include "Sound.h"
#include "fmod_errors.h"
#include <stdio.h>

// Crucial Information
bool Sound::running = true;
bool Sound::possible = true;
char* Sound::currentSound;
FMOD_RESULT Sound::result;
FMOD::System* Sound::fmodsys = NULL;
FMOD::Sound* Sound::sound;
FMOD::Channel* Sound::channel;

/**
 * Initializes the Sound Class
 *
 */
void Sound::init(void) {
	result = FMOD::System_Create(&fmodsys);
	if (result != FMOD_OK) {
		possible = false;
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}

	if (possible) result = fmodsys->init(2, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK) {
		possible = false;
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}

	if (possible) channel->setVolume(0.0f);
}

/**
 * Sets the Volume of the Sound
 *
 * @param v Volume (0.0f - 1.0f)
 */
void Sound::setVolume(float v) {
	if (possible && running && v >= 0.0f && v <= 1.0f) {
		channel->setVolume(v);
	}
}

/**
 * Sets the Pitch of the Sound
 *
 * @param p Pitch (0.5f = Half, 1.0f = Normal, 2.0f = Double)
 */
void Sound::setPitch(float p) {
	if (possible && running) {
		channel->setPitch(p);
	}
}

/**
 * Loads a Sound File
 *
 * @param file Sound File to be loaded
 */
void Sound::load(const char* file) {
	currentSound = (char*)file;
	if (possible && running) {
		result = sound->release();
		result = fmodsys->createStream(currentSound, FMOD_DEFAULT, 0, &sound);
		if (result != FMOD_OK) {
			possible = false;
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		}
	}
}

void Sound::unload(void) {
	if (possible) {
		result = sound->release();
	}
}

void Sound::play(bool pause) {
	if (possible && running) {
		result = fmodsys->playSound(sound, 0, pause, &channel);
		channel->setMode(FMOD_LOOP_OFF);
	}
}

void Sound::toggleSound(void) {
	running = !running;
	if (running == true) { load(currentSound); play(); }
	if (running == false) { unload(); }
}

void Sound::setPause(bool pause) {
	channel->setPaused(pause);
}

void Sound::setSound(bool s) {
	running = s;
}

void Sound::togglePause(void) {
	//FMOD_BOOL p;
	//channel->getPaused(p);
	//channel->setPaused(!p);
}

/**
 * Checks if the Sound is currently Running
 *
 * @return Sound currently Running
 */
bool Sound::getSound(void) {
	return running;
}