#include "../include/Face.h"
#include "../include/Sound.h"
#include "../include/Sprite.h"

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
