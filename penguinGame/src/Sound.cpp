#include "../include/Sound.h"
#include <iostream>

using std::string;
using std::cout;

Sound::Sound(GameObject& associated) : Component (associated){

    chunk = nullptr;
}

Sound::Sound(GameObject& associated, string file) : Component (associated){
    
    chunk = nullptr;
    Open(file);
}

void Sound::Play(int times){
    channel = Mix_PlayChannel(-1, chunk, times);
}

void Sound::Stop(){

    if(chunk != nullptr){
        Mix_HaltChannel(channel);
    }

}

void Sound::Open(string file){
    
    chunk = Mix_LoadWAV(&file[0]);
    if(chunk == nullptr){
        SDL_Log("Error in Mix_LoadWAV: %s", SDL_GetError());
        cout << "Error in Mix_LoadWAV" << "\n";
    }
    
}

Sound::~Sound(){

    if(chunk != nullptr){
        Mix_HaltChannel(channel);
        Mix_FreeChunk(chunk);
    }

}

void Sound::Update(float dt){

}

void Sound::Render(){

}

bool Sound::Is(string type){
    return (type == "Sound") ? true : false;
}

int Sound::getChannel(){
    return channel;
}