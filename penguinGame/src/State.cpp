#include "../include/State.h"

State::State(){

    quitRequested = false;
    bg = new Sprite("img/ocean.jpg");
    music = new Music("audio/stageState.ogg");

}

State::~State(){

    delete(bg);
    delete(music);

}

void State::LoadAssets(){
    
    music->Play();

}

void State::Update(float dt){
    
    if(SDL_QuitRequested() == true){
        quitRequested = true;
    }   

}

void State::Render(){
    //TODO set the right parameter in Render()
   bg->Render(0,0);
}

bool State::QuitRequested(){

    return quitRequested;
}

