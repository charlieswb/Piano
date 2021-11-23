#define SDL_MAIN_HANDLED

#include<iostream>
#include<string>
#include<vector>
#include<filesystem>
#include<fstream>
#include<chrono>
#include<thread>
#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_syswm.h>
#include<Windows.h>
#include"Config.hpp"

import SDLApp;
import Piano;
import Key;
import Note;

void imagine();


int main(int argc, char* argv[]) {
	using namespace std;
	using namespace std::this_thread;     // sleep_for, sleep_until
	using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
	using std::chrono::system_clock;
	namespace fs = std::filesystem;

	SDLApp& app = SDLApp::instance();

	SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);
	SDL_RenderClear(app.renderer);

	SDL_Rect topViewport;
	topViewport.x = 0;
	topViewport.y = 0;
	topViewport.w = SCREEN_WIDTH;
	topViewport.h = SCREEN_HEIGHT / 2;
	SDL_RenderSetViewport(app.renderer, &topViewport);
	SDL_SetRenderDrawColor(app.renderer, 90, 90, 90, 255);
	SDL_RenderFillRect(app.renderer, &topViewport);

	SDL_Rect bottomViewport;
	bottomViewport.x = 0;
	bottomViewport.y = SCREEN_HEIGHT / 2;
	bottomViewport.w = SCREEN_WIDTH;
	bottomViewport.h = SCREEN_HEIGHT / 2;
	SDL_RenderSetViewport(app.renderer, &bottomViewport);

	Piano p;
	p.renderPiano(app.renderer);
	app.presentScene();



	bool quit = false;
	while (!quit){
		app.prepareScene();
		p.renderPiano(app.renderer);
		//Handle events on queue
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0){
			//User requests quit
			if (e.type == SDL_QUIT){
				quit = true;
			}

			//Handle button events
			p.handleMouseEvent(&e);
			p.handleKeyboardEvent(&e);
		}


		app.presentScene();
	}


	//sleep_for(2s);
	//SDL_SetRenderDrawColor(app.renderer, 0xff, 0x00, 0x00, 0xff);
	//SDL_RenderDrawRect(app.renderer, p.keys[0]);
	//app.presentScene();

	//p.printNotes();
	//c3.play();
	//imagine();
	//getchar();

	return 0;
}

