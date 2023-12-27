#include "SDL2/SDL.h"
#include "../include/Camera.h"
#include "../include/InputManager.h"

GameObject* Camera::focus = nullptr;
Vec2 Camera::pos = Vec2(0, 0);
Vec2 Camera::speed = Vec2(130, 130);

void Camera::Follow(GameObject* newFocous){
    
    focus = newFocous;
}

void Camera::UnFollow(){
    
    focus = nullptr;
}

void Camera::Update(float dt){
    
    InputManager &inputManager = InputManager::GetInstance();

    if(focus != nullptr){
        int screenWidth = focus->box.w;
        int screenHeight = focus->box.h;
        pos = Vec2(focus->box.x - screenWidth / 2, focus->box.y - screenHeight / 2);
    }else{
        
        if (inputManager.IsKeyDown(RIGHT_ARROW)) pos.x += speed.x * dt;
        if (inputManager.IsKeyDown(LEFT_ARROW)) pos.x -= speed.x * dt;
        if (inputManager.IsKeyDown(DOWN_ARROW)) pos.y += speed.y * dt;
        if (inputManager.IsKeyDown(UP_ARROW)) pos.y -= speed.y * dt;
    }

}