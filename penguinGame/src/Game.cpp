#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include "../include/Game.h"
#include "../include/Resources.h"
#include "../include/InputManager.h"

#include <cstdlib>
#include <ctime>

using std::string;
using std::cout;

Game* Game::instance;

Game& Game::GetInstance(){

    if(instance != nullptr){
        return *instance;
    }else{
        instance = new Game("Lucas Gabriel Sousa Camargo Paiva - 190112123", 1024, 600);
        return *instance;
    }

}

Game::Game(string title, int width, int height){
    
    Title = title;
    Width = width;
    Height = height;

    if(instance != nullptr){
        cout << "Error already exist a instance, there is an error in the programming logic" << "\n";
    }else{
        instance = this;
    }

    if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0 ){
        SDL_Log("Error in SDL_Init: %s", SDL_GetError());
        exit (EXIT_FAILURE);
    }

    //TODO set the right parameter in IMG_Init and Mix_Init
    //Other flags for Mix_Init: (MIX_INIT_FLUIDSYNTH | MIX_INIT_MODPLUG)

    if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0){
        cout << "Error in IMG_Init" << "\n";
    }

    if(Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 |MIX_INIT_OGG | MIX_INIT_MOD ) == 0){
        cout << "Error in Mix_Init" << "\n";
    }

    if(Mix_OpenAudio( MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0){
        cout << "Error in Mix_OpenAudio" << "\n";
    }

    Mix_AllocateChannels(32);
    
    window = SDL_CreateWindow( &title[0], SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if(window == nullptr){
        cout << "Error in SDL_CreateWindow" << "\n";
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(window == nullptr){
        cout << "Error in SDL_CreateRenderer" << "\n";
    }

    state = new State();

    srand(time(NULL));
}

Game::~Game(){
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

State& Game::GetState(){

    return *state;

}

SDL_Renderer* Game::GetRenderer(){
    return renderer;
}


void Game::Run(){

    state->LoadAssets();
    InputManager &inputManager = InputManager::GetInstance();

    while(state->QuitRequested() != true){
        CalculateDeltaTime();
        inputManager.Update();
        //TODO set the right parameter in Update
        state->Update(0);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }

    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
}

float Game::CalculateDeltaTime(){
    
    int frameEnd = SDL_GetTicks();
    dt = (float) (frameEnd - frameStart) / 1000.0f; 
    frameStart = frameEnd;
    return dt;
}


float Game::GetDeltaTime(){
    return dt;
}