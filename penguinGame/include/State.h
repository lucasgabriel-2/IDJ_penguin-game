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
using std::weak_ptr;
using std::shared_ptr;

class State{

    public:

        State();
        ~State();
        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();
        void Start();
        weak_ptr <GameObject> AddObject(GameObject* go);
        weak_ptr <GameObject> GetObjectPtr(GameObject* go);
        
    private:

        Sprite *bg;
        Music *music;
        bool quitRequested;
        void AddObject(int mouseX, int mouseY);
        bool started;
        vector <shared_ptr <GameObject>> objectArray;
};

