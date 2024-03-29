#include "../include/GameObject.h"

GameObject::GameObject(){
    isDead = false;
    almostDead = false;
    started =  false;
    angleDeg = 0.0;
}

GameObject::~GameObject(){

    for(int i = components.size()-1; i >= 0; i--){
        components.erase(components.begin()+i);
    }

    components.clear();

}

void GameObject::Update(float dt){

    for(long unsigned int i = 0; i < components.size(); i++){
        components[i]->Update(dt);
    }
    
}

void GameObject::Render(){

    for(long unsigned int i = 0; i < components.size(); i++){
        components[i]->Render();
    }

}

bool GameObject::IsDead(){

    return isDead;
    
}

void GameObject::RequestDelete(){

    isDead = true;
    
}

void GameObject::AddComponent(Component* cpt){
    components.emplace_back(cpt);

    if(started){
        cpt->Start();
    }
}

void GameObject::RemoveComponent(Component* cpt){

    for(long unsigned int i = 0; i < components.size(); i++){
        if(components[i].get() == cpt){
            components.erase(components.begin()+i);
        }
    }

}

Component* GameObject::GetComponent(string type){

    for(long unsigned int i = 0; i < components.size(); i++){
        if(components[i]->Is(type)){
            return components[i].get();
        }
    }

    return nullptr;
    
}

void GameObject::Start(){
    
    for(auto& component : components){
        component->Start();
    }
    started = true;

}