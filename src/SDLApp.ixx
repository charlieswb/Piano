module;

#include<iostream>
#include<string>
#include<windows.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include"Config.hpp"
#include"resource.h"

export module SDLApp;

export class SDLApp {

    SDLApp() {
        window = nullptr;
        renderer = nullptr;
        font = nullptr;

        if (!initSDL("Untitled")) {
            throw std::exception("InitSDL failed");
        }

        if (!loadFont()) {
            throw std::exception("LoadFont failed");
        }
    }

    bool initSDL(std::string name) {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
        {
            std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << '\n';
            return false;
        }

        window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << '\n';
            return false;
        }

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED /*| SDL_RENDERER_PRESENTVSYNC*/);
        if (renderer == NULL)
        {
            std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << '\n';
            return false;
        }

        if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
            std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << '\n';
            return false;
        }

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
            std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << '\n';
            return false;
        }

        if (Mix_AllocateChannels(88) != 88) {
            std::cerr << "SDL_mixer could not allocate 88 channels.\n";
            return false;
        }

        return true;
    }

    bool loadFont() {
        if (TTF_Init() == -1) {
            std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << '\n';
            return false;
        }

        HRSRC hResource = FindResource(nullptr, MAKEINTRESOURCEW(IDR_TTF2), TEXT("TTF"));
        if (!hResource) {
            std::cerr << "Error Loading Resource TTF" << '\n';
            return false;
        }
        HGLOBAL hData = LoadResource(nullptr, hResource);
        DWORD dataSize = SizeofResource(nullptr, hResource);

        auto data = LockResource(hData);

        auto sdldata = SDL_RWFromConstMem(data, dataSize);

        font = TTF_OpenFontRW(sdldata, 1, 32);
        if (font == NULL) {
            std::cerr << "Failed to load lazy font! SDL_ttf Error: " << TTF_GetError() << '\n';
            return false;
        }

        return true;
    }

public:

    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;

    //Singleton
    static SDLApp& instance() {
        static SDLApp app;
        return app;
    }

    ~SDLApp() {
        //Free global font
        if (font) {
            TTF_CloseFont(font);
            font = nullptr;
        }

        //Destroy renderer
        if (renderer) {
            SDL_DestroyRenderer(renderer);
            renderer = nullptr;
        }

        //Destroy window
        if (window) {
            SDL_DestroyWindow(window);
            window = nullptr;
        }

        //Quit SDL subsystems
        TTF_Quit();
        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    SDLApp(const SDLApp&) = delete;
    SDLApp& operator=(const SDLApp&) = delete;

    SDLApp(SDLApp&&) = delete;
    SDLApp& operator=(SDLApp&&) = delete;

    void prepareScene() {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        //Clear screen
        SDL_RenderClear(renderer);
    }

    void presentScene() {
        // Update screen
        SDL_RenderPresent(renderer);
    }

};
