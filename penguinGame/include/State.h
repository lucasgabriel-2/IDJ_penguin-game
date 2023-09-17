#include <SDL2/SDL.h>  
#include <iostream>

#include "Sprite.h"
#include "Music.h"

#pragma once

class State{

    public:

        State();
        ~State();
        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();

    private:

        Sprite *bg;
        Music *music;
        bool quitRequested;

};

