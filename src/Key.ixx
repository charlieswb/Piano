module;

#include<iostream>
#include<string>
#include<utility>
#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>

using namespace std;
import Note;

export module Key;

export class Key {
	string name;
	SDL_Rect* rect; // rectangle on screen
	Mix_Chunk* audio; // sound to play
	int channel; // channel to play this key (1-1)
	SDL_Scancode scancode; // key mapping
	bool isOn;	// is playing
public:
	Key(int channel, string name, string wavePath, SDL_Scancode key, SDL_Rect* r): channel(channel), name(name), scancode(key), rect(r) {
		audio = Mix_LoadWAV(wavePath.c_str());
		if (audio == nullptr) {
			std::cerr << "Failed to load high sound effect! SDL_mixer Error: " << Mix_GetError() << '\n';
			throw std::exception(("Fail to load sound: " + wavePath).c_str());
		}
		isOn = false;
	}

	~Key() {
		stop();
		if (audio != nullptr) {
			Mix_FreeChunk(audio);
			audio = nullptr;
		}
	}

	void play(int ticks) {
		Mix_PlayChannelTimed(channel, audio, 0, ticks);
	}

	void play() {
		if (isOn) {
			stop();
		}
		Mix_PlayChannel(channel, audio, 0);
		isOn = true;
	}
	
	void stop() {
		Mix_HaltChannel(channel);
		isOn = false;
	}

	void Pause() {
		Mix_Pause(channel);
		isOn = false;
	}

	void Resume() {
		Mix_Resume(channel);
		isOn = true;
	}

};