void imagine() {

	using namespace std::this_thread;     // sleep_for, sleep_until
	using namespace std::chrono_literals; // ns, us, ms, s, h, etc.

	Key c3{ 0, "C3", "C:\\Users\\Alpha\\source\\repos\\Piano\\resources\\ff\\converted\\Piano.ff.C3.aiff", SDL_SCANCODE_UNKNOWN, nullptr };
	Key d3{ 1,"D3", "C:\\Users\\Alpha\\source\\repos\\Piano\\resources\\ff\\converted\\Piano.ff.D3.aiff", SDL_SCANCODE_UNKNOWN, nullptr };
	Key e3{ 2,"E3", "C:\\Users\\Alpha\\source\\repos\\Piano\\resources\\ff\\converted\\Piano.ff.E3.aiff", SDL_SCANCODE_UNKNOWN, nullptr };
	Key f3{ 3,"F3", "C:\\Users\\Alpha\\source\\repos\\Piano\\resources\\ff\\converted\\Piano.ff.F3.aiff", SDL_SCANCODE_UNKNOWN, nullptr };
	Key g3{ 4,"G3", "C:\\Users\\Alpha\\source\\repos\\Piano\\resources\\ff\\converted\\Piano.ff.G3.aiff", SDL_SCANCODE_UNKNOWN, nullptr };
	Key ab3{ 5, "Ab3", "C:\\Users\\Alpha\\source\\repos\\Piano\\resources\\ff\\converted\\Piano.ff.Ab3.aiff", SDL_SCANCODE_UNKNOWN, nullptr };
	Key a3{ 6,"A3", "C:\\Users\\Alpha\\source\\repos\\Piano\\resources\\ff\\converted\\Piano.ff.A3.aiff", SDL_SCANCODE_UNKNOWN, nullptr };
	Key bb3{ 7, "Bb3", "C:\\Users\\Alpha\\source\\repos\\Piano\\resources\\ff\\converted\\Piano.ff.Bb3.aiff", SDL_SCANCODE_UNKNOWN, nullptr };
	Key b3{ 8,"B", "C:\\Users\\Alpha\\source\\repos\\Piano\\resources\\ff\\converted\\Piano.ff.B3.aiff", SDL_SCANCODE_UNKNOWN, nullptr };
	Key c4{ 9,"C4", "C:\\Users\\Alpha\\source\\repos\\Piano\\resources\\ff\\converted\\Piano.ff.C4.aiff", SDL_SCANCODE_UNKNOWN, nullptr };
	Key d4{ 10,"D4", "C:\\Users\\Alpha\\source\\repos\\Piano\\resources\\ff\\converted\\Piano.ff.D4.aiff", SDL_SCANCODE_UNKNOWN, nullptr };
	Key e4{ 11,"E4", "C:\\Users\\Alpha\\source\\repos\\Piano\\resources\\ff\\converted\\Piano.ff.E4.aiff", SDL_SCANCODE_UNKNOWN, nullptr };
	Key f4{ 87,"F4", "C:\\Users\\Alpha\\source\\repos\\Piano\\resources\\ff\\converted\\Piano.ff.F4.aiff", SDL_SCANCODE_UNKNOWN, nullptr };

	
		// verse
		for (int j = 0; j < 4; ++j) {
			
			for (int i = 0; i < 3; ++i) {
				// C
				e3.play(1000); g3.play(1000); c4.play(1000);
				sleep_for(500ms);
				c3.play(1000);
				sleep_for(500ms);
			}

			// Cmaj7
			e3.play(1000); g3.play(1000); b3.play(1000);
			sleep_for(500ms);
			c3.play(1000);
			sleep_for(500ms);

			for (int i = 0; i < 3; ++i) {
				// F
				f3.play(1000); a3.play(1000); c4.play(1000);
				sleep_for(500ms);
				c3.play(1000);
				sleep_for(500ms);
			}

			if (j != 3) {
				a3.play(1000);
				sleep_for(220ms);
				bb3.play(780);
				sleep_for(250ms);
				b3.play(550);
				sleep_for(550ms);
			}
			else { // into bridge
				// F
				f3.play(1000); a3.play(1000); c4.play(1000);
				sleep_for(500ms);
				c3.play(1000);
				sleep_for(500ms);
			}
		}
		// Imagine all the people
		for (int i = 0; i < 2; ++i) {
			// F
			f3.play(1000); a3.play(1000); c4.play(1000);
			sleep_for(500ms);
			c3.play(1000);
			sleep_for(500ms);
		}
		
		for (int i = 0; i < 2; ++i) {
			// Am/E
			a3.play(1000); c4.play(1000); e4.play(1000);
			sleep_for(500ms);
			e3.play(1000);
			sleep_for(500ms);
		}

		for (int i = 0; i < 2; ++i) {
			// Dm7
			f3.play(1000); a3.play(1000); c4.play(1000);
			sleep_for(500ms);
			d3.play(1000);
			sleep_for(500ms);
		}

		for (int i = 0; i < 2; ++i) {
			// F
			f3.play(1000); a3.play(1000); c4.play(1000);
			sleep_for(500ms);
			c3.play(1000);
			sleep_for(500ms);
		}

		//Living for today
		for (int i = 0; i < 3; ++i) {
			// G
			g3.play(1000); b3.play(1000); d4.play(1000);
			sleep_for(500ms);
			d3.play(1000);
			sleep_for(500ms);
		}
		
		// C
		e3.play(1000); g3.play(1000); c4.play(1000);
		sleep_for(500ms);
		c3.play(1000);
		sleep_for(500ms);

		// G7
		g3.play(1000); b3.play(1000); d4.play(1000);
		sleep_for(500ms);
		f4.play(3000);
		sleep_for(500ms);

		// you-hou-hou-ou-ou
		sleep_for(3s);

		for (int j = 0; j < 4; ++j) {
			//You may say
			for (int i = 0; i < 2; ++i) {
				// F
				f3.play(1000); a3.play(1000); c4.play(1000);
				sleep_for(500ms);
				c3.play(1000);
				sleep_for(500ms);
			}
			
			for (int i = 0; i < 2; ++i) {
				// G
				g3.play(1000); b3.play(1000); d4.play(1000);
				sleep_for(500ms);
				d3.play(1000);
				sleep_for(500ms);
			}
			//I'm a dreamer
			if (j % 4 != 3) {
				// C
				e3.play(1000); g3.play(1000); c4.play(1000);
				sleep_for(500ms);
				c3.play(1000);
				sleep_for(500ms);
				// C
				e3.play(1000); g3.play(1000); c4.play(1000);
				sleep_for(500ms);
				c3.play(1000);
				sleep_for(500ms);
				// E
				ab3.play(1000); b3.play(1000); e4.play(1000);
				sleep_for(500ms);
				e3.play(1000);
				sleep_for(500ms);
				// E7
				ab3.play(1000); b3.play(1000); d4.play(1000);
				sleep_for(500ms);
				e4.play(1000);
				sleep_for(500ms);
			}
			else {
				// C end
				e3.play(10000); g3.play(10000); c3.play(10000); c4.play(10000);
				sleep_for(4s);
			}

		}

		// C2 C3
		// G1 C3
		// A1 C3
		// B1 C3
		Mix_HaltChannel(-1);

}