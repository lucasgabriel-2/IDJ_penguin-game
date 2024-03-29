#include "../include/Rect.h"

Rect::Rect(){

    x = 0;
    y = 0;
    w = 0;
    h = 0;
}

Rect::Rect(float X, float Y, float W, float H){

    x = X;
    y = Y;
    w = W;
    H = H;
    
}

bool Rect::Contains(Vec2 vec){

    if(vec.x >= x && vec.x <= x + w && vec.y >= y && vec.y <= y + h){
        return true;
    }else{
        return false;
    }

}

Vec2 Rect::Center(){
    return Vec2(x + w/2, y + h/2);
}

void Rect::PlaceCenterAt(Vec2 pos){
    x = pos.x - w/2;
    y = pos.y - h/2;
}