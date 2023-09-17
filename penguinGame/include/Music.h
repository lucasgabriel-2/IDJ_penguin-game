#include <SDL2/SDL.h>  
#include <SDL2/SDL_mixer.h>  

#include <iostream>

#pragma once

using std::string;

class Music{

    public:

        Music();
        Music(string file);
        ~Music();
        void Play(int times = -1);
        void Stop(int msToSop = 1500);
        void Open(string file);
        bool IsOpen();

    private:

       Mix_Music* music;

};

