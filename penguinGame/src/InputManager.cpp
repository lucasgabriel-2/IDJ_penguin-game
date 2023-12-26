#include "../include/InputManager.h"

#include <SDL2/SDL_events.h>

InputManager& InputManager::GetInstance(){

    static InputManager inputManagerInstance;
    return inputManagerInstance;

}

InputManager::InputManager(){
    
    for (int i = 0; i < 6; ++i){
        mouseState[i] = false;
        mouseUpdate[i] = false;
    }

    quitRequested = false;
    updateCounter = 0;
    mouseX = 0;
    mouseY = 0;
}

InputManager::~InputManager(){

}

void InputManager::Update(){

    quitRequested = false;
    SDL_GetMouseState(&mouseX, &mouseY);

    updateCounter++;

    SDL_Event event;
    while (SDL_PollEvent(&event)){

        if(!(event.key.repeat == 1)){

            switch(event.type){

                case SDL_QUIT:
                    quitRequested = true;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    mouseState[event.button.button] = true;
                    mouseUpdate[event.button.button] = updateCounter;
                    break;

                case SDL_MOUSEBUTTONUP:
                    mouseState[event.button.button] = false;
                    mouseUpdate[event.button.button] = updateCounter;
                    break;

                case SDL_KEYDOWN:
                    keyState[event.key.keysym.sym] = true;
                    keyUpdate[event.key.keysym.sym] = updateCounter;
                    break;

                case SDL_KEYUP:
                    keyState[event.key.keysym.sym] = false;
                    keyUpdate[event.key.keysym.sym] = updateCounter;
                    break;

                default:
                    break;
            }
        }
    }
}

bool InputManager::KeyPress(int key){
    return (keyState[key] && keyUpdate[key] == updateCounter);
}

bool InputManager::KeyRelease(int key){
    return (!keyState[key] && keyUpdate[key] == updateCounter);
}

bool InputManager::IsKeyDown(int key){
    return keyState[key];
}

bool InputManager::MousePress(int button){
    return (mouseState[button] && mouseUpdate[button] == updateCounter);
}

bool InputManager::MouseRelease(int button){
    return (!mouseState[button] && mouseUpdate[button] == updateCounter);
}

bool InputManager::IsMouseDown(int button){
    return mouseState[button];
}

int InputManager::GetMouseX(){
    return mouseX;
}

int InputManager::GetMouseY(){
    return mouseY;
}

bool InputManager::QuitRequested(){
    return quitRequested;
}