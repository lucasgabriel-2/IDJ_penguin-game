#include "../include/Face.h"
#include "../include/Sound.h"
#include "../include/Sprite.h"

#include <iostream>

using std::string;

Face::Face(GameObject& associated) : Component (associated){
    hitpoints = 30;
}

void Face::Damage(int damage){
    hitpoints = hitpoints - damage;

    if(hitpoints <= 0){

        Sprite* penguinFace = (Sprite*) this->associated.GetComponent("Sprite");
        Sound* damageSound = (Sound*) this->associated.GetComponent("Sound");

        if(damageSound != nullptr){
            damageSound->isPlaying = 1;
            damageSound->Play();

            while(damageSound->isPlaying == 1){
                damageSound->isPlaying = Mix_Playing(damageSound->getChannel());
            }

            associated.RemoveComponent(penguinFace);
        }
    }
}

void Face::Update(float dt){
    Sound* damageSound = (Sound*) this->associated.GetComponent("Sound");
    
    if( damageSound->isPlaying == 0){
        this->associated.RequestDelete();
    }
}

void Face::Render(){

}

bool Face::Is(string type){
    return (type == "Face") ? true : false;
}
