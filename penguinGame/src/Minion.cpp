#include "../include/Minion.h"
#include "../include/Sprite.h"

using std::shared_ptr;
#define angularSpeed M_PI/5

Minion::Minion(GameObject& associated, weak_ptr <GameObject> alienCenter, float arcOffsetDeg) : Component (associated){

    this->alienCenter = alienCenter;
    float arcOffsetRad = arcOffsetDeg * M_PI / 180.0;
    this->arc = arcOffsetRad;
    Sprite* sprite = new Sprite(associated, "img/minion.png");
    associated.AddComponent(sprite);

}

void Minion::Update(float dt){
    
    shared_ptr<GameObject> centerPointer = alienCenter.lock();
    if(centerPointer == nullptr){
        associated.RequestDelete();
        return;
    }

    arc += angularSpeed * dt;
    if(arc >= 2 * M_PI){
        arc -= 2 * M_PI;
    }


    Vec2 position;
    position = position.AddVectors(Vec2(200, 0).GetRotated(arc), centerPointer->box.Center());
    associated.box.PlaceCenterAt(position);
}

void Minion::Render(){

}

bool Minion::Is(string type){
    return (type == "Minion") ? true : false;
}

void Minion::Shoot(Vec2 pos){

}