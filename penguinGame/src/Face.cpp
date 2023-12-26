#include "../include/Face.h"
#include "../include/Sound.h"
#include "../include/Sprite.h"
#include "../include/InputManager.h"
#include "../include/Camera.h"

#include <iostream>

using std::string;

Face::Face(GameObject& associated) : Component (associated){
    hitpoints = 30;
}

void Face::Damage(int damage){

    if(this->associated.almostDead == true){
        return;
    }

    hitpoints = hitpoints - damage;

    if(hitpoints <= 0){

        Sprite* penguinFace = (Sprite*) this->associated.GetComponent("Sprite");
        Sound* damageSound = (Sound*) this->associated.GetComponent("Sound");

        if(damageSound != nullptr){
            damageSound->Play();
            this->associated.almostDead = true;
            this->associated.RemoveComponent(penguinFace);
        }
    }
}

void Face::Update(float dt){
    Sound* damageSound = (Sound*) this->associated.GetComponent("Sound");

    InputManager& inputManager = InputManager::GetInstance();
    if(inputManager.MousePress(LEFT_MOUSE_BUTTON) || inputManager.MousePress(RIGHT_MOUSE_BUTTON)){

        int mouseX= inputManager.GetMouseX();
        int mouseY= inputManager.GetMouseY();
        if(associated.box.Contains( {(float)mouseX - Camera::pos.x , (float)mouseY - Camera::pos.y} )){
            this->Damage(std::rand() % 10 + 10);
        }
    }
    
    if(this->associated.almostDead == true && !Mix_Playing(damageSound->getChannel())){  
        this->associated.almostDead = false;
        this->associated.RequestDelete();
    }
}

void Face::Render(){

}

bool Face::Is(string type){
    return (type == "Face") ? true : false;
}
