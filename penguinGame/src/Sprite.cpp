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
    scale = Vec2(1,1);
    angle = 0.0;
    center = nullptr;
    flip = SDL_FLIP_NONE;

}

Sprite::Sprite(GameObject& associated, string file) : Component(associated){

    texture = nullptr;
    Open(file);
    scale = Vec2(1,1);
    angle = 0.0;
    center = nullptr;
    flip = SDL_FLIP_NONE;

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
    dst.w = (int)(associated.box.w * scale.x);
    dst.h = (int)(associated.box.h * scale.y);

    Game& penguinGame = Game::GetInstance();

    SDL_RenderCopyEx(penguinGame.GetRenderer(), texture, &clipRect, &dst, angle, center, flip);
}

void Sprite::Render(int x, int y){

    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = (int)(associated.box.w * scale.x);
    dst.h = (int)(associated.box.h * scale.y);

    Game& penguinGame = Game::GetInstance();
    
    SDL_RenderCopyEx(penguinGame.GetRenderer(), texture, &clipRect, &dst, angle, center, flip);
}


int Sprite::GetWidth(){
    int spriteWidth = (int) (width * scale.x);
    return spriteWidth;
}


int Sprite::GetHeight(){
    int spriteHeight = (int) (height * scale.y);
    return spriteHeight;
}

bool Sprite::IsOpen(){
    return (texture != nullptr) ? true : false;
}

void Sprite::Update(float dt){

}

bool Sprite::Is(string type){
    return (type == "Sprite") ? true : false;
}


void Sprite::SetScale(float scaleX,float scaleY){

    scale.x = (scaleX != 0) ? scaleX : scale.x;
    scale.y = (scaleY != 0) ? scaleY : scale.y;

    this->associated.box.x += (this->associated.box.w - this->associated.box.w * scale.x) / 2;
    this->associated.box.y += (this->associated.box.h - this->associated.box.h * scale.y) / 2;
    this->associated.box.w *= scale.x;
    this->associated.box.h *= scale.y;
}

Vec2 Sprite::GetScale(){
    return scale;
}

void Sprite::SetAngle(double angle){
    this->angle = angle;
}