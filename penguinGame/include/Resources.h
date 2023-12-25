#include <SDL2/SDL.h>
#include <iostream>
#include <unordered_map>

#include "Music.h"

#pragma once

using std::string;
using std::unordered_map;

class Resources{

    public:
    
        static SDL_Texture* GetImage(string file);
        static void ClearImages();
        static Mix_Music* GetMusic(string file);
        static void ClearMusics();
        static Mix_Chunk* GetSound();
        static void ClearSounds();

    private:

    private:

        static unordered_map<string, SDL_Texture*> imageTable;
        static unordered_map<string, Mix_Music*> musicTable;
        static unordered_map<string, Mix_Chunk*> soundTable;

};