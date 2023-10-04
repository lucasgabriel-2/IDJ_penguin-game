#include <SDL2/SDL.h>
#include <iostream>

#include "GameObject.h"
#include "Component.h"

#pragma once

using std::string;

class Sprite : public Component{

    public:

        Sprite(GameObject& associated);
        Sprite(GameObject& associated, string file);
        ~Sprite();
        void Open(string file);
        void SetClip (int x, int y, int w, int h);
        void Render();
        int GetWidth();
        int GetHeight();
        bool IsOpen();
        void Update(float dt);
        bool Is(string type);

    private:

        SDL_Texture* texture;
        int  width;
        int height;
        SDL_Rect clipRect;

};