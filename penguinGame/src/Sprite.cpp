#include "../include/Sprite.h"
#include <iostream>

#include "../include/Game.h"
#include "../include/Resources.h"
#include "../include/Camera.h"
#include <SDL2/SDL_image.h>

using std::string;
using std::cout;

Sprite::Sprite(GameObject& associated) : Component(associated){
    
    texture = nullptr; 

}

Sprite::Sprite(GameObject& associated, string file) : Component(associated){

    texture = nullptr;
    Open(file);

}

Sprite::~Sprite(){
    

}

void Sprite::Open(string file){
    
    texture = Resources::GetImage(&file[0]);

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    //TODO set the right parameter in SetClip()
    SetClip(0,0,width,height);
    
}


void Sprite::SetClip(int x, int y, int w, int h){
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;

    this->associated.box.x = x;
    this->associated.box.y = y;
    this->associated.box.w = w;
    this->associated.box.h = h;
}

void Sprite::Render(){

    SDL_Rect dst;
    dst.x = associated.box.x - Camera::pos.x;
    dst.y = associated.box.y - Camera::pos.y;
    dst.w = associated.box.w;
    dst.h = associated.box.h;

    Game& penguinGame = Game::GetInstance();

    SDL_RenderCopy(penguinGame.GetRenderer(), texture, &clipRect, &dst);
}

void Sprite::Render(int x, int y){

    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = associated.box.w;
    dst.h = associated.box.h;

    Game& penguinGame = Game::GetInstance();

    SDL_RenderCopy(penguinGame.GetRenderer(), texture, &clipRect, &dst);
}


int Sprite::GetWidth(){
    return width;
}


int Sprite::GetHeight(){
    return height;
}

bool Sprite::IsOpen(){
    return (texture != nullptr) ? true : false;
}

void Sprite::Update(float dt){

}

bool Sprite::Is(string type){
    return (type == "Sprite") ? true : false;
}
