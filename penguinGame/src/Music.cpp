#include "../include/Music.h"
#include <iostream>

using std::string;
using std::cout;

Music::Music(){
    music = nullptr;
}

Music::Music(string file){

    music = nullptr;
    Open(file);

}

void Music::Play(int times){

    Mix_PlayMusic(music, times);
}

void Music::Stop(int msToStop){

    Mix_FadeOutMusic(msToStop);

}

void Music::Open(string file){

    music = Mix_LoadMUS( &file[0]);
    if(music == nullptr){
        cout << "Error in Mix_LoadMUS" << "\n";
    }
    
}

bool Music::IsOpen(){
    return (music != nullptr) ? true : false;
}

Music::~Music(){
    
    Stop();
    Mix_FreeMusic(music);

}