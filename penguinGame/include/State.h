#include <SDL2/SDL.h>  
#include <iostream>
#include <vector>
#include <memory>

#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"

#pragma once

using std::vector;
using std::unique_ptr;

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
        void Input();
        void AddObject(int mouseX, int mouseY);
        vector <unique_ptr <GameObject>> objectArray;
};

