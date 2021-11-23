module;

#include<iostream>
#include<string>
#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>

using namespace std;

export module Note;

export class Note {
	static int id;
	const string name;
	const int channel; // channel to play this key (1 to 1)
	Mix_Chunk* audio; // sound to play
	bool isOn;	// is playing
public:
	Note(string name, string wavePath) : channel(id++), name(name) {
		audio = Mix_LoadWAV(wavePath.c_str());
		if (audio == nullptr) {
			std::cerr << "Failed to load high sound effect! SDL_mixer Error: " << Mix_GetError() << '\n';
			throw std::exception(("Fail to load sound: " + wavePath).c_str());
		}
		isOn = false;
	}

	Note(const Note& n) = delete;

	Note& operator=(const Note&) = delete;

	Note(Note&& n) : channel(n.channel), name(n.name) {
		audio = n.audio;
		n.audio = nullptr;
		isOn = false;
	}

	Note& operator=(Note&&) = delete;

	~Note() {
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
		Mix_PlayChannel(channel, audio, 0);
		isOn = true;
	}

	void playHold() {
		if (!isOn) {
			Mix_PlayChannel(channel, audio, 0);
			isOn = true;
		}
	}

	void stop(int ticks) {
		if (isOn) {
			Mix_ExpireChannel(channel, ticks);
		}
		isOn = false;
	}

	void stop() {
		if (isOn) {
			Mix_HaltChannel(channel);
		}
		isOn = false;
	}

	void pause() {
		Mix_Pause(channel);
		isOn = false;
	}

	void resume() {
		Mix_Resume(channel);
		isOn = true;
	}

	string getName() {
		return name;
	}

	int getChannel() {
		return channel;
	}

};

int Note::id = 0;