#include "../include/Bullet.h"
#include "../include/Sprite.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, string sprite) : Component (associated){
   
    Sprite* bulletSprite = new Sprite(associated, sprite);
    associated.AddComponent(bulletSprite);

    this->speed = Vec2(speed * cos(angle), speed * sin(angle));
    this->distanceLeft = maxDistance;
    this->damage = damage;
    this->bulletAngle = angle;
}

void Bullet::Update(float dt){
    
    Vec2 movement = Vec2(speed.x * dt, speed.y * dt);
    associated.box.x += movement.x;
    associated.box.y += movement.y;

    distanceLeft = distanceLeft - movement.GetLength();
    
    if(distanceLeft <= 0){
        associated.RequestDelete();
    }
    
    Sprite* bulletSprite = (Sprite*) associated.GetComponent("Sprite");
    if(bulletSprite != nullptr){
        bulletAngle = atan2(movement.y, movement.x) * (180 / M_PI);
        bulletSprite->SetAngle(bulletAngle);
    }
}

void Bullet::Render(){

}

bool Bullet::Is(string type){
    return (type == "Bullet") ? true : false;
}

int Bullet::GetDamage(){
    return damage;
}