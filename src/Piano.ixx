module;

#include<iostream>
#include<vector>
#include<map>
#include<fstream>
#include<sstream>
#include<string>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include"Config.hpp"

import Note;

using namespace std;

export module Piano;

char layout[] = { 'w','b','w','w','b','w','b','w','w','b','w','b' };

bool isInside(SDL_Rect* r, int x, int y) {
	//Mouse is left of the key
	if (x < r->x) return false;
	
	//Mouse is right of the key
	if (x > r->x + r->w) return false;

	//Mouse above the key
	if (y < r->y) return false;

	//Mouse below the key
	if (y > r->y + r->h) return false;
	
	return true;
}

export class Piano {
	void initRects() {
		// init visual
		int pos = -8;
		whiteKeys.reserve(52);
		blackKeys.reserve(36);

		for (int i = 0; i < 88; ++i) {
			if (layout[i % 12] == 'w') { // white
				whiteKeys.emplace_back( pos + 8, 0, 24, 220 );
				keys.push_back(&whiteKeys.back());
				pos += 24;
			}
			else { // black
				blackKeys.emplace_back( pos, 0, 16, 120 );
				keys.push_back(&blackKeys.back());
			}
		}
	}

	void initNotes() {
		notes.reserve(88);

		string basePath = R"(C:\Users\Alpha\source\repos\Piano\resources\ff\converted\)";
		ifstream file( R"(C:\Users\Alpha\source\repos\Piano\src\Keys.csv)" );

		string line;
		getline(file, line); // dispose header row
		//cout << "reading csv\n";
		while (getline(file, line)) {
			//cout << line << '\n';
			stringstream ss(line);
			string name;
			getline(ss, name, ',');
			string filename;
			getline(ss, filename, ',');
			filename = basePath + filename;
			//cout << "creating note from: " << name << ' ' << filename << ' ' << keyBinding << '\n';
			notes.emplace_back(name, filename);		

			string keyBinding;
			getline(ss, keyBinding, ',');
			keyMapping[SDL_Scancode(stoi(keyBinding))] = &notes.back();
		}
	}
public:
	vector<Note> notes;
	vector<SDL_Rect*> keys;
	vector<SDL_Rect> whiteKeys;
	vector<SDL_Rect> blackKeys;
	map<SDL_Scancode, Note*> keyMapping;
	bool isPlaying;
	Piano() : isPlaying(false){
		initRects();

		initNotes();

	}

	void handleMouseEvent(SDL_Event* e) {
		if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
			int x, y;
			SDL_GetMouseState(&x, &y);
			y -= SCREEN_HEIGHT / 2;
			if (y >= 0) {
				bool found = false;
				//check black keys
				for (int i = 0; i < keys.size(); ++i) {
					if (keys[i]->h == 120) {
						if (isInside(keys[i], x, y)) {
							switch (e->type) {
							case SDL_MOUSEMOTION:
								break;
							case SDL_MOUSEBUTTONDOWN:
								isPlaying = true;
								break;

							case SDL_MOUSEBUTTONUP:
								isPlaying = false;
								break;
							}
							if (isPlaying) {
								notes[i].playHold();
							}
							else {
								notes[i].stop(200);
							}
							found = true;
							break;
						}
						else {
							notes[i].stop(200);
						}
					}
				}
				//check white keys
				if (!found) {
					for (int i = 0; i < keys.size(); ++i) {
						if (keys[i]->h == 220) {
							if (isInside(keys[i], x, y)) {
								switch (e->type) {
								case SDL_MOUSEMOTION:
									break;
								case SDL_MOUSEBUTTONDOWN:
									isPlaying = true;
									break;

								case SDL_MOUSEBUTTONUP:
									isPlaying = false;
									break;
								}
								if (isPlaying) {
									notes[i].playHold();
								}
								else {
									notes[i].stop(200);
								}
								found = true;
								break;
							}
							else {
								notes[i].stop(200);
							}
						}
					}
				}

			}
		}
	}

	void handleKeyboardEvent(SDL_Event* e) {
		if (e->type == SDL_KEYDOWN || e->type == SDL_KEYUP) {
			SDL_Scancode key = e->key.keysym.scancode;
			if (keyMapping.contains(key)) {
				if (e->type == SDL_KEYDOWN) {
					keyMapping[key]->playHold();
				}
				else {
					keyMapping[key]->stop(200);
				}
				
			}
		}
	}

	void printNotes() {
		for (auto& n : notes) {
			//n.play();
			cout << n.getChannel() << ", " << n.getName() << '\n';
		}
	}

	void renderPiano(SDL_Renderer* renderer) {
		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderFillRects(renderer, &whiteKeys[0], whiteKeys.size());
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xaa);
		SDL_RenderDrawRects(renderer, &whiteKeys[0], whiteKeys.size());

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xaa);
		SDL_RenderFillRects(renderer, &blackKeys[0], blackKeys.size());
		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderDrawRects(renderer, &blackKeys[0], blackKeys.size());
	}
};

