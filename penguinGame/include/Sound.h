#include <SDL2/SDL.h>  
#include <SDL2/SDL_mixer.h>  
#include <iostream>

#include "../include/GameObject.h"

#pragma once

using std::string;

class Sound : public Component{

    public:

        Sound(GameObject& associated);
        Sound(GameObject& associated, string file);
        ~Sound();
        void Play(int times = 0);
        void Stop();
        void Open(string file);
        bool IsOpen();
        void Update(float dt);
        void Render();
        bool Is(string type);
        int getChannel();
        int isPlaying = 1;

    private:

       Mix_Chunk* chunk;
       int channel;

};
