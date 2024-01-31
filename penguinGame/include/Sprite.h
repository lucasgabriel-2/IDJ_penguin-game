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
        void Render(int x, int y);
        int GetWidth();
        int GetHeight();
        bool IsOpen();
        void Update(float dt);
        bool Is(string type);
        void SetScale(float scaleX,float scaleY);
        Vec2 GetScale();
        double angle;
        SDL_Point* center;
        SDL_RendererFlip flip;
        void SetAngle(double angle);

    private:

        SDL_Texture* texture;
        int  width;
        int height;
        SDL_Rect clipRect;
        Vec2 scale;

};