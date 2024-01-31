#include "../include/Minion.h"
#include "../include/Sprite.h"
#include "../include/Bullet.h"
#include "../include/Game.h"

using std::shared_ptr;
#define angularSpeed M_PI/5

Minion::Minion(GameObject& associated, weak_ptr <GameObject> alienCenter, float arcOffsetDeg) : Component (associated){

    this->alienCenter = alienCenter;
    float arcOffsetRad = arcOffsetDeg * M_PI / 180.0;
    this->arc = arcOffsetRad;
    Sprite* minionSprite = new Sprite(associated, "img/minion.png");
    associated.AddComponent(minionSprite);

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

    State& gameState = Game::GetInstance().GetState();

    Vec2 auxiliar;
    auxiliar = auxiliar.SubtractVectors(pos, associated.box.Center());
    float angle = atan2(auxiliar.y, auxiliar.x);

    float speed = 100;
    int damage = 30;
    float maxDistance = 1000;
    string sprite = "img/minionbullet1.png";

    GameObject* newBullet  = new GameObject();
    Bullet* bullet = new Bullet(*newBullet, angle, speed, damage, maxDistance, sprite);
    newBullet->AddComponent(bullet);
    newBullet->box.x = associated.box.Center().x;
    newBullet->box.y = associated.box.Center().y;
    gameState.AddObject(newBullet);
}