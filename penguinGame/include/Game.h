#include <SDL2/SDL.h>  
#include <iostream>
#include "State.h"

#pragma once

using std::string;

class Game{

    public:

        ~Game();
        void Run();
        SDL_Renderer* GetRenderer();
        State& GetState();
        static Game& GetInstance();

    private:

        Game(string title, int width, int height);
        static Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        State* state;
        
        string Title;
        int Width;
        int Height;

};